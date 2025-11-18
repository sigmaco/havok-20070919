/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/SceneData/hkSceneData.h>
#include <Common/Base/hkBase.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/SceneData/Scene/hkxSceneUtils.h>

#include <Common/Base/Algorithm/Sort/hkSort.h>
#include <Common/SceneData/Scene/hkxScene.h>
#include <Common/SceneData/Attributes/hkxAttributeGroup.h>
#include <Common/SceneData/Graph/hkxNode.h>
#include <Common/SceneData/Camera/hkxCamera.h>
#include <Common/SceneData/Light/hkxLight.h>
#include <Common/SceneData/Material/hkxMaterial.h>
#include <Common/SceneData/Mesh/hkxVertexBuffer.h>
#include <Common/SceneData/Mesh/hkxIndexBuffer.h>
#include <Common/SceneData/Skin/hkxSkinBinding.h>
#include <Common/SceneData/Mesh/hkxMesh.h>
#include <Common/SceneData/Mesh/hkxMeshSection.h>
#include <Common/SceneData/Mesh/hkxVertexFormat.h>

#include <Common/SceneData/Attributes/hkxAttributeGroup.h>

#include <Common/SceneData/Environment/hkxEnvironment.h>


// perform the given transform on the selected scene elements
void hkxSceneUtils::transformScene( hkxScene& scene, const SceneTransformOptions& opts )
{
	// Construct the "transformInfo" object
	TransformInfo transformInfo;
	{
		// The 4x4 matrix
		transformInfo.m_transform = opts.m_transformMatrix;

		// Its inverse
		transformInfo.m_inverse = transformInfo.m_transform;
		if( transformInfo.m_inverse.invert( HK_REAL_EPSILON ) != HK_SUCCESS )
		{
			HK_WARN_ALWAYS ( 0xabba45e4, "Inversion failed. Check the Matrix is not singular" );
			return;
		}

		// The inverse, transposed (for normals)
		transformInfo.m_inverseTranspose = transformInfo.m_inverse;
		transformInfo.m_inverseTranspose.transpose();

		// Its decomposition
		hkMathUtil::decomposeMatrix(transformInfo.m_transform, transformInfo.m_decomposition);
	}

	HK_REPORT_SECTION_BEGIN(0x5e4345e4, "Transform Scene" );

	// nodes
	if( opts.m_applyToNodes && scene.m_rootNode )
	{
		// transform node and node's children
		hkxSceneUtils::transformNode( transformInfo, *scene.m_rootNode);

		HK_REPORT( "Processed all nodes in the scene." );
	}

	// skin bindings
	if( opts.m_applyToNodes && scene.m_numSkinBindings )
	{
		// iterate through all binding in the scene
		for( int cs = 0; cs < scene.m_numSkinBindings; ++cs )
		{
			hkxSkinBinding* skin= scene.m_skinBindings[cs];
			hkxSceneUtils::transformSkinBinding( transformInfo, *skin);
		}

		HK_REPORT( "Processed " << scene.m_numSkinBindings << " skin bindings." );
	}

	// mesh buffers (vertex and/or index)
	if( ( opts.m_applyToBuffers || opts.m_flipWinding ) && scene.m_numMeshes )
	{
		// find the buffers
		for( int cm = 0; cm < scene.m_numMeshes; ++cm )
		{
			hkxMesh* curMesh = scene.m_meshes[cm];

			for( int cs = 0; cs < curMesh->m_numSections; ++cs )
			{
				hkxMeshSection* curSection = curMesh->m_sections[cs];

				// buffers?
				if( opts.m_applyToBuffers )
				{
					// transform the vertex buffer
					hkxSceneUtils::transformVertexBuffer( transformInfo, *curSection->m_vertexBuffer);
				}

				// winding?
				if( opts.m_flipWinding )
				{
					for( int cib = 0; cib < curSection->m_numIndexBuffers; ++cib )
					{
						// flip the triangle winding
						hkxSceneUtils::flipWinding( *curSection->m_indexBuffers[cib] );
					}
				}
			}
		}

		HK_REPORT( "Processed " << scene.m_numMeshes << " meshes." );
	}

	// cameras
	if( opts.m_applyToCameras && scene.m_numCameras )
	{
		for( int cc = 0; cc < scene.m_numCameras; ++cc )
		{
			// transform the cameras
			hkxSceneUtils::transformCamera( transformInfo, *scene.m_cameras[cc]);
		}

		HK_REPORT( "Processed " << scene.m_numCameras << " cameras." );
	}

	// lights
	if( opts.m_applyToLights && scene.m_numLights )
	{
		for( int cc = 0; cc < scene.m_numLights; ++cc )
		{
			// transform the lights
			hkxSceneUtils::transformLight( transformInfo, *scene.m_lights[cc]);
		}

		HK_REPORT( "Processed " << scene.m_numLights << " lights." );
	}

	// Finally, the scene itself
	scene.m_appliedTransform.mul(transformInfo.m_transform);

	HK_REPORT_SECTION_END();
}


