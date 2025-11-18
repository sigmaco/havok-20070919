/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Visualize/hkVisualize.h>
#include <Common/Visualize/hkVisualDebuggerDebugOutput.h>
#include <Common/Visualize/Serialize/hkDisplaySerializeOStream.h>

// Definitions of complex types
#include <Common/Base/Types/Geometry/hkGeometry.h>
#include <Common/Base/System/Io/Writer/Buffered/hkBufferedStreamWriter.h>
#include <Common/Visualize/Shape/hkDisplayGeometry.h>
#include <Common/Visualize/Shape/hkDisplaySphere.h>
#include <Common/Visualize/Shape/hkDisplayBox.h>
#include <Common/Visualize/Shape/hkDisplayAABB.h>
#include <Common/Visualize/Shape/hkDisplayCone.h>
#include <Common/Visualize/Shape/hkDisplaySemiCircle.h>
#include <Common/Visualize/Shape/hkDisplayPlane.h>
#include <Common/Visualize/Shape/hkDisplayCapsule.h>
#include <Common/Visualize/Shape/hkDisplayCylinder.h>

#define _PACKET_SIZE 8192 // 8KB (the MTU (max transmission unit) for ethernet is 1500bytes usually). 

hkDisplaySerializeOStream::hkDisplaySerializeOStream(hkStreamWriter* writer)
	: hkOArchive( new hkBufferedStreamWriter(writer, _PACKET_SIZE) )
{
	m_writer->removeReference(); // our one we made with new() above.
}

hkDisplaySerializeOStream::hkDisplaySerializeOStream(hkArray<char>& buf)
	: hkOArchive(buf)
{
}

void hkDisplaySerializeOStream::writeQuadVector4(const hkVector4& v)
{
	writeArrayFloat32(&v(0), 3);
}

void hkDisplaySerializeOStream::writeTransform(const hkTransform& t)
{
//	writeFloats(&t.getRotation().getColumn(0)(0), 16);
	
//*
	// get the position
	hkVector4 position = t.getTranslation();

	// get the orientation
	hkRotation rotation = t.getRotation();
	hkQuaternion orientation(rotation);
//	HK_VISUAL_DEBUGGER_INFO(0, "Warning rotation of transform no normalized!");
//	if(orientation.getReal() != 1.0f) this should be done differently

	// send data
	writeArrayFloat32(&position(0), 3);
	writeArrayFloat32(&orientation(0), 4);
//*/
}

void hkDisplaySerializeOStream::writeTriangle(const hkGeometry::Triangle& ti)
{
	write32(ti.m_a);
	write32(ti.m_b);
	write32(ti.m_c);
}

void hkDisplaySerializeOStream::writeGeometry(const hkGeometry& g)
{
	// dump out the array of vertices
	{
		const int s = g.m_vertices.getSize();

		write32(s);
		for(int i = 0; i < s; i++)
		{
			writeQuadVector4(g.m_vertices[i]);
		}
	}

	// dump out the array of triangle indices
	{
		const int s = g.m_triangles.getSize();

		write32(s);
		for(int i = 0; i < s; i++)
		{
			writeTriangle(g.m_triangles[i]);
		}
	}
}

hkUint32 hkDisplaySerializeOStream::computeBytesRequired( const hkGeometry& g )
{
	hkUint32 vertBytes = 4 + ( (3*4)*g.m_vertices.getSize() );
	hkUint32 triBytes = 4 + ( (3*4)*g.m_triangles.getSize() );
	return vertBytes + triBytes;
}

