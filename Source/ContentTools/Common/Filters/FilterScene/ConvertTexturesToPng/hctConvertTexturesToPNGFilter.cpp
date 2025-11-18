/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <ContentTools/Common/Filters/FilterScene/hctFilterScene.h>

// GDI+ to make the image handling simple
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

#include <ContentTools/Common/Filters/FilterScene/ConvertTexturesToPng/hctConvertTexturesToPNGFilter.h>

#include <Common/Base/System/Io/Reader/Memory/hkMemoryStreamReader.h>
#include <Common/Base/System/Io/Writer/Array/hkArrayStreamWriter.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>
#include <Common/Base/System/Io/Reader/hkStreamReader.h>

#include <Common/SceneData/Material/hkxMaterial.h>
#include <Common/SceneData/Material/hkxTextureFile.h>
#include <Common/SceneData/Material/hkxTextureInplace.h>
#include <Common/Base/Reflection/hkTypeInfo.h>

#include <tchar.h>

int _GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}


hctConvertTexturesToPNGFilterDesc g_convertTexturesToPNGDesc;

hctConvertTexturesToPNGFilter::hctConvertTexturesToPNGFilter(const hctFilterManagerInterface* owner)
: hctFilterInterface (owner)
{
	// initial defaults
	m_options.m_enable = false;
	m_options.m_u = 0;
	m_options.m_v = 0;
}

hctConvertTexturesToPNGFilter::~hctConvertTexturesToPNGFilter()
{

}

static inline hkUint32 hkRoundUpPow2(hkUint32 n)
{
	n--;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	n++;
	return n;
}

static inline hkUint32 hkRoundDownPow2(hkUint32 n)
{
	return hkRoundUpPow2( n - n/2 + 1);
}

static void recursivelyFindSceneMaterials(hkxMaterial* current, hkArray<hkxMaterial*>& sceneMaterials)
{
	if (current != HK_NULL)
	{
		sceneMaterials.pushBack(current);
	}

	for (int i=0; i< current->m_numSubMaterials; i++)
	{
		recursivelyFindSceneMaterials(current->m_subMaterials[i], sceneMaterials);
	}
}

static void findSceneMaterials(hkxScene& scene, hkArray<hkxMaterial*>& sceneMaterials)
{
		for (int cim = 0; cim < scene.m_numMaterials; ++cim)
		{
			recursivelyFindSceneMaterials( scene.m_materials[cim], sceneMaterials) ;
		}
}