// transform a node's keys
void hkxSceneUtils::transformNode( const TransformInfo& transformInfo, hkxNode& node)
{
	// recurse into node tree
	for( int c = 0; c < node.m_numChildren; ++c )
	{
		hkxSceneUtils::transformNode( transformInfo, *node.m_children[c]);
	}

	hkMatrix4 key;

	// Transform the keyframes
	for( int i = 0; i < node.m_numKeyFrames; i++ )
	{
		transformMatrix4(transformInfo, node.m_keyFrames[i]);
	}

	// Transform any attributes of the node that can be transformed
	for ( int agIndex = 0; agIndex < node.m_numAttributeGroups; ++agIndex)
	{
		hkxAttributeGroup& ag = node.m_attributeGroups[agIndex];

		hkxSceneUtils::transformAttributeGroup (transformInfo, ag);
	}
}

void hkxSceneUtils::transformAttributeGroup(const TransformInfo& transformInfo, hkxAttributeGroup& attributeGroup)
{
	for ( int aIndex = 0; aIndex < attributeGroup.m_numAttributes; ++aIndex)
	{
		hkxAttribute& attribute = attributeGroup.m_attributes[aIndex];

		if (attribute.m_value.m_object)
		{
			// we can transform certain known attribute types
			// and can transform based on the hint in those attributes
			const hkClass* klass = attribute.m_value.m_class;

			// Floats
			if ( hkString::strCmp( klass->getName(), hkxAnimatedFloatClass.getName()) == 0)
			{
				hkxAnimatedFloat* f = (hkxAnimatedFloat*) attribute.m_value.m_object;
				transformAnimatedFloat (transformInfo, *f);

				continue;
			}

			// Vectors
			if ( hkString::strCmp( klass->getName(), hkxAnimatedVectorClass.getName()) == 0)
			{
				hkxAnimatedVector* v = (hkxAnimatedVector*)attribute.m_value.m_object;
				transformAnimatedVector (transformInfo, *v);

				continue;
			}

			// Quaternions
			if ( hkString::strCmp( klass->getName(), hkxAnimatedQuaternionClass.getName()) == 0)
			{
				hkxAnimatedQuaternion* q = (hkxAnimatedQuaternion*)attribute.m_value.m_object;
				transformAnimatedQuaternion (transformInfo, *q);

				continue;
			}

			// Matrices
			if ( hkString::strCmp( klass->getName(), hkxAnimatedMatrixClass.getName()) == 0)
			{
				hkxAnimatedMatrix* m = (hkxAnimatedMatrix*)attribute.m_value.m_object;
				transformAnimatedMatrix (transformInfo, *m);

				continue;

			}
		}
	}
}

void hkxSceneUtils::transformAnimatedFloat (const TransformInfo& transformInfo, hkxAnimatedFloat& animatedFloat)
{
	// Scale : floats representing distances
	const bool shouldScale = (animatedFloat.m_hint & hkxAttribute::HINT_SCALE) != 0;

	// Flip : floats representing angles
	const bool shouldFlip = ((animatedFloat.m_hint & hkxAttribute::HINT_FLIP) && transformInfo.m_decomposition.m_flips) != 0;

	// Floats can only be scaled or flipped
	if ( shouldScale || shouldFlip)
	{
		if (shouldScale && shouldFlip)
		{
			HK_WARN_ALWAYS(0xabba8a03, "Float attribute with both FLIP and SCALE flags... Weird..");
		}

		float scaleFloat = (shouldFlip) ? -1.0f : 1.0f;
		if (shouldScale)
		{
			const hkVector4& scaleVector = transformInfo.m_decomposition.m_scale;
			const hkReal scaleLength = hkReal(scaleVector.length3()) / hkMath::sqrt(3.0f);
			scaleFloat *= scaleLength;

		}

		for (int fi= 0; fi < animatedFloat.m_numFloats; ++fi)
		{
			animatedFloat.m_floats[fi] *= scaleFloat;
		}
	}
}