void hkDisplaySerializeOStream::writeDisplayGeometry(hkDisplayGeometry* dg)
{
	// dump the information which defines the given type of display geometry
	const hkDisplayGeometryType t = dg->getType();
	write8( char(t) );

	switch(t)
	{
		case HK_DISPLAY_CONVEX:
			{
				writeTransform(dg->getTransform());
				HK_ASSERT2(0x65e14373, dg->getGeometry(), "A display geometry must have a valid geometry pointer!");
				hkGeometry& g = *dg->getGeometry();
				writeGeometry(g);
			}
			break;

		case HK_DISPLAY_SPHERE:
			{
				writeTransform(dg->getTransform());
				hkDisplaySphere* ds = static_cast<hkDisplaySphere*>(dg);
				hkSphere s; ds->getSphere(s);
				writeFloat32(s.getRadius());
				writeQuadVector4(s.getPosition());
				write32(ds->getXRes());
				write32(ds->getYRes());
			}
			break;

		case HK_DISPLAY_CAPSULE:
			{
				writeTransform(dg->getTransform());
				hkDisplayCapsule* dc = static_cast<hkDisplayCapsule*>(dg);
				writeFloat32(dc->getRadius());
				writeQuadVector4(dc->getTop());
				writeQuadVector4(dc->getBottom());
				write32(dc->getNumSides());
				write32(dc->getNumHeightSamples());
			}
			break;

		case HK_DISPLAY_CYLINDER:
			{
				writeTransform(dg->getTransform());
				hkDisplayCylinder* dc = static_cast<hkDisplayCylinder*>(dg);
				writeFloat32(dc->getRadius());
				writeQuadVector4(dc->getTop());
				writeQuadVector4(dc->getBottom());
				write32(dc->getNumSides());
				write32(dc->getNumHeightSamples());
			}
			break;

		case HK_DISPLAY_BOX:
			{
				writeTransform(dg->getTransform());
				hkDisplayBox* db = static_cast<hkDisplayBox*>(dg);
				writeQuadVector4(db->getHalfExtents());
			}
			break;

		case HK_DISPLAY_AABB:
			{
				hkDisplayAABB* daabb = static_cast<hkDisplayAABB*>(dg);
				writeQuadVector4(daabb->getMinExtent());
				writeQuadVector4(daabb->getMaxExtent());
			}
			break;

		case HK_DISPLAY_CONE:
			{
				hkDisplayCone* dcone = static_cast<hkDisplayCone*>(dg);
				writeQuadVector4(dcone->getPosition());
				writeQuadVector4(dcone->getAxis());
				writeFloat32(dcone->getAngle());
				writeFloat32(dcone->getHeight());
				write32(dcone->getNumSegments());
			}
		
			break;
	
		case HK_DISPLAY_SEMICIRCLE:
			{
				hkDisplaySemiCircle* dsemi = static_cast<hkDisplaySemiCircle*>(dg);
				writeQuadVector4(dsemi->getCenter());
				writeQuadVector4(dsemi->getNormal());
				writeQuadVector4(dsemi->getPerp());
				writeFloat32(dsemi->getRadius());
				writeFloat32(dsemi->getThetaMin());
				writeFloat32(dsemi->getThetaMax());
				write32(dsemi->getNumSegments());
			}
			break;

		case HK_DISPLAY_PLANE:
			{
				hkDisplayPlane* dplane = static_cast<hkDisplayPlane*>(dg);
				writeQuadVector4(dplane->getCenter());
				writeQuadVector4(dplane->getNormal());
				writeQuadVector4(dplane->getPerpToNormal());
				writeFloat32(dplane->getExtents()(0)); //XXX: need to change protocol to send all 3 extents
			}
			break;

		default:
			HK_ASSERT2(0x71315d69, 0, "Display stream corrupt or unsupported display geometry cannot serialize!");
	}
}


