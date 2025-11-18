/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Visualize/hkVisualize.h>

// Serialization dependencies
#include <Common/Visualize/Serialize/hkDisplaySerializeOStream.h>
#include <Common/Visualize/hkServerDebugDisplayHandler.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>

hkServerDebugDisplayHandler::hkServerDebugDisplayHandler(hkDisplaySerializeOStream* stream)
: m_outStream(stream)
{
	m_outstreamLock = new hkCriticalSection(1000); // usually no contention
}

hkServerDebugDisplayHandler::~hkServerDebugDisplayHandler()
{
	delete m_outstreamLock;
}

static hkUint32 _getGeometryByteSize(const hkArray<hkDisplayGeometry*>& geometries)
{
	hkUint32 bytes = 4; // numGeoms size
	for(int i = 0; i < geometries.getSize(); i++)
	{
		bytes += hkDisplaySerializeOStream::computeBytesRequired(geometries[i]);
	}
	return bytes;
}

void hkServerDebugDisplayHandler::sendGeometryData(const hkArray<hkDisplayGeometry*>& geometries)
{
	m_outstreamLock->enter();
	{
		m_outStream->write32(geometries.getSize());
		for(int i = 0; i < geometries.getSize(); i++)
		{
			m_outStream->writeDisplayGeometry(geometries[i]);
		}
	}
	m_outstreamLock->leave();
}

hkResult hkServerDebugDisplayHandler::addGeometry(const hkArray<hkDisplayGeometry*>& geometries, const hkTransform& transform, hkUlong id, int tag, hkUlong shapeIdHint)
{
	bool streamOK;

	m_outstreamLock->enter();
	{
		if (m_outStream)
		{
			const int packetSize = 1 + _getGeometryByteSize(geometries) + 7*4 + 8 + 4;
			const hkUint64 longId = (hkUint64)id;

			m_outStream->write32(packetSize);
			// send a serialized version of the displayObject
			m_outStream->write8u(hkDebugDisplayHandler::HK_ADD_GEOMETRY);
			sendGeometryData(geometries);
			m_outStream->writeTransform(transform);
			m_outStream->write64u(longId);
			m_outStream->write32(tag);
		}
		streamOK = (m_outStream && m_outStream->isOk());
	}
	m_outstreamLock->leave();

	return  streamOK ? HK_SUCCESS : HK_FAILURE;
}

hkResult hkServerDebugDisplayHandler::addGeometryInstance(hkUlong originalInstanceID, const hkTransform& transform, hkUlong id, int tag, hkUlong shapeIdHint)
{
	bool streamOK;

	m_outstreamLock->enter();
	{
		if (m_outStream)
		{
		//TODO: const int packetSize = 1 + 8 + 7*4 + 8 + 4;
		//TODO: const hkUint64 longId = (hkUint64)id;

		//TODO: m_outStream->write32(packetSize);
		//TODO: m_outStream->write8u(hkDebugDisplayHandler::HK_ADD_GEOMETRY_INSTANCE);
		//TODO: m_outStream->write64u(originalInstanceID);
		//TODO: m_outStream->writeTransform(transform);
		//TODO: m_outStream->write64u(longId);
		//TODO: m_outStream->write32(tag);

		}
		streamOK = (m_outStream && m_outStream->isOk());
	}
	m_outstreamLock->leave();

	return  streamOK ? HK_SUCCESS : HK_FAILURE;

}

hkResult hkServerDebugDisplayHandler::displayGeometry(const hkArray<hkDisplayGeometry*>& geometries, const hkTransform& transform, int color, int tag)
{
	bool streamOK;

	m_outstreamLock->enter();
	{
		if	(m_outStream)
		{
			const int packetSize = 1 + _getGeometryByteSize(geometries) + 7*4 + 4 + 4;
			m_outStream->write32(packetSize);

			// send a serialized version of the displayObject
			m_outStream->write8u(hkDebugDisplayHandler::HK_DISPLAY_GEOMETRY_WITH_TRANSFORM);
			sendGeometryData(geometries);
			m_outStream->writeTransform(transform);
			m_outStream->write32u(color);
			m_outStream->write32(tag);
		}
		streamOK = (m_outStream && m_outStream->isOk());
	}
	m_outstreamLock->leave();

	return streamOK ? HK_SUCCESS : HK_FAILURE;
}