void hkxSceneUtils::transformAnimatedQuaternion (const TransformInfo& transformInfo,  hkxAnimatedQuaternion& animatedQuaternion)
{
	// Quaternions are always transformed as they always represent rotations
	for (int qi=0; qi < animatedQuaternion.m_numQuaternions; qi++)
	{
		hkQuaternion& quatRef = animatedQuaternion.m_quaternions[qi];

		// We rotate the axis of the quaternion by the basis of the transform
		hkVector4 imag = quatRef.getImag();
		imag.setRotatedDir(transformInfo.m_decomposition.m_basis, imag);
		quatRef.setImag(imag);

		// And if the transformation involves a change of handness, flip the sign 
		if (transformInfo.m_decomposition.m_flips)
		{
			quatRef.setReal(-quatRef.getReal());
		}
	}

}

void hkxSceneUtils::transformAnimatedMatrix (const TransformInfo& transformInfo,  hkxAnimatedMatrix& animatedMatrix)
{
	if (animatedMatrix.m_hint & hkxAttribute::HINT_TRANSFORM_AND_SCALE)
	{
		for (int mi= 0; mi < animatedMatrix.m_numMatrices; ++mi)
		{
			transformMatrix4(transformInfo, animatedMatrix.m_matrices[mi]);
		}
	}
}

void hkxSceneUtils::transformAnimatedVector (const TransformInfo& transformInfo,  hkxAnimatedVector& animatedVector)
{
	// Vectors are either just rotated or rotated and scaled
	const bool shouldRotate = (animatedVector.m_hint & hkxAttribute::HINT_TRANSFORM) != 0;
	const bool shouldScale = (animatedVector.m_hint & hkxAttribute::HINT_SCALE) != 0;

	if (!shouldRotate && !shouldScale)
	{
		return;
	}

	hkMatrix3 theTransform; theTransform.setIdentity();
	{
		if (shouldRotate && !shouldScale)
		{
			theTransform = transformInfo.m_decomposition.m_basis;
		}

		if (shouldRotate && shouldScale)
		{
			theTransform = transformInfo.m_transform;
		}

		if (!shouldRotate && shouldScale)
		{
			// uncommon, but...
			const hkVector4& scaleVector = transformInfo.m_decomposition.m_scale;
			theTransform.setDiagonal(scaleVector(0), scaleVector(1), scaleVector(2));
		}
	}

	for (int vi= 0; vi < animatedVector.m_numVectors; ++vi)
	{
		hkVector4 vs = animatedVector.m_vectors[vi];
		animatedVector.m_vectors[vi].setMul3(theTransform, vs);
	}
}



// transform the skin binding
void hkxSceneUtils::transformSkinBinding( const TransformInfo& transformInfo, hkxSkinBinding& nodeInfo)
{
	hkMatrix4 temp;

	// Transform initBoneTransform Array
	{
		for( int i = 0; i < nodeInfo.m_numBindPose; i++ )
		{
			transformMatrix4(transformInfo, nodeInfo.m_bindPose[i]);
		}
	}

	// Transform init skin transform
	{
		transformMatrix4 (transformInfo, nodeInfo.m_initSkinTransform);
	}

}