void hctConvertTexturesToPNGFilter::process( hkRootLevelContainer& data, bool batchMode )
{
	// EXP-370
	hkThreadMemory& sceneMemory = hkThreadMemory::getInstance();

	// Find the scene in the root level container
	hkxScene* scenePtr = reinterpret_cast<hkxScene*>( data.findObjectByType( hkxSceneClass.getName() ) );
	if (scenePtr == HK_NULL)
	{
		HK_WARN_ALWAYS(0xabbaa5f0, "No scene data found");
		return;
	}
	hkxScene& scene = *scenePtr;

	hkArray<hkxTextureFile*> doneTextures;
	hkArray<hkxTextureInplace*> replacementTextures;

	if (scene.m_numMaterials > 0)
	{
		ULONG_PTR gdiplusToken;
		GdiplusStartupInput gdiplusStartupInput;	
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		hkArray<hkxMaterial*> sceneMaterials;
		findSceneMaterials(scene, sceneMaterials);

		for (int cim = 0; cim < sceneMaterials.getSize(); ++cim)
		{
			hkxMaterial* material = sceneMaterials[cim];
			// all external textures (can extend to inplace aswell later on)
			for (int net = 0; net < material->m_numStages; ++net)
			{
				if ( !(material->m_stages[net].m_texture.m_class) || !(material->m_stages[net].m_texture.m_object) || (hkString::strCmp( material->m_stages[net].m_texture.m_class->getName(), hkxTextureFileClass.getName() ) != 0) )
					continue;

				hkxTextureInplace* pTi = HK_NULL;
				hkxTextureFile* textureFile = (hkxTextureFile*)( material->m_stages[net].m_texture.m_object );
				int doneIdx = doneTextures.indexOf(textureFile);
				if ( doneIdx >= 0)
				{
					// done already
					pTi = replacementTextures[doneIdx];
				}
				else
				{
					
					// add so we don't try again
					doneTextures.pushBack(textureFile);
					replacementTextures.pushBack(HK_NULL);

					hkString filename = textureFile->m_filename;
					hkString filenameLowerCase =  filename.asLowerCase();
					
					char *pBuff = HK_NULL;
					int buffSize = 0;

					// types we don't convert / don't need to convert, but can imbed
					bool isDDS = filenameLowerCase.endsWith("dds");
					bool isTGA = filenameLowerCase.endsWith("tga");
					if ( isDDS || isTGA ) 
					{
						hkIstream istr(filename.cString());
						if ( istr.isOk() && istr.getStreamReader()->seekTellSupported())
						{
							istr.getStreamReader()->seek(0, hkStreamReader::STREAM_END);
							buffSize = istr.getStreamReader()->tell();
							if (buffSize < 1) 
							{
								buffSize = 0; 
								HK_WARN_ALWAYS(0xabba7ed3, "Couldn't load file: " << filename.cString());
								continue;
							}
							pBuff = (char*)sceneMemory.allocateChunk( buffSize, HK_MEMORY_CLASS_EXPORT );
							istr.getStreamReader()->seek(0, hkStreamReader::STREAM_SET);
							int r = istr.read( pBuff, buffSize );
							if (r != buffSize)
							{
								sceneMemory.deallocateChunk(pBuff, buffSize, HK_MEMORY_CLASS_EXPORT);
								HK_WARN_ALWAYS(0xabba7ed3, "Couldn't load file: " << filename.cString());
								continue;
							}
							HK_REPORT("Embedded " << filename.cString() );
						}
						else
						{
							HK_WARN_ALWAYS(0xabba66d5, "Texture file " << filename.cString() << " not found.");
							continue;						
						}
					}
					else // try to convert to png
					{
						const char* fn = filename.cString();
						int nLen = MultiByteToWideChar(CP_ACP, 0,fn, -1, NULL, NULL);
						LPWSTR lpszFilenameW = new WCHAR[nLen];
						MultiByteToWideChar(CP_ACP, 0, fn, -1, lpszFilenameW, nLen);
						// use it to call OLE here

						HK_REPORT("Converting " << filename.cString());
						
						Bitmap image( lpszFilenameW );
						delete [] lpszFilenameW;
											
						// Render to a proper sized image
						Bitmap* bm = &image;
						if (image.GetLastStatus()!=Ok)
						{
							HK_WARN_ALWAYS(0xabba7ed3, "Couldn't load texture file: " << filename.cString());
							continue;
						}

						hkUint32 rw = hkRoundDownPow2( bm->GetWidth());
						hkUint32 rh = hkRoundDownPow2( bm->GetHeight());

						if( m_options.m_enable )
						{
							rw = m_options.m_u;
							rh = m_options.m_v;
						}

						// texture resizing/reformatting
						Bitmap* resized = HK_NULL;
						if ( (rw != bm->GetWidth()) || (rh != bm->GetHeight()) ||
							 (bm->GetPixelFormat() == PixelFormat1bppIndexed) ||
							 (bm->GetPixelFormat() == PixelFormat4bppIndexed) ||
							 (bm->GetPixelFormat() == PixelFormat8bppIndexed) )
						{		
							HK_REPORT("Resizing (" << bm->GetWidth() << "," << bm->GetHeight() << ") to (" << rw << "," << rh << ")");
							resized = new Bitmap( rw, rh, PixelFormat32bppARGB);
							Graphics* g = Graphics::FromImage(resized);
							g->Clear(Color(255,255,255,255));
							//g->SetCompositingMode(CompositingModeSourceCopy);
							g->SetInterpolationMode(InterpolationModeHighQuality);
							RectF rect( 0, 0, (Gdiplus::REAL)rw, (Gdiplus::REAL)rh );
							g->DrawImage(bm, rect,0,0,(Gdiplus::REAL)bm->GetWidth(), (Gdiplus::REAL)bm->GetHeight(), UnitPixel);
							delete g;

							bm = resized; // use the resized version
						}

						// Get encoder class id for png compression
						// for other compressions use
						//    image/bmp
						//    image/jpeg
						//    image/gif
						//    image/tiff

						CLSID pngClsid;
						_GetEncoderClsid(L"image/png", &pngClsid);

						// Setup encoder parameters
						EncoderParameters encoderParameters;
						encoderParameters.Count = 1;
						encoderParameters.Parameter[0].Guid = EncoderQuality;
						encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
						encoderParameters.Parameter[0].NumberOfValues = 1;

						// setup compression level
						ULONG quality = 100;
						encoderParameters.Parameter[0].Value = &quality;

						// Create stream with 0 size
						IStream* pIStream    = NULL;
						if(CreateStreamOnHGlobal(NULL, TRUE, (LPSTREAM*)&pIStream) != S_OK)
						{
							//	AfxMessageBox(_T("Failed to create stream on global memory!"));
							continue;
						}

						//  Save the image to the stream
						Status SaveStatus = bm->Save(pIStream, &pngClsid, &encoderParameters);
						if (resized) delete resized;

						if(SaveStatus != Ok)
						{
							// this should free global memory used by the stream
							// according to MSDN
							pIStream->Release();
						//	AfxMessageBox(_T("Failed to save to stream!"));
							continue;
						}

						// get the size of the stream
						ULARGE_INTEGER ulnSize;
						LARGE_INTEGER lnOffset;
						lnOffset.QuadPart = 0;
						if(pIStream->Seek(lnOffset, STREAM_SEEK_END, &ulnSize) != S_OK)
						{
							pIStream->Release();
						//	AfxMessageBox(_T("Failed to get the size of the stream!"));
							continue;
						}

						// now move the pointer to the beginning of the file
						if(pIStream->Seek(lnOffset, STREAM_SEEK_SET, NULL) != S_OK)
						{
							pIStream->Release();
						//	AfxMessageBox(_T("Failed to move the file pointer to "
						//		"the beginning of the stream!"));
							continue;
						}

						buffSize = (int)ulnSize.QuadPart;
						pBuff = (char*)sceneMemory.allocateChunk( buffSize, HK_MEMORY_CLASS_EXPORT );

						// Read the stream directly into the buffer
						ULONG ulBytesRead;
						if(pIStream->Read(pBuff, (ULONG)ulnSize.QuadPart, &ulBytesRead) != S_OK)
						{
							pIStream->Release();
							// never deallocate, let the scene management do that.
							continue;
						}

						HK_REPORT("Converted and embedded " << filename.cString() );

						// Free memory used by the stream
						pIStream->Release();
					}

					// make our new texture
					pTi = (hkxTextureInplace*)sceneMemory.alignedAllocate( sizeof(void*), sizeof(hkxTextureInplace), HK_MEMORY_CLASS_EXPORT);
					pTi->m_data = (hkUint8*)pBuff; // will be dealloced after delete.
					pTi->m_numData = buffSize;
					
					if (isTGA)
					{
						pTi->m_fileType[0] = 'T'; pTi->m_fileType[1] = 'G'; pTi->m_fileType[2] = 'A';
					}
					else if (isDDS)
					{
						pTi->m_fileType[0] = 'D'; pTi->m_fileType[1] = 'D'; pTi->m_fileType[2] = 'S';
					}
					else
					{
						pTi->m_fileType[0] = 'P'; pTi->m_fileType[1] = 'N'; pTi->m_fileType[2] = 'G';
					}				
					pTi->m_fileType[3] = '\0';

					replacementTextures[replacementTextures.getSize()-1] = pTi;
				}

				// Replace it! 
				if (pTi)
				{
					material->m_stages[net].m_texture.m_class = &hkxTextureInplaceClass;
					material->m_stages[net].m_texture.m_object = pTi; 
				}
			}
			
		} // all mats
		GdiplusShutdown(gdiplusToken);
	}
}