hkResult hkServerDebugDisplayHandler::displayGeometry(const hkArray<hkDisplayGeometry*>& geometries, int color, int tag)
{
	bool streamOK;

	m_outstreamLock->enter();
	{
		if	(m_outStream)
		{
			const int packetSize = 1 + _getGeometryByteSize(geometries) + 4 + 4;
			m_outStream->write32(packetSize);

			// send a serialized version of the displayObject
			m_outStream->write8u(hkDebugDisplayHandler::HK_DISPLAY_GEOMETRY);
			sendGeometryData(geometries);
			m_outStream->write32u(color);
			m_outStream->write32(tag);
		}
		streamOK = (m_outStream && m_outStream->isOk());
	}
	m_outstreamLock->leave();

	return streamOK ? HK_SUCCESS : HK_FAILURE;
}


hkResult hkServerDebugDisplayHandler::setGeometryColor(int color, hkUlong id, int tag)
{
	bool streamOK;

	m_outstreamLock->enter();
	{
		if (m_outStream)
		{
			const int packetSize = 1 + 4 + 8 + 4;
			const hkUint64 longId = (hkUint64)id;

			m_outStream->write32u(packetSize);
			m_outStream->write8u(hkDebugDisplayHandler::HK_SET_COLOR_GEOMETRY);
			m_outStream->write32u(color);
			m_outStream->write64u(longId);
			m_outStream->write32(tag);
		}
		streamOK = (m_outStream && m_outStream->isOk());
	}
	m_outstreamLock->leave();

	return streamOK ? HK_SUCCESS : HK_FAILURE;
}


hkResult hkServerDebugDisplayHandler::updateGeometry(const hkTransform& transform, hkUlong id, int tag)
{
	bool streamOK;

	m_outstreamLock->enter();
	{
		// update a display object identified by id
		if (m_outStream)
		{
			const int packetSize = 1 + (7*4) + 8 + 4;
			const hkUint64 longId = (hkUint64)id;

			m_outStream->write32u(packetSize);
			m_outStream->write8u(hkDebugDisplayHandler::HK_UPDATE_GEOMETRY);
			m_outStream->writeTransform(transform); // 7 * float
			m_outStream->write64u(longId);
			m_outStream->write32(tag);
		}
		streamOK = (m_outStream && m_outStream->isOk());
	}
	m_outstreamLock->leave();

	return streamOK ? HK_SUCCESS : HK_FAILURE;
}

hkResult hkServerDebugDisplayHandler::removeGeometry(hkUlong id, int tag, hkUlong shapeIdHint)
{
	bool streamOK;

	m_outstreamLock->enter();
	{
		if (m_outStream)
		{
			const int packetSize = 1 + 8 + 4;
			const hkUint64 longId = (hkUint64)id;

			m_outStream->write32u(packetSize);
			// remove a display object identified by id
			m_outStream->write8u(hkDebugDisplayHandler::HK_REMOVE_GEOMETRY);
			m_outStream->write64u(longId);
			m_outStream->write32(tag);
		}
		streamOK = (m_outStream && m_outStream->isOk());
	}
	m_outstreamLock->leave();

	return streamOK ? HK_SUCCESS : HK_FAILURE;
}

hkResult hkServerDebugDisplayHandler::updateCamera(const hkVector4& from, const hkVector4& to, const hkVector4& up, hkReal nearPlane, hkReal farPlane, hkReal fov, const char* name)
{
	bool streamOK;

	m_outstreamLock->enter();
	{
		if (m_outStream)
		{
			const int length = hkString::strLen(name);
			const int packetSize = 1 + 3*3*4 + 3*4 + 2 + length;

			m_outStream->write32u(packetSize);
			// update a display object identified by id
			m_outStream->write8u(hkDebugDisplayHandler::HK_UPDATE_CAMERA);
			m_outStream->writeQuadVector4(from); //3*float
			m_outStream->writeQuadVector4(to);
			m_outStream->writeQuadVector4(up);
			m_outStream->writeFloat32(nearPlane);
			m_outStream->writeFloat32(farPlane);
			m_outStream->writeFloat32(fov);
			// send the name
			m_outStream->write16u( hkUint16(length) );
			m_outStream->writeRaw(name, length);
		}
		streamOK = (m_outStream && m_outStream->isOk());
	}
	m_outstreamLock->leave();

	return streamOK ? HK_SUCCESS : HK_FAILURE;
}