// transform the vertex buffer data
void hkxSceneUtils::transformVertexBuffer( const TransformInfo& transformInfo, hkxVertexBuffer& vbCinfo)
{
	// Positions are transformed by the full matrix
	const hkMatrix3& trans = transformInfo.m_transform;

	// Normals are transformed by the inverse of the basis, transposed
	const hkMatrix3& transNormal = transformInfo.m_inverseTranspose;
	
	// vertex data
	char* vertexData = (char*)( vbCinfo.m_vertexData );

	// vertex buffer stride
	unsigned int stride = vbCinfo.m_format->m_stride;

	// vertex data pointers
	float* position = HK_NULL;
	float* normal = HK_NULL;
	float* tangent = HK_NULL;
	float* binormal = HK_NULL;

	hkVector4 vector;
	const hkxVertexFormat& fmt = *vbCinfo.m_format;
	
	// iterate through the buffer transforming position and normals
	for( int i = 0; i < vbCinfo.m_numVertexData; i++ )
	{
		if (fmt.m_positionOffset != HK_VFMT_NOT_PRESENT)
		{
			// position ( 3 floats )
			position = (float*)( vertexData + vbCinfo.m_format->m_positionOffset );
			vector.set( position[0], position[1], position[2] );
			vector.setMul3( trans, vector );

			position[0] = vector(0);
			position[1] = vector(1);
			position[2] = vector(2);
		}

		if (fmt.m_normalOffset != HK_VFMT_NOT_PRESENT)
		{
			// normal ( 3 floats )
			normal = (float*)( vertexData + vbCinfo.m_format->m_normalOffset );
			vector.set( normal[0], normal[1], normal[2] );
			vector.setMul3( transNormal, vector ); 
			vector.normalize3IfNotZero();

			normal[0] = vector(0);
			normal[1] = vector(1);
			normal[2] = vector(2);
		}

		if (fmt.m_tangentOffset != HK_VFMT_NOT_PRESENT)
		{
			// tangent ( 3 floats )
			tangent = (float*)( vertexData + vbCinfo.m_format->m_tangentOffset );
			vector.set( tangent[0], tangent[1], tangent[2] );
			vector.setMul3( transNormal, vector );
			vector.normalize3IfNotZero();

			tangent[0] = vector(0);
			tangent[1] = vector(1);
			tangent[2] = vector(2);
		}

		if (fmt.m_binormalOffset != HK_VFMT_NOT_PRESENT)
		{
			// binormal ( 3 floats )
			binormal = (float*)( vertexData + vbCinfo.m_format->m_binormalOffset );
			vector.set( binormal[0], binormal[1], binormal[2] );
			vector.setMul3( transNormal, vector );
			vector.normalize3IfNotZero();
			
			binormal[0] = vector(0);
			binormal[1] = vector(1);
			binormal[2] = vector(2);
		}
		// next vertex
		vertexData += stride;
	}

}


// transform the light
void hkxSceneUtils::transformLight( const TransformInfo& transformInfo, hkxLight& light)
{
	light.m_position.setMul3( transformInfo.m_transform, light.m_position );
	light.m_direction.setRotatedDir( transformInfo.m_decomposition.m_basis, light.m_direction );
}


// transform the camera
void hkxSceneUtils::transformCamera( const TransformInfo& transformInfo, hkxCamera& camera)
{
	camera.m_from.setMul3( transformInfo.m_transform, camera.m_from );
	camera.m_focus.setMul3( transformInfo.m_transform, camera.m_focus );
	camera.m_up.setRotatedDir( transformInfo.m_decomposition.m_basis, camera.m_up );

	// Get a single float value for the scale in the transform,  
	// and scale the clipping planes by it
	const hkVector4& scaleVector = transformInfo.m_decomposition.m_scale;
	const hkReal scaleLength = hkReal(scaleVector.length3()) / hkMath::sqrt(3.0f);
	camera.m_near *= scaleLength;
	camera.m_far *= scaleLength;

	// Change handness of the camera if required
	if (transformInfo.m_decomposition.m_flips)
	{
		camera.m_leftHanded = !camera.m_leftHanded;
	}

}


// flip the triangle winding
void hkxSceneUtils::flipWinding( hkxIndexBuffer &ibuffer )
{
	// 16 bit indices
	unsigned int numI = ibuffer.m_numIndices16 | ibuffer.m_numIndices32;
	if( ibuffer.m_indices16)
	{
		for( unsigned int i = 0; i < numI; i += 3 )
		{
			hkAlgorithm::swap( ibuffer.m_indices16[i+0], ibuffer.m_indices16[i+2] );
		}
	}

	// 32 bit indices
	else if (ibuffer.m_indices32)
	{
		for( unsigned int i = 0; i < numI; i += 3 )
		{
			hkAlgorithm::swap( ibuffer.m_indices32[i+0], ibuffer.m_indices32[i+2] );
		}
	}
	//else tri order in the Vertex Buffer.. TODO

}