void hctConvertTexturesToPNGFilter::setOptions( const void* optionData, int optionDataSize, unsigned int version ) 
{
	// Check if the options have been saved as raw data.
	if ( version < HCT_FILTER_VERSION(1,1,1) )
	{
		hkString::memCpy( &m_options, optionData, optionDataSize );
		return;
	}
	else if ( version != g_convertTexturesToPNGDesc.getFilterVersion() )
	{
		HK_WARN_ALWAYS( 0xabba4ace, "The " << g_convertTexturesToPNGDesc.getShortName() << " option data was of an incompatible version and could not be loaded." );
		return;
	}

	// Get the options from the XML data.
	if ( hctFilterUtils::readOptionsXml( optionData, optionDataSize, m_optionsBuf, hctConvertTexturesToPNGOptionsClass ) == HK_SUCCESS )
	{
		hctConvertTexturesToPNGOptions* options = reinterpret_cast<hctConvertTexturesToPNGOptions*>( m_optionsBuf.begin() );

		m_options = *options;
	}
	else
	{
		HK_WARN_ALWAYS( 0xabba8821, "The XML for the " << g_convertTexturesToPNGDesc.getShortName() << " option data could not be loaded." );
		return;
	}
}

int hctConvertTexturesToPNGFilter::getOptionsSize() const
{
	hctFilterUtils::writeOptionsXml( hctConvertTexturesToPNGOptionsClass, &m_options, m_optionsBuf, g_convertTexturesToPNGDesc.getShortName() );
	return m_optionsBuf.getSize();
}

void hctConvertTexturesToPNGFilter::getOptions(void* optionData) const
{
	// can memcpy as the options have no strings, char* etc.
	hkString::memCpy( optionData, m_optionsBuf.begin(), m_optionsBuf.getSize() );
}


/*
* Havok SDK - PUBLIC RELEASE, BUILD(#20070919)
*
* Confidential Information of Havok.  (C) Copyright 1999-2007 
* Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
* Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
* rights, and intellectual property rights in the Havok software remain in
* Havok and/or its suppliers.
*
* Use of this software for evaluation purposes is subject to and indicates 
* acceptance of the End User licence Agreement for this product. A copy of 
* the license is included with this software and is also available from salesteam@havok.com.
*
*/