hkResult hkServerDebugDisplayHandler::displayPoint(const hkVector4& position, int color, int tag)
{
	bool streamOK;

	m_outstreamLock->enter();
	{
		if (m_outStream)
		{
			const int packetSize = 1 + 3*4 + 4 + 4;

			m_outStream->write32u(packetSize);
			m_outStream->write8u(hkDebugDisplayHandler::HK_DISPLAY_POINT);
			m_outStream->writeQuadVector4(position);
			m_outStream->write32u(color);
			m_outStream->write32(tag);
		}
		streamOK = (m_outStream && m_outStream->isOk());
	}
	m_outstreamLock->leave();

	return streamOK ? HK_SUCCESS : HK_FAILURE;
}

hkResult hkServerDebugDisplayHandler::displayLine(const hkVector4& start, const hkVector4& end, int color, int tag)
{
	bool streamOK;

	m_outstreamLock->enter();
	{
		if (m_outStream)
		{
			const int packetSize = 1 + 2*3*4 + 4 + 4;

			m_outStream->write32u(packetSize);
			m_outStream->write8u(hkDebugDisplayHandler::HK_DISPLAY_LINE);
			m_outStream->writeQuadVector4(start);
			m_outStream->writeQuadVector4(end);
			m_outStream->write32u(color);
			m_outStream->write32(tag);
		}
		streamOK = (m_outStream && m_outStream->isOk());
	}
	m_outstreamLock->leave();

	return streamOK ? HK_SUCCESS : HK_FAILURE;
}

hkResult hkServerDebugDisplayHandler::displayText(const char* text, int color, int tag)
{
	bool streamOK;

	m_outstreamLock->enter();
	{
		if (m_outStream)
		{
			const int length = hkMath::min2(hkString::strLen(text), 65535);
			const int packetSize = 1 + 2 + length + 4 + 4;

			m_outStream->write32u(packetSize);
			m_outStream->write8u(hkDebugDisplayHandler::HK_DISPLAY_TEXT);
			m_outStream->write16u((unsigned short)length);
			m_outStream->writeRaw(text, length);
			m_outStream->write32(color);
			m_outStream->write32(tag);
		}
		streamOK = (m_outStream && m_outStream->isOk());
	}
	m_outstreamLock->leave();

	return streamOK ? HK_SUCCESS : HK_FAILURE;
}

hkResult hkServerDebugDisplayHandler::display3dText(const char* text, const hkVector4& pos, int color, int tag)
{
	bool streamOK;

	m_outstreamLock->enter();
	{
		if (m_outStream)
		{
			const int length = hkMath::min2(hkString::strLen(text), 65535);
			const int packetSize = 1 + 2 + length + 4 + 4 + 3*4;

			m_outStream->write32u(packetSize);
			m_outStream->write8u(hkDebugDisplayHandler::HK_DISPLAY_TEXT_3D);
			m_outStream->write16u((unsigned short)length);
			m_outStream->writeRaw(text, length);
			m_outStream->write32(color);
			m_outStream->write32(tag);
			m_outStream->writeFloat32(pos(0));
			m_outStream->writeFloat32(pos(1));
			m_outStream->writeFloat32(pos(2));
		}
		streamOK = (m_outStream && m_outStream->isOk());
	}
	m_outstreamLock->leave();

	return streamOK ? HK_SUCCESS : HK_FAILURE;
}

hkResult hkServerDebugDisplayHandler::sendMemStatsDump(const char* data, int length)
{
	bool streamOK;

	m_outstreamLock->enter();
	{
		if (m_outStream)
		{
			const int packetSize = 1 + 4 + length;

			m_outStream->write32u(packetSize);
			m_outStream->write8u(hkDebugDisplayHandler::HK_SEND_MEMSTATS_DUMP);
			m_outStream->write32(length);
			m_outStream->writeRaw(data, length);
		}
		streamOK = (m_outStream && m_outStream->isOk());
	}
	m_outstreamLock->leave();

	return streamOK ? HK_SUCCESS : HK_FAILURE;
}


hkResult hkServerDebugDisplayHandler::holdImmediate()
{
	bool streamOK;

	m_outstreamLock->enter();
	{
		if (m_outStream)
		{
			const int packetSize = 1;

			m_outStream->write32u(packetSize);
			m_outStream->write8u(hkDebugDisplayHandler::HK_HOLD_IMMEDIATE);
		}
		streamOK = (m_outStream && m_outStream->isOk());
	}
	m_outstreamLock->leave();

	return streamOK ? HK_SUCCESS : HK_FAILURE;
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