// Transforms a fullMatrix4, reused in different places
void hkxSceneUtils::transformMatrix4 (const TransformInfo& transformInfo, hkMatrix4& matrix4)
{
	// We split the matrix4 into a matrix3 and a translation
	hkMatrix3 matrix3; 
	{
		// Take it from the matrix4
		matrix3.setCols(matrix4.getColumn(0), matrix4.getColumn(1), matrix4.getColumn(2));

		// Change of basis (t * m * t^-1)
		hkMatrix3 temp;
		temp.setMul(matrix3, transformInfo.m_inverse);
		matrix3.setMul(transformInfo.m_transform, temp);
	}
	
	hkVector4 translation;
	{
		translation = matrix4.getColumn(3);

		translation.setMul3(transformInfo.m_transform, translation);
		translation(3) = 1.0f; //w
	}

	// We put it back together
	matrix4.setCols(matrix3.getColumn(0), matrix3.getColumn(1), matrix3.getColumn(2), translation);
}

static hkxNode* _findFirstSelected( hkxNode* node )
{
	if( !node )
	{
		return HK_NULL;
	}

	for( int i=0; i<node->m_numChildren; ++i )
	{
		hkxNode* child = node->m_children[i];
		if( child->m_selected )
		{
			return child;
		}
		else
		{
			hkxNode* descendant = _findFirstSelected( child );
			if( descendant != HK_NULL )
			{
				return descendant;
			}
		}
	}
	return HK_NULL;
}

void hkxSceneUtils::fillEnvironmentFromScene(const hkxScene& scene, hkxEnvironment& environment)
{
	if (scene.m_modeller)
	{
		environment.setVariable("modeller", hkString::strDup(scene.m_modeller));
	}

	if (scene.m_asset)
	{
		// Full path
		{
			environment.setVariable("assetPath", hkString::strDup(scene.m_asset));
		}

		// Find the asset name, i.e. remove the path and file extension.
		{
			hkString assetName = hkString( scene.m_asset );
			{
				int offset = assetName.lastIndexOf( '\\' ) + 1;
				int len = ( assetName.lastIndexOf( '.' ) - offset > 0 ) ? assetName.lastIndexOf( '.' ) - offset : assetName.getLength();

				assetName = assetName.substr( offset, len );

				if( assetName.getLength() == 0 )
				{
					assetName = "untitled";
				}
			}

			environment.setVariable("asset", hkString::strDup(assetName.cString()));
		}

		// Folder
		{
			hkString fullPath (scene.m_asset);

			const int folderEndIdx = hkMath::max2(fullPath.lastIndexOf('\\'), fullPath.lastIndexOf('/'));

			const char* assetFolder = "";

			if (folderEndIdx>=0)
			{
				assetFolder = hkString::strDup(hkString(scene.m_asset, folderEndIdx+1).cString());
			}

			environment.setVariable("assetFolder", assetFolder);
		}


	}

	// EXP-631
	{
		hkxNode* firstSelected = _findFirstSelected(scene.m_rootNode);

		if (firstSelected && firstSelected->m_name)
		{
			environment.setVariable("selected", hkString::strDup(firstSelected->m_name));
		}
	}

	
}

static bool _nodeCompare (hkxNode* one, hkxNode* two)
{
	if (!one || !one->m_name) return true;
	if (!two || !two->m_name) return false;

	return (hkString::strCasecmp(one->m_name, two->m_name)<0);
}

static void _reorderChildrenOfNodeRecursive (hkxNode* node)
{
	if (!node) return;

	// Recurse
	{
		for (int i=0; i<node->m_numChildren; i++)
		{
			_reorderChildrenOfNodeRecursive(node->m_children[i]);
		}
	}

	// Reorder
	{
		hkAlgorithm::quickSort(node->m_children, node->m_numChildren, _nodeCompare);
	}
}

/*static*/ void hkxSceneUtils::reorderNodesAlphabetically ( class hkxScene& scene )
{
	_reorderChildrenOfNodeRecursive(scene.m_rootNode);
}

/*static*/ hkxMesh* hkxSceneUtils::getMeshFromNode (const hkxNode* node)
{
	if (!node) return HK_NULL;
	if (!node->m_object.m_class) return HK_NULL;

	if (hkString::strCasecmp (node->m_object.m_class->getName(), hkxMeshClass.getName())==0)
	{
		return (hkxMesh*) node->m_object.m_object;
	}
	else if (hkString::strCasecmp(node->m_object.m_class->getName(), hkxSkinBindingClass.getName())==0)
	{
		return ((hkxSkinBinding*) node->m_object.m_object)->m_mesh;
	}

	return HK_NULL;
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