hkUint32 hkDisplaySerializeOStream::computeBytesRequired( hkDisplayGeometry* dg )
{
	const hkDisplayGeometryType t = dg->getType();
	hkUint32 bytes = 1; // type field

	switch(t)
	{
	case HK_DISPLAY_CONVEX:
		{
			bytes += 7*4; //writeTransform(dg->getTransform());
			hkGeometry& g = *dg->getGeometry();
			bytes += computeBytesRequired(g);
		}
		break;

	case HK_DISPLAY_SPHERE:
		{
			bytes += 7*4;//writeTransform(dg->getTransform());
			//hkDisplaySphere* ds = static_cast<hkDisplaySphere*>(dg);
			//writeFloat32(ds->getSphere().getRadius());
			//writeQuadVector4(ds->getSphere().getPosition()); //3*4
			//write32(ds->getXRes());
			//write32(ds->getYRes());
			bytes += 3*4 + 3*4;
		}
		break;

	case HK_DISPLAY_CAPSULE:
		{
			bytes += 7*4; //writeTransform(dg->getTransform());
			//hkDisplayCapsule* dc = static_cast<hkDisplayCapsule*>(dg);
			//writeFloat32(dc->getRadius());
			//writeQuadVector4(dc->getTop());
			//writeQuadVector4(dc->getBottom());
			//write32(dc->getNumSides());
			//write32(dc->getNumHeightSamples());
			bytes += 3*4 + 2*3*4; 
		}
		break;

	case HK_DISPLAY_CYLINDER:
		{
			bytes += 7*4; //writeTransform(dg->getTransform());
			//hkDisplayCylinder* dc = static_cast<hkDisplayCylinder*>(dg);
			//writeFloat32(dc->getRadius());
			//writeQuadVector4(dc->getTop());
			//writeQuadVector4(dc->getBottom());
			//write32(dc->getNumSides());
			//write32(dc->getNumHeightSamples());
			bytes += 3*4 + 2*3*4; 
		}
		break;

	case HK_DISPLAY_BOX:
		{
			bytes += 7*4;//writeTransform(dg->getTransform());
			//hkDisplayBox* db = static_cast<hkDisplayBox*>(dg);
			//writeQuadVector4(db->getHalfExtents());
			bytes += 3*4;
		}
		break;

	case HK_DISPLAY_AABB:
		{
			//hkDisplayAABB* daabb = static_cast<hkDisplayAABB*>(dg);
			//writeQuadVector4(daabb->getMinExtent());
			//writeQuadVector4(daabb->getMaxExtent());
			bytes += 2*3*4;
		}
		break;

	case HK_DISPLAY_CONE:
		{
			//hkDisplayCone* dcone = static_cast<hkDisplayCone*>(dg);
			//writeQuadVector4(dcone->getPosition());
			//writeQuadVector4(dcone->getAxis());
			//writeFloat32(dcone->getAngle());
			//writeFloat32(dcone->getHeight());
			//write32(dcone->getNumSegments());
			bytes += 2*3*4 + 3*4;
		}

		break;

	case HK_DISPLAY_SEMICIRCLE:
		{
			//hkDisplaySemiCircle* dsemi = static_cast<hkDisplaySemiCircle*>(dg);
			//writeQuadVector4(dsemi->getCenter());
			//writeQuadVector4(dsemi->getNormal());
			//writeQuadVector4(dsemi->getPerp());
			//writeFloat32(dsemi->getRadius());
			//writeFloat32(dsemi->getThetaMin());
			//writeFloat32(dsemi->getThetaMax());
			//write32(dsemi->getNumSegments());
			bytes += 3*3*4 + 4*4;
		}
		break;

	case HK_DISPLAY_PLANE:
		{
			//hkDisplayPlane* dplane = static_cast<hkDisplayPlane*>(dg);
			//writeQuadVector4(dplane->getCenter());
			//writeQuadVector4(dplane->getNormal());
			//writeQuadVector4(dplane->getPerpToNormal());
			//writeFloat32(dplane->getExtent());
			bytes += 3*3*4 + 4;
		}
		break;

	default:
		HK_ASSERT2(0x71315d69, 0, "Display stream corrupt or unsupported display geometry cannot serialize!");
	}

	return bytes;
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
