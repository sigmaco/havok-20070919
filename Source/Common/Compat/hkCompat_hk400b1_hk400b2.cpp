/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#include <Common/Compat/hkCompat.h>
#include <Common/Compat/hkCompatUtil.h>
#include <Common/Serialize/Version/hkVersionRegistry.h>
#include <Common/Serialize/Version/hkVersionUtil.h>
#include <Common/Serialize/Util/hkBuiltinTypeRegistry.h>
#include <Common/Serialize/Version/hkObjectUpdateTracker.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Common/Compat/hkHavokAllClasses.h>

#include <Common/Base/Algorithm/Sort/hkSort.h>
#include <Common/Base/Math/hkMath.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>

enum SimulationType330
{
	SIMULATION_TYPE_INVALID_400b1,
	SIMULATION_TYPE_DISCRETE_400b1,
	SIMULATION_TYPE_ASYNCHRONOUS_400b1,
	SIMULATION_TYPE_HALFSTEP_400b1,
	SIMULATION_TYPE_CONTINUOUS_400b1,
	SIMULATION_TYPE_CONTINUOUS_HALFSTEP_400b1,
	SIMULATION_TYPE_CONTINUOUS_ONE_THIRD_STEP_400b1,
	SIMULATION_TYPE_BACKSTEP_SIMPLE_400b1,
	SIMULATION_TYPE_BACKSTEP_NON_PENETRATING_400b1,
	SIMULATION_TYPE_MULTITHREADED_400b1,
};

enum SimulationType400
{
	SIMULATION_TYPE_INVALID_400b2,
	SIMULATION_TYPE_DISCRETE_400b2,
	SIMULATION_TYPE_CONTINUOUS_400b2,
	SIMULATION_TYPE_MULTITHREADED_400b2,
};


static void WorldCinfoVersion_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{

	//
	// Update simulation type
	//

	hkClassMemberAccessor newSimulationType(newObj, "simulationType");
	hkClassMemberAccessor oldSimulationType(oldObj, "simulationType");
	if( newSimulationType.isOk() && oldSimulationType.isOk() )
	{
		//
		hkInt8 type = oldSimulationType.asInt8();
		switch ( type )
		{
			case SIMULATION_TYPE_DISCRETE_400b1:
			{
				newSimulationType.asInt8() = SIMULATION_TYPE_DISCRETE_400b2;
				break;
			}
			case SIMULATION_TYPE_ASYNCHRONOUS_400b1:
			case SIMULATION_TYPE_HALFSTEP_400b1:
			{
				HK_WARN(0x9fe65234, "Unsupported simulation type, setting to SIMULTION_TYPE_DISCRETE. See documentation on world stepping and time management");
				newSimulationType.asInt8() = SIMULATION_TYPE_DISCRETE_400b2;
				break;
			}
			case SIMULATION_TYPE_CONTINUOUS_400b1:
			case SIMULATION_TYPE_CONTINUOUS_HALFSTEP_400b1:
			case SIMULATION_TYPE_CONTINUOUS_ONE_THIRD_STEP_400b1:
			{
				HK_WARN(0x9fe65234, "Unsupported simulation type, setting to SIMULATION_TYPE_CONTINUOUS. See documentation on world stepping and time management");
				newSimulationType.asInt8() = SIMULATION_TYPE_CONTINUOUS_400b2;
				break;
			}
			case SIMULATION_TYPE_BACKSTEP_SIMPLE_400b1:
			case SIMULATION_TYPE_BACKSTEP_NON_PENETRATING_400b1:
			{
				HK_WARN(0x9fe65234, "Unsupported simulation type, setting to SIMULATION_TYPE_INVALID. See documentation on world stepping and time management");
				newSimulationType.asInt8() = SIMULATION_TYPE_INVALID_400b2;
				break;
			}
			case SIMULATION_TYPE_MULTITHREADED_400b1:
			{
				newSimulationType.asInt8() = SIMULATION_TYPE_MULTITHREADED_400b2;
				break;
			}
			default:
			{
				HK_ASSERT2(0xeafea795, 0, "Unknown old simulation type");
				break;
			}
		}
	}
	else
	{
		HK_ASSERT2(0xad7daade, false, "member not found");
	}

	//
	// Update frane synchronization
	//

	hkClassMemberAccessor newFrameMarkerPsiSnap(newObj, "frameMarkerPsiSnap");
	hkClassMemberAccessor oldSynchronizeFrameAndPhysicsTime(oldObj, "synchronizeFrameAndPhysicsTime");

	if ( oldSynchronizeFrameAndPhysicsTime.isOk() && newFrameMarkerPsiSnap.isOk() )
	{
		if ( oldSynchronizeFrameAndPhysicsTime.asBool() == true )
		{
			newFrameMarkerPsiSnap.asReal() = .0001f;
		}
		else
		{
			newFrameMarkerPsiSnap.asReal() = 0;
		}
	}
}

static void CharacterCinfoVersion_440b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	hkClassMemberAccessor newMember(newObj, "contactAngleSensitivity");
	hkClassMemberAccessor oldMember(oldObj, "characterRadius");
	if( newMember.isOk() && oldMember.isOk() )
	{
		newMember.asReal() = oldMember.asReal();
	}
	else
	{
		HK_ASSERT2(0xad7d77de, false, "member not found");
	}
}


class CompatVersionContext
{
	public:


		CompatVersionContext( hkArray<hkVariant>& objectsInOut )
		{
			for (int i = 0; i < objectsInOut.getSize(); ++i )
			{
				m_classFromObject.insert(objectsInOut[i].m_object, objectsInOut[i].m_class);
			}
			extractAllMotionObjects( objectsInOut );
		}

		hkArray<hkVariant>& getUnusedMotions()
		{
			return m_motionObjects;
		}

		const hkClass* findClassFromMotionObject(const void* motionObjectToFind)
		{
			for (int i = 0; i < m_motionObjects.getSize(); ++i)
			{
				if (m_motionObjects[i].m_object == motionObjectToFind)
				{
					const hkClass* klass = m_motionObjects[i].m_class;
					m_motionObjects.removeAt(i);
					return klass;
				}
			}
			HK_ASSERT2(0x1b92e41f, false, "Cannot find referenced motion, may be it is already referenced by another object?");
			return HK_NULL;
		}

		const hkClass* findClassFromOldObject( const void* oldObject )
		{
			return m_classFromObject.getWithDefault(oldObject, HK_NULL);
		}

		static hkBool classIsDerivedFrom(const hkClass* klass, const char* baseName)
		{
			while (klass && hkString::strCmp(klass->getName(), baseName) != 0)
			{
				klass = klass->getParent();
			}
			return klass != HK_NULL;
		}

		hkBool oldObjectIsA(const void* oldObjectToCheck, const char* typeName)
		{
			if( const hkClass* c = findClassFromOldObject(oldObjectToCheck) )
			{
				return classIsDerivedFrom(c, typeName);
			}
			return false;
		}

	private:

		void extractAllMotionObjects(hkArray<hkVariant>& objectsInOut)
		{
			for (int i = 0; i < objectsInOut.getSize();)
			{
				if (classIsDerivedFrom(objectsInOut[i].m_class, "hkMotion"))
				{
					hkVariant& v = m_motionObjects.expandOne();
					v = objectsInOut[i];
					objectsInOut.removeAt(i);
				}
				else
				{
					++i;
				}
			}
		}

		hkPointerMap<const void*, const hkClass*> m_classFromObject;
		hkArray<hkVariant> m_motionObjects;
};

static CompatVersionContext* s_compatVersionContext;

struct SolverResults { float f[2]; };


struct Vector4 : public hkVector4
{
	Vector4(const hkClassMemberAccessor::Vector4& v)
	{
		hkQuadRealUnion u;
		u.r[0] = v.r[0]; u.r[1] = v.r[1]; u.r[2] = v.r[2]; u.r[3] = v.r[3];
		getQuad() = u.q;
	}
};


/*static void setEnumTypeFromName(hkClassMemberAccessor& enumAccessor, const char* typeName)
{
	const hkClassMember& enumMember = enumAccessor.getClassMember();
	const hkClassEnum& enumKlass = enumMember.getEnumClass();
	int value;
	HK_ON_DEBUG(hkResult res = )enumKlass.getValueOfName(typeName, &value);
	HK_ASSERT(0x1b92e41e, res == HK_SUCCESS);
	enumMember.setEnumValue( enumAccessor.getAddress(), value );
}*/

static int getSizeOfAtoms(const hkClassMemberAccessor& newAtoms)
{
	const hkClass& atomClass = newAtoms.object().getClass();
	const hkClassMember& lastMember = atomClass.getMember(atomClass.getNumMembers() - 1);
	return newAtoms.member(lastMember.getName()).getClassMember().getOffset() + lastMember.getStructClass().getObjectSize();
}

static hkInt16 getTypeValueFromEnumName(const hkClassAccessor& memAcc, const char* typeName)
{
	int ret;
	HK_ON_DEBUG(hkResult res = )memAcc.member("type").getClassMember().getEnumClass().getValueOfName(typeName, &ret);
	HK_ASSERT(0x1b92e41e, res == HK_SUCCESS);
	return hkInt16(ret);
}

#define ATOM_TYPE(ATOM, NAME) \
	static hkInt16 NAME = -1; \
	if( NAME == -1 ) NAME = getTypeValueFromEnumName(ATOM,#NAME); \
	ATOM.member("type").asInt16() = NAME

#define ATOM_SIZE( ATOMS, SIZE ) \
	static hkInt16 SIZE = -1; \
	if( SIZE == -1 ) SIZE = (hkInt16)getSizeOfAtoms(ATOMS)

/*
TYPE_HEADER, 
TYPE_MODIFIER_HEADER,

TYPE_BRIDGE, 

TYPE_SET_LOCAL_TRANSFORMS,
TYPE_SET_LOCAL_TRANSLATIONS,
TYPE_SET_LOCAL_ROTATIONS,

TYPE_BALL_SOCKET,
TYPE_STIFF_SPRING,

TYPE_LIN,
TYPE_LIN_SOFT,
TYPE_LIN_LIMIT,
TYPE_LIN_FRICTION, 
TYPE_LIN_MOTOR,

TYPE_2D_ANG,

TYPE_ANG,
TYPE_ANG_LIMIT,
TYPE_TWIST_LIMIT,
TYPE_CONE_LIMIT,
TYPE_ANG_FRICTION,
TYPE_ANG_MOTOR,

TYPE_RAGDOLL_MOTOR,

TYPE_PULLEY,
TYPE_OVERWRITE_PIVOT,

TYPE_CONTACT,

TYPE_MODIFIER_SOFT_CONTACT,
TYPE_MODIFIER_MASS_CHANGER,
TYPE_MODIFIER_VISCOUS_SURFACE,
TYPE_MODIFIER_MOVING_SURFACE,
*/

// Atom ctor-like functions

static void setBridgeAtomData(const hkClassAccessor& bridge, void* constraintData, hkObjectUpdateTracker& tracker)
{
	ATOM_TYPE(bridge, TYPE_BRIDGE);
	hkClassMemberAccessor bridgeConstraintData = bridge.member("constraintData");
	bridgeConstraintData.asPointer() = constraintData;
	//bridge.member("buildJacobianFunc"); initialized in finish constructor
	tracker.objectPointedBy(constraintData, bridgeConstraintData.getAddress());
}

static void setLocalTransformsAtomData(const hkClassAccessor& local,
									   const hkClassMemberAccessor::Transform& transformA,
									   const hkClassMemberAccessor::Transform& transformB )
{
	ATOM_TYPE(local, TYPE_SET_LOCAL_TRANSFORMS);
	local.member("transformA").asTransform() = transformA;
	local.member("transformB").asTransform() = transformB;
}

static void setLocalTranslationsAtomData(const hkClassAccessor& pivots,
										 const hkClassMemberAccessor::Vector4& pivotInA,
										 const hkClassMemberAccessor::Vector4& pivotInB )
{
	ATOM_TYPE(pivots, TYPE_SET_LOCAL_TRANSLATIONS);
	pivots.member("translationA").asVector4() = pivotInA;
	pivots.member("translationB").asVector4() = pivotInB;
}

static void setLocalRotationsAtomData(const hkClassAccessor& rotations,
									  const hkClassMemberAccessor::Rotation& rotationA,
									  const hkClassMemberAccessor::Rotation& rotationB)
{
	ATOM_TYPE(rotations, TYPE_SET_LOCAL_ROTATIONS);
	rotations.member("rotationA").asRotation() = rotationA;
	rotations.member("rotationB").asRotation() = rotationB;
}

static void setBallSocketAtomData(const hkClassAccessor& ballSocket)
{
	ATOM_TYPE(ballSocket, TYPE_BALL_SOCKET);
}

static void setStiffSpringAtomData(const hkClassAccessor& spring, hkReal springLength )
{
	ATOM_TYPE(spring, TYPE_STIFF_SPRING);
	spring.member("length").asReal() = springLength;
}

static void setLinearAtomData(const hkClassAccessor& linear, hkUint8 axisIndex)
{
	ATOM_TYPE(linear, TYPE_LIN);
	linear.member("axisIndex").asUint8() = axisIndex;
}

static void setLinearSoftAtomData(const hkClassAccessor& linearSoft,
								  hkUint8 axisIndex, hkReal tau, hkReal damping)
{
	ATOM_TYPE(linearSoft, TYPE_LIN_SOFT);
	linearSoft.member("axisIndex").asUint8() = axisIndex;
	linearSoft.member("tau").asReal() = tau;
	linearSoft.member("damping").asReal() = damping;
}

static void setLinearLimitAtomData(const hkClassAccessor& linearLimit,
								   hkUint8 axisIndex, hkReal minLimit, hkReal maxLimit)
{
	ATOM_TYPE(linearLimit, TYPE_LIN_LIMIT);
	linearLimit.member("axisIndex").asUint8() = axisIndex;
	linearLimit.member("min").asReal() = minLimit;
	linearLimit.member("max").asReal() = maxLimit;
}

static void setLinearFrictionAtomData(const hkClassAccessor& linearFriction,
									  hkUint8 enabled,
									  hkUint8 frictionAxis,
									  hkReal maxFrictionForce)
{
	ATOM_TYPE(linearFriction, TYPE_LIN_FRICTION);
	linearFriction.member("isEnabled").asUint8() = enabled;
	linearFriction.member("frictionAxis").asUint8() = frictionAxis;
	linearFriction.member("maxFrictionForce").asReal() = maxFrictionForce;
}

static void setLinearMotorAtomData(const hkClassAccessor& linearMotor,
								   hkBool enabled,
								   hkUint8 motorAxis,
								   hkInt16 initializedOffset,
								   hkInt16 previousTargetAngleOffset,
								   hkReal targetPosition,
								   HK_CPU_PTR(class hkConstraintMotor*) motor)
{
	ATOM_TYPE(linearMotor, TYPE_LIN_MOTOR);
	linearMotor.member("isEnabled").asBool() = enabled;
	linearMotor.member("motorAxis").asUint8() = motorAxis;
	linearMotor.member("initializedOffset").asInt16() = initializedOffset;
	linearMotor.member("previousTargetPositionOffset").asInt16() = previousTargetAngleOffset;
	linearMotor.member("targetPosition").asReal() = targetPosition;
	linearMotor.member("motor").asPointer() = motor;
}

static void set2dAngAtomData(const hkClassAccessor& atom2dAng, hkUint8 freeRotationAxis)
{
	ATOM_TYPE(atom2dAng, TYPE_2D_ANG);
	atom2dAng.member("freeRotationAxis").asUint8() = freeRotationAxis;
}

static void setAngAtomData(const hkClassAccessor& angular, hkUint8 firstConstrainedAxis, hkUint8 numConstrainedAxes)
{
	ATOM_TYPE(angular, TYPE_ANG);
	angular.member("firstConstrainedAxis").asUint8() = firstConstrainedAxis;
	angular.member("numConstrainedAxes").asUint8() = numConstrainedAxes;
}

static void setAngLimitAtomData(const hkClassAccessor& angLimit,
								hkUint8 enabled,
								hkUint8 limitAxis,
								hkReal minAngle,
								hkReal maxAngle,
								hkReal angularLimitsTauFactor)
{
	ATOM_TYPE(angLimit, TYPE_ANG_LIMIT);
	angLimit.member("isEnabled").asUint8() = enabled;
	angLimit.member("limitAxis").asUint8() = limitAxis;
	angLimit.member("minAngle").asReal() = minAngle;
	angLimit.member("maxAngle").asReal() = maxAngle;
	angLimit.member("angularLimitsTauFactor").asReal() = angularLimitsTauFactor; // +default(1.0) +absmin(0) +absmax(1)
}

static void setTwistLimitAtomData(const hkClassAccessor& twistLimit,
								  hkUint8 enabled,
								  hkUint8 twistAxis,
								  hkUint8 refAxis,
								  hkReal minAngle,
								  hkReal maxAngle,
								  hkReal angularLimitsTauFactor)
{
	ATOM_TYPE(twistLimit, TYPE_TWIST_LIMIT);
	twistLimit.member("isEnabled").asUint8() = enabled;
	twistLimit.member("twistAxis").asUint8() = twistAxis;
	twistLimit.member("refAxis").asUint8() = refAxis;
	twistLimit.member("minAngle").asReal() = minAngle;
	twistLimit.member("maxAngle").asReal() = maxAngle;
	twistLimit.member("angularLimitsTauFactor").asReal() = angularLimitsTauFactor; // +default(1.0) +absmin(0) +absmax(1)
}

static void setConeLimitAtomData(const hkClassAccessor& coneLimit,
								 hkUint8 enabled,
								 hkUint8 twistAxisInA,
								 hkUint8 refAxisInB,
								 hkUint8 angleMeasurementMode,
								 hkReal minAngle,
								 hkReal maxAngle,
								 hkReal angularLimitsTauFactor)
{
	ATOM_TYPE(coneLimit, TYPE_CONE_LIMIT);
	coneLimit.member("isEnabled").asUint8() = enabled;
	coneLimit.member("twistAxisInA").asUint8() = twistAxisInA;
	coneLimit.member("refAxisInB").asUint8() = refAxisInB;
	coneLimit.member("angleMeasurementMode").asUint8() = angleMeasurementMode;
	coneLimit.member("minAngle").asReal() = minAngle;
	coneLimit.member("maxAngle").asReal() = maxAngle;
	coneLimit.member("angularLimitsTauFactor").asReal() = angularLimitsTauFactor; //+default(1.0) +absmin(0) +absmax(1)
}

static void setAngFrictionAtomData(const hkClassAccessor& angFriction,
								   hkUint8 enabled,
								   hkUint8 firstFrictionAxis,
								   hkUint8 numFrictionAxes,
								   hkReal maxFrictionTorque)
{
	ATOM_TYPE(angFriction, TYPE_ANG_FRICTION);
	angFriction.member("isEnabled").asUint8() = enabled;
	angFriction.member("firstFrictionAxis").asUint8() = firstFrictionAxis;
	angFriction.member("numFrictionAxes").asUint8() = numFrictionAxes;
	angFriction.member("maxFrictionTorque").asReal() = maxFrictionTorque;
}

static void setAngMotorAtomData(const hkClassAccessor& angMotor,
								hkBool enabled,
								hkUint8 motorAxis,
								hkInt16 initializedOffset,
								hkInt16 previousTargetAngleOffset,
								hkInt16 correspondingAngLimitSolverResultOffset,
								hkReal targetAngle,
								HK_CPU_PTR(class hkConstraintMotor*) motor)
{
	ATOM_TYPE(angMotor, TYPE_ANG_MOTOR);
	angMotor.member("isEnabled").asBool() = enabled;
	angMotor.member("motorAxis").asUint8() = motorAxis;
	angMotor.member("initializedOffset").asInt16() = initializedOffset;
	angMotor.member("previousTargetAngleOffset").asInt16() = previousTargetAngleOffset;
	angMotor.member("correspondingAngLimitSolverResultOffset").asInt16() = correspondingAngLimitSolverResultOffset;
	angMotor.member("targetAngle").asReal() = targetAngle;
	angMotor.member("motor").asPointer() = motor;
}

typedef hkClassMemberAccessor::Matrix3 Matrix3;

static void setRagdollMotorAtomData(const hkClassAccessor& ragdollMotor,
									hkBool enabled,
									hkInt16 initializedOffset,
									hkInt16 previousTargetAngleOffset,
									const Matrix3& targetFrameAinB,
									HK_CPU_PTR(class hkConstraintMotor*) motors[3])
{
	ATOM_TYPE(ragdollMotor, TYPE_RAGDOLL_MOTOR);
	ragdollMotor.member("isEnabled").asBool() = enabled;
	ragdollMotor.member("initializedOffset").asInt16() = initializedOffset;
	ragdollMotor.member("previousTargetAnglesOffset").asInt16() = previousTargetAngleOffset;
	ragdollMotor.member("targetFrameAinB").asMatrix3() = targetFrameAinB;

	reinterpret_cast<HK_CPU_PTR(class hkConstraintMotor*)&>(ragdollMotor.member("motors").asPointer(0)) = motors[0];
	reinterpret_cast<HK_CPU_PTR(class hkConstraintMotor*)&>(ragdollMotor.member("motors").asPointer(1)) = motors[1];
	reinterpret_cast<HK_CPU_PTR(class hkConstraintMotor*)&>(ragdollMotor.member("motors").asPointer(2)) = motors[2];
}

static void setPulleyAtomData(const hkClassAccessor& pulley,
							  const hkClassMemberAccessor::Vector4& fixedPivotAinWorld,
							  const hkClassMemberAccessor::Vector4& fixedPivotBinWorld,
							  hkReal ropeLength,
							  hkReal leverageOnBodyB)
{
	ATOM_TYPE(pulley, TYPE_PULLEY);
	pulley.member("fixedPivotAinWorld").asVector4() = fixedPivotAinWorld;
	pulley.member("fixedPivotBinWorld").asVector4() = fixedPivotBinWorld;
	pulley.member("ropeLength").asReal() = ropeLength;
	pulley.member("leverageOnBodyB").asReal() = leverageOnBodyB;
}

// Update functions

static void BallAndSocketConstraintData_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	hkClassMemberAccessor newAtoms(newObj, "atoms");
	hkClassAccessor oldData(oldObj);
	ATOM_SIZE( newAtoms, sizeOfAllAtoms );

	setLocalTranslationsAtomData(
		newAtoms.member("pivots").object(),
		oldData.member("pivotInA").asVector4(),
		oldData.member("pivotInB").asVector4() );
	setBallSocketAtomData(newAtoms.member("ballSocket").object());
}

static void BallSocketChainData_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& tracker )
{
	hkClassMemberAccessor newAtoms(newObj, "atoms");
	ATOM_SIZE( newAtoms, sizeOfAllAtoms );

	setBridgeAtomData(newAtoms.member("bridgeAtom").object(), newObj.m_object, tracker);
}

static void BreakableConstraintData_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& tracker )
{
	hkClassMemberAccessor newAtoms(newObj, "atoms");
	ATOM_SIZE( newAtoms, sizeOfAllAtoms );

	setBridgeAtomData(newAtoms.member("bridgeAtom").object(), newObj.m_object, tracker);
}

static void GenericConstraintData_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& tracker )
{
	hkClassMemberAccessor newAtoms(newObj, "atoms");
	ATOM_SIZE( newAtoms, sizeOfAllAtoms );

	setBridgeAtomData(newAtoms.member("bridgeAtom").object(), newObj.m_object, tracker);
}

static void HingeConstraintData_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	hkClassMemberAccessor newAtoms(newObj, "atoms");
	hkClassAccessor oldData(oldObj);
	ATOM_SIZE( newAtoms, sizeOfAllAtoms );

	hkTransform transformA;
	{
		hkClassAccessor basisA = oldData.member("basisA").object();
		Vector4 perpToAxle1 = basisA.member("perpToAxle1").asVector4();
		Vector4 perpToAxle2 = basisA.member("perpToAxle2").asVector4();
		Vector4 pivot = basisA.member("pivot").asVector4();
		hkVector4 axle; axle.setCross(perpToAxle1, perpToAxle2);
		transformA.getRotation().setCols(axle, perpToAxle1, perpToAxle2);
		transformA.setTranslation( pivot );
	}

	hkTransform transformB;
	{
		hkClassAccessor basisB = oldData.member("basisB").object();
		Vector4 axle = basisB.member("axle").asVector4();
		Vector4 pivot = basisB.member("pivot").asVector4();
		hkVector4Util::buildOrthonormal( axle, transformB.getRotation() );
		transformB.setTranslation( pivot );
	}

	setLocalTransformsAtomData(
		newAtoms.member("transforms").object(),
		(hkClassMemberAccessor::Transform&)transformA,
		(hkClassMemberAccessor::Transform&)transformB);
	set2dAngAtomData(newAtoms.member("2dAng").object(), 0);
	setBallSocketAtomData(newAtoms.member("ballSocket").object());
}

static void HingeLimitsData_400b1_400b2(
										hkVariant& oldObj,
										hkVariant& newObj,
										hkObjectUpdateTracker& )
{
	hkClassMemberAccessor newAtoms(newObj, "atoms");
	hkClassAccessor oldData(oldObj);

	ATOM_SIZE( newAtoms, sizeOfAllAtoms );
	{
		hkClassMemberAccessor::Rotation rotationB;
		hkClassAccessor basisB = oldData.member("basisB").object();

		rotationB.v[0] = basisB.member("axle").asVector4();
		rotationB.v[2] = basisB.member("perp2FreeAxis").asVector4();
		rotationB.v[1].setCross( rotationB.v[2], rotationB.v[0] );
		setLocalRotationsAtomData(newAtoms.member("rotations").object(),
			*static_cast<hkClassMemberAccessor::Rotation*>(oldData.member("basisA").getAddress()),
			rotationB ); 
	}
	setAngLimitAtomData( newAtoms.member("angLimit").object(),
		true, // enabled
		0, // limitAxis
		oldData.member("minAngle").asReal(),
		oldData.member("maxAngle").asReal(), 
		oldData.member("angularLimitsTauFactor").asReal() );
	set2dAngAtomData( newAtoms.member("2dAng").object(), 0);
}

static void MalleableConstraintData_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& tracker )
{
	hkClassMemberAccessor newAtoms(newObj, "atoms");
	hkClassAccessor oldData(oldObj);
	ATOM_SIZE( newAtoms, sizeOfAllAtoms );

	setBridgeAtomData(newAtoms.member("bridgeAtom").object(), newObj.m_object, tracker);
}

static void PointToPathConstraintData_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& tracker )
{
	hkClassMemberAccessor newAtoms(newObj, "atoms");
	hkClassAccessor oldData(oldObj);
	ATOM_SIZE( newAtoms, sizeOfAllAtoms );

	setBridgeAtomData(newAtoms.member("bridgeAtom").object(), newObj.m_object, tracker);
}

static void PointToPlaneConstraintData_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	hkClassMemberAccessor newAtoms(newObj, "atoms");
	hkClassAccessor oldData(oldObj);
	ATOM_SIZE( newAtoms, sizeOfAllAtoms );

	{
		Vector4 pivotInA = oldData.member("pivotInA").asVector4();
		Vector4 pivotInB = oldData.member("pivotInB").asVector4();
		Vector4 planeNormalA = oldData.member("planeNormalA").asVector4();


		hkTransform transformA;
		transformA.setIdentity();
		transformA.setTranslation( pivotInB );

		hkTransform transformB;
		hkVector4Util::buildOrthonormal( planeNormalA, transformB.getRotation() );
		transformB.setTranslation( pivotInA );

		setLocalTransformsAtomData(newAtoms.member("transforms").object(),
			(hkClassMemberAccessor::Transform&)transformA,
			(hkClassMemberAccessor::Transform&)transformB );
	}

	setLinearAtomData( newAtoms.member("lin").object(), 0); 
}

static void PoweredChainData_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& tracker )
{
	hkClassMemberAccessor newAtoms(newObj, "atoms");
	hkClassAccessor oldData(oldObj);
	ATOM_SIZE( newAtoms, sizeOfAllAtoms );

	setBridgeAtomData(newAtoms.member("bridgeAtom").object(), newObj.m_object, tracker);
}

static void RagdollConstraintData_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	hkClassMemberAccessor newAtoms(newObj, "atoms");
	hkClassAccessor oldData(oldObj);
	ATOM_SIZE( newAtoms, sizeOfAllAtoms );

	hkTransform transformA;
	{
		hkClassAccessor basisA = oldData.member("basisA").object();
		Vector4 pivot = basisA.member("pivot").asVector4();
		Vector4 twistAxis = basisA.member("twistAxis").asVector4();
		Vector4 planeAxis = basisA.member("planeAxis").asVector4();
		hkVector4 cross; cross.setCross(twistAxis, planeAxis);
		transformA.getRotation().setCols(twistAxis, planeAxis, cross);
		transformA.setTranslation(pivot);
	}
	hkTransform transformB;
	{
		hkClassAccessor basisB = oldData.member("basisB").object();
		Vector4 pivot = basisB.member("pivot").asVector4();
		Vector4 twistAxis = basisB.member("twistAxis").asVector4();
		Vector4 planeAxis = basisB.member("planeAxis").asVector4();
		hkVector4 cross; cross.setCross(twistAxis, planeAxis);
		transformB.getRotation().setCols(twistAxis, planeAxis, cross);
		transformB.setTranslation(pivot);
	}

	setLocalTransformsAtomData(newAtoms.member("transforms").object(), (hkClassMemberAccessor::Transform&)transformA, (hkClassMemberAccessor::Transform&)transformB);
	HK_ALIGN16( hkClassMemberAccessor::Matrix3 targetFrameAinB ); 
	(hkMatrix3&)targetFrameAinB = transformB.getRotation();
	HK_CPU_PTR(class hkConstraintMotor*) motors[3] = { HK_NULL, HK_NULL, HK_NULL };

	struct Runtime
	{
		HK_ALIGN16( struct SolverResults solverResults[12] );
		hkUint8 initialized[3];
		hkReal previousTargetAngles[3];
	};

	setRagdollMotorAtomData(newAtoms.member("ragdollMotors").object(), 
		false,
		hkInt16(HK_OFFSET_OF(Runtime, initialized[0])), // assuming motors are the first atom
		hkInt16(HK_OFFSET_OF(Runtime, previousTargetAngles[0])), // assuming motors are the first atom
		targetFrameAinB, motors);
	setAngFrictionAtomData(newAtoms.member("angFriction").object(), true, 0, 3,
		oldData.member("maxFrictionTorque").asReal());

	{	// Setup limits
		hkResult res[4];
		int twistAxisIndex;  res[0] = newAtoms.object().getClass().getEnumByName("Axis")->getValueOfName("AXIS_TWIST", &twistAxisIndex);
		int planesAxisIndex; res[1] = newAtoms.object().getClass().getEnumByName("Axis")->getValueOfName("AXIS_PLANES", &planesAxisIndex);
		int zeroWhenAlignedMeasurementMode; res[2] = newAtoms.object().member("coneLimit").object().getClass().getEnumByName("MeasurementMode")->getValueOfName("ZERO_WHEN_VECTORS_ALIGNED", &zeroWhenAlignedMeasurementMode);
		int zeroWhenPerpendicularMeasurementMode; res[3] = newAtoms.object().member("coneLimit").object().getClass().getEnumByName("MeasurementMode")->getValueOfName("ZERO_WHEN_VECTORS_PERPENDICULAR", &zeroWhenPerpendicularMeasurementMode);
		HK_ASSERT2(0xad67d88a, res[0] == HK_SUCCESS && res[1] == HK_SUCCESS && res[2] == HK_SUCCESS && res[3] == HK_SUCCESS, "Enumeration values not extracted properly.");

		setTwistLimitAtomData(newAtoms.member("twistLimit").object(), true, hkUint8(twistAxisIndex), hkUint8(planesAxisIndex), 
			oldData.member("twistMinAngle").asReal(),
			oldData.member("twistMaxAngle").asReal(),
			oldData.member("angularLimitsTauFactor").asReal());
		setConeLimitAtomData(newAtoms.member("coneLimit").object(), true, hkUint8(twistAxisIndex), hkUint8(twistAxisIndex), hkUint8(zeroWhenAlignedMeasurementMode),
			-100.0f,
			oldData.member("coneMinAngle").asReal(),
			oldData.member("angularLimitsTauFactor").asReal());
		setConeLimitAtomData(newAtoms.member("planesLimit").object(), true, hkUint8(twistAxisIndex), hkUint8(planesAxisIndex), hkUint8(zeroWhenPerpendicularMeasurementMode),
			oldData.member("planeMinAngle").asReal(),
			oldData.member("planeMaxAngle").asReal(),
			oldData.member("angularLimitsTauFactor").asReal() );
	}

	setBallSocketAtomData(newAtoms.member("ballSocket").object());
}

static void PoweredRagdollConstraintData_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& tracker )
{
	// parent data first
	RagdollConstraintData_400b1_400b2(oldObj, newObj, tracker);

	hkClassMemberAccessor newAtoms(newObj, "atoms");
	hkClassAccessor newData(newObj);
	hkClassAccessor oldData(oldObj);

	// redo motor and friction

	HK_ALIGN16( hkClassMemberAccessor::Matrix3 targetFrameAinB );
	targetFrameAinB = oldData.member("targetFrameAinB").asMatrix3(); 

	HK_CPU_PTR(class hkConstraintMotor*) motors[3];
	{  
		hkResult res[3];
		int twistMotorIndex; res[0] = newData.getClass().getEnumByName("MotorIndex")->getValueOfName("MOTOR_TWIST", &twistMotorIndex);
		int planeMotorIndex; res[1] = newData.getClass().getEnumByName("MotorIndex")->getValueOfName("MOTOR_PLANE", &planeMotorIndex);
		int coneMotorIndex;  res[2] = newData.getClass().getEnumByName("MotorIndex")->getValueOfName("MOTOR_CONE",  &coneMotorIndex);
		HK_ASSERT2(0xad67dd5a, res[0] == HK_SUCCESS && res[1] == HK_SUCCESS && res[2] == HK_SUCCESS, "Enumeration values not extracted properly.");
		motors[twistMotorIndex] = static_cast<HK_CPU_PTR(class hkConstraintMotor*)>(oldData.member("twistMotor").asPointer());
		motors[planeMotorIndex] = static_cast<HK_CPU_PTR(class hkConstraintMotor*)>(oldData.member("planeMotor").asPointer());
		motors[coneMotorIndex ] = static_cast<HK_CPU_PTR(class hkConstraintMotor*)>(oldData.member( "coneMotor").asPointer());
	}
	struct Runtime
	{
		HK_ALIGN16( struct SolverResults solverResults[12] );
		hkUint8 initialized[3];
		hkReal previousTargetAngles[3];
	};

	hkBool areMotorsActive = oldData.member("motorsActive").asBool();

	setRagdollMotorAtomData(newAtoms.member("ragdollMotors").object(), 
		areMotorsActive,
		hkInt16(HK_OFFSET_OF(Runtime, initialized[0])), // assuming motors are the first atoms with solver results
		hkInt16(HK_OFFSET_OF(Runtime, previousTargetAngles[0])), // assuming motors are the first atoms with solver results
		targetFrameAinB, motors);

	if (newAtoms.member("ragdollMotors").object().member("motors").asPointer(0)) {	tracker.objectPointedBy(newAtoms.member("ragdollMotors").object().member("motors").asPointer(0),                  newAtoms.member("ragdollMotors").object().member("motors").getAddress() );   }
	if (newAtoms.member("ragdollMotors").object().member("motors").asPointer(1)) { tracker.objectPointedBy(newAtoms.member("ragdollMotors").object().member("motors").asPointer(1), hkAddByteOffset( newAtoms.member("ragdollMotors").object().member("motors").getAddress(), 1 * sizeof(hkConstraintMotor*) ) ); }
	if (newAtoms.member("ragdollMotors").object().member("motors").asPointer(2))  { tracker.objectPointedBy(newAtoms.member("ragdollMotors").object().member("motors").asPointer(2), hkAddByteOffset( newAtoms.member("ragdollMotors").object().member("motors").getAddress(), 2 * sizeof(hkConstraintMotor*) ) ); }

	setAngFrictionAtomData(newAtoms.member("angFriction").object(), 
		!areMotorsActive, 0, 3,
		oldData.member("maxFrictionTorque").asReal());

}

static void PrismaticConstraintData_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& tracker)
{
	hkClassMemberAccessor newAtoms(newObj, "atoms");
	hkClassAccessor oldData(oldObj);
	ATOM_SIZE( newAtoms, sizeOfAllAtoms );

	hkTransform transformB;
	{
		hkClassAccessor basisB = oldData.member("basisB").object();
		Vector4 pivotB = basisB.member("pivot").asVector4();
		Vector4 shaftB = basisB.member("shaft").asVector4();
		Vector4 perpToShaftB = basisB.member("perpToShaft").asVector4();
		hkVector4Util::buildOrthonormal(shaftB, perpToShaftB, transformB.getRotation());
		transformB.setTranslation( pivotB );
	}
	hkTransform transformA;
	{
		hkClassAccessor basisA = oldData.member("basisA").object();
		Vector4 pivotA = basisA.member("pivot").asVector4();
		Vector4 shaftA = basisA.member("shaft").asVector4();
		HK_ALIGN16( hkClassMemberAccessor::Rotation aTb );
		aTb = basisA.member("BtoAoffsetRotation").asRotation();

		transformA.getRotation().setMul( (hkMatrix3&)aTb, transformB.getRotation() );
		HK_ON_DEBUG( hkVector4 diff );
		HK_ON_DEBUG( diff.setSub4(shaftA, transformA.getColumn(0)) );
		HK_ASSERT2(0xad88aad7, hkMath::equal( diff.lengthSquared3(), 0.0f ), "Error in converting prismatic constraint.");
		transformA.setTranslation( pivotA );
	}
	setLocalTransformsAtomData(newAtoms.member("transforms").object(), 
								(hkClassMemberAccessor::Transform&)transformA,
								(hkClassMemberAccessor::Transform&)transformB);

	struct Runtime
	{
		struct SolverResults solverResults[8];
		hkUint8 initialized;
		hkReal previousTargetPosition;
	};
	hkBool isMotorActive = ( HK_NULL != oldData.member("motor").asPointer() );
	setLinearMotorAtomData(newAtoms.member("motor").object(),
							isMotorActive,
							0,
							HK_OFFSET_OF(Runtime,initialized), // assuming motors are the first atom !!!
							HK_OFFSET_OF(Runtime,previousTargetPosition), // assuming motors are the first atom !!!
							oldData.member("motorTargetPosition").asReal(),
							static_cast<HK_CPU_PTR(class hkConstraintMotor*)>(oldData.member("motor").asPointer()) );
	if (newAtoms.member("motor").object().member("motor").asPointer())
	{
		tracker.objectPointedBy(newAtoms.member("motor").object().member("motor").asPointer(), newAtoms.member("motor").object().member("motor").getAddress() );
	}

	setLinearFrictionAtomData(newAtoms.member("friction").object(), !isMotorActive, 0,
		oldData.member("maxFrictionForce").asReal());
	setAngAtomData(newAtoms.member("ang").object(), 0, 3);
	setLinearAtomData(newAtoms.member("lin0").object(), 1); 
	setLinearAtomData(newAtoms.member("lin1").object(), 2);
	setLinearLimitAtomData(newAtoms.member("linLimit").object(),
		0,
		oldData.member("minLimit").asReal(),
		oldData.member("maxLimit").asReal());
}

static void PulleyConstraintData_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	hkClassMemberAccessor newAtoms(newObj, "atoms");
	hkClassAccessor oldData(oldObj);
	ATOM_SIZE( newAtoms, sizeOfAllAtoms );

	setLocalTranslationsAtomData(
		newAtoms.member("translations").object(),
		oldData.member("pivotInA").asVector4(),
		oldData.member("pivotInB").asVector4() );
	setPulleyAtomData(newAtoms.member("pulley").object(),
		oldData.member("pulleyPivotAinWorld").asVector4(),
		oldData.member("pulleyPivotBinWorld").asVector4(),
		oldData.member("ropeLength").asReal(),
		oldData.member("leverageOnBodyB").asReal() );
}

static void RagdollLimitsData_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	hkClassMemberAccessor newAtoms(newObj, "atoms");
	hkClassAccessor oldData(oldObj);
	ATOM_SIZE( newAtoms, sizeOfAllAtoms );

	hkRotation rotationA;
	{
		hkClassAccessor basisA = oldData.member("basisA").object();
		Vector4 twistAxis = basisA.member("twistAxis").asVector4();
		Vector4 planeAxis = basisA.member("planeAxis").asVector4();
		hkVector4 cross; cross.setCross(twistAxis, planeAxis);
		rotationA.setCols(twistAxis, planeAxis, cross);
	}
	hkRotation rotationB;
	{
		hkClassAccessor basisB = oldData.member("basisB").object();
		Vector4 twistAxis = basisB.member("twistAxis").asVector4();
		Vector4 planeAxis = basisB.member("planeAxis").asVector4();
		hkVector4 cross; cross.setCross(twistAxis, planeAxis);
		rotationB.setCols(twistAxis, planeAxis, cross);
	}

	setLocalRotationsAtomData(newAtoms.member("rotations").object(), (hkClassMemberAccessor::Rotation&)rotationA, (hkClassMemberAccessor::Rotation&)rotationB);

	{	// Setup limits
		hkResult res[4];
		int twistAxisIndex;  res[0] = newAtoms.object().getClass().getEnumByName("Axis")->getValueOfName("AXIS_TWIST", &twistAxisIndex);
		int planesAxisIndex; res[1] = newAtoms.object().getClass().getEnumByName("Axis")->getValueOfName("AXIS_PLANES", &planesAxisIndex);
		int zeroWhenAlignedMeasurementMode; res[2] = newAtoms.object().member("coneLimit").object().getClass().getEnumByName("MeasurementMode")->getValueOfName("ZERO_WHEN_VECTORS_ALIGNED", &zeroWhenAlignedMeasurementMode);
		int zeroWhenPerpendicularMeasurementMode; res[3] = newAtoms.object().member("coneLimit").object().getClass().getEnumByName("MeasurementMode")->getValueOfName("ZERO_WHEN_VECTORS_PERPENDICULAR", &zeroWhenPerpendicularMeasurementMode);
		HK_ASSERT2(0xad67d88a, res[0] == HK_SUCCESS && res[1] == HK_SUCCESS && res[2] == HK_SUCCESS && res[3] == HK_SUCCESS, "Enumeration values not extracted properly.");

		setTwistLimitAtomData(newAtoms.member("twistLimit").object(), true, hkUint8(twistAxisIndex), hkUint8(planesAxisIndex), 
			oldData.member("twistMinAngle").asReal(),
			oldData.member("twistMaxAngle").asReal(),
			oldData.member("angularLimitsTauFactor").asReal());
		setConeLimitAtomData(newAtoms.member("coneLimit").object(), true, hkUint8(twistAxisIndex), hkUint8(twistAxisIndex), hkUint8(zeroWhenAlignedMeasurementMode),
			-100.0f,
			oldData.member("coneMinAngle").asReal(),
			oldData.member("angularLimitsTauFactor").asReal());
		setConeLimitAtomData(newAtoms.member("planesLimit").object(), true, hkUint8(twistAxisIndex), hkUint8(planesAxisIndex), hkUint8(zeroWhenPerpendicularMeasurementMode),
			oldData.member("planeMinAngle").asReal(),
			oldData.member("planeMaxAngle").asReal(),
			oldData.member("angularLimitsTauFactor").asReal() );
	}

}

static void StiffSpringChainData_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& tracker )
{
	hkClassMemberAccessor newAtoms(newObj, "atoms");
	hkClassAccessor oldData(oldObj);
	ATOM_SIZE( newAtoms, sizeOfAllAtoms );

	setBridgeAtomData(newAtoms.member("bridgeAtom").object(), newObj.m_object, tracker);
}

static void StiffSpringConstraintData_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	hkClassMemberAccessor newAtoms(newObj, "atoms");
	hkClassAccessor oldData(oldObj);
	ATOM_SIZE(newAtoms, sizeOfAllAtoms);

	setLocalTranslationsAtomData(
		newAtoms.member("pivots").object(),
		oldData.member("pivotInA").asVector4(),
		oldData.member("pivotInB").asVector4() );
	setStiffSpringAtomData(newAtoms.member("spring").object(), oldData.member("springLength").asReal() );
}

static void WheelConstraintData_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	hkClassMemberAccessor newAtoms(newObj, "atoms");
	hkClassAccessor newData(newObj);
	hkClassAccessor oldData(oldObj);
	ATOM_SIZE( newAtoms, sizeOfAllAtoms );

	hkTransform transformA; 
	{
		hkClassAccessor basisA = oldData.member("basisA").object();
		Vector4 pivot = basisA.member("pivot").asVector4();
		transformA.getRotation().setIdentity();
		transformA.setTranslation( pivot );
	}
	hkTransform transformB;
	{
		hkClassAccessor basisB = oldData.member("basisB").object();
		Vector4 pivot = basisB.member("pivot").asVector4();
		Vector4 suspensionAxis  = basisB.member("suspensionAxis" ).asVector4();

		hkVector4Util::buildOrthonormal(suspensionAxis, transformB.getRotation());
		transformB.setTranslation(pivot);
	}

	setLocalTransformsAtomData(newAtoms.member("suspensionBase").object(), (hkClassMemberAccessor::Transform&)transformA, (hkClassMemberAccessor::Transform&)transformB);
	setLinearLimitAtomData(newAtoms.member("lin0Limit").object(), 0,
		oldData.member("suspensionMinLimit").asReal(),
		oldData.member("suspensionMaxLimit").asReal());
	setLinearSoftAtomData(newAtoms.member("lin0Soft").object(), 0, oldData.member("suspensionStrength").asReal(), oldData.member("suspensionDamping").asReal());
	setLinearAtomData(newAtoms.member("lin1").object(), 1);
	setLinearAtomData(newAtoms.member("lin2").object(), 2);
	hkRotation rotationA;
	{
		hkClassAccessor basisA = oldData.member("basisA").object();
		Vector4 axle  = basisA.member("axle" ).asVector4();
		hkVector4Util::buildOrthonormal(axle, rotationA);
	}
	hkRotation rotationB;
	{
		hkClassAccessor basisB = oldData.member("basisB").object();
		Vector4 referenceAxle  = basisB.member("referenceAxle" ).asVector4();
		Vector4 steeringAxis   = basisB.member("steeringAxis" ).asVector4();
		reinterpret_cast<Vector4&>(newData.member("initialAxleInB").asVector4()) = referenceAxle;
		reinterpret_cast<Vector4&>(newData.member("initialSteeringAxisInB").asVector4()) = steeringAxis;

		HK_ASSERT2(0xad78dd9a, hkMath::equal( referenceAxle.dot3(steeringAxis), 0), "Error when versioning wheel constraint: Wheel axle and steering axis must be perpendicular.");

		hkVector4Util::buildOrthonormal(referenceAxle, steeringAxis, rotationB);
	}
	setLocalRotationsAtomData(newAtoms.member("steeringBase").object(), (hkClassMemberAccessor::Rotation&)rotationA, (hkClassMemberAccessor::Rotation&)rotationB);
	set2dAngAtomData(newAtoms.member("2dAng").object(), 0);
}

static void ConstraintMotor_400b1_400b2(
										hkVariant& oldObj,
										hkVariant& newObj,
										hkObjectUpdateTracker& )
{
	const char* motorType;
	if( CompatVersionContext::classIsDerivedFrom(oldObj.m_class,"hkSpringDamperConstraintMotor") )
	{
		motorType = "TYPE_SPRING_DAMPER";
	}
	else if( CompatVersionContext::classIsDerivedFrom(oldObj.m_class,"hkVelocityConstraintMotor") )
	{
		motorType = "TYPE_VELOCITY";
	}
	else if( CompatVersionContext::classIsDerivedFrom(oldObj.m_class,"hkPositionConstraintMotor") )
	{
		motorType = "TYPE_POSITION";
	}
	else
	{
		HK_ASSERT(0x751be2e2, 0);
		motorType = "TYPE_INVALID";
	}
	hkClassMemberAccessor(newObj, "type").asInt8() = hkInt8(getTypeValueFromEnumName(hkClassAccessor(newObj), motorType));
}

static void LimitedHingeConstraintData_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& )
{
	hkClassMemberAccessor newAtoms(newObj, "atoms");
	hkClassAccessor oldData(oldObj);
	ATOM_SIZE( newAtoms, sizeOfAllAtoms );

	hkClassMemberAccessor::Transform transformA;
	{
		hkClassAccessor basisA = oldData.member("basisA").object();
		transformA.r[0] = basisA.member("axle").asVector4();
		transformA.r[1] = basisA.member("perpToAxle1").asVector4();
		transformA.r[2] = basisA.member("perpToAxle2").asVector4();
		transformA.t = basisA.member("pivot").asVector4();
	}
	hkClassMemberAccessor::Transform transformB;
	{
		hkClassAccessor basisB = oldData.member("basisB").object();
		transformB.r[0] = basisB.member("axle").asVector4();
		transformB.r[2] = basisB.member("perp2FreeAxis").asVector4();
		transformB.r[1].setCross( transformB.r[2], transformB.r[0] );
		transformB.t = basisB.member("pivot").asVector4();
	}
	setLocalTransformsAtomData(newAtoms.member("transforms").object(), transformA, transformB);

	struct Runtime
	{
		HK_ALIGN16( struct SolverResults solverResults[8] );
		hkUint8 initialized;
		hkReal previousTargetAngle;
	};
	setAngMotorAtomData(newAtoms.member("angMotor").object(),
		0,
		0,
		HK_OFFSET_OF(Runtime, initialized), // assuming the motor atoms is the first one with solver results
		HK_OFFSET_OF(Runtime, previousTargetAngle), // assuming the motor atoms is the first one with solver results
		2 * sizeof(SolverResults),
		0.0f,
		HK_NULL);

	setAngFrictionAtomData( newAtoms.member("angFriction").object(), 1, 0, 1, oldData.member("maxFrictionTorque").asReal() );
	setAngLimitAtomData (newAtoms.member("angLimit").object(), 1, 0, oldData.member("minAngle").asReal(), oldData.member("maxAngle").asReal(), oldData.member("angularLimitsTauFactor").asReal() );
	set2dAngAtomData(newAtoms.member("2dAng").object(), 0);
	setBallSocketAtomData(newAtoms.member("ballSocket").object() );
}

static void PoweredHingeConstraintData_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& tracker)
{
	LimitedHingeConstraintData_400b1_400b2(oldObj, newObj, tracker);

	hkClassMemberAccessor newAtoms(newObj, "atoms");
	hkClassAccessor oldData(oldObj);

	struct Runtime
	{
		HK_ALIGN16( struct SolverResults solverResults[8] );
		hkUint8 initialized;
		hkReal previousTargetAngle;
	};

	hkBool isMotorActive = oldData.member("motorActive").asBool() && (HK_NULL != oldData.member("motor").asPointer());
	setAngMotorAtomData(newAtoms.member("angMotor").object(),
						isMotorActive,
						0,
						HK_OFFSET_OF(Runtime, initialized), // assuming the motor atom is the first one with solver results
						HK_OFFSET_OF(Runtime, previousTargetAngle), // assuming the motor atom is the first one with solver results
						2 * sizeof(SolverResults),
						oldData.member("targetAngle").asReal(),
						static_cast<HK_CPU_PTR(hkConstraintMotor*)>( oldData.member("motor").asPointer() ) );
	if (oldData.member("motor").asPointer())
	{
		tracker.objectPointedBy(newAtoms.member("angMotor").object().member("motor").asPointer(), newAtoms.member("angMotor").object().member("motor").getAddress() );
	}

	setAngFrictionAtomData(newAtoms.member("angFriction").object(), 
		! isMotorActive, 
		0,
		1,
		oldData.member("maxFrictionTorque").asReal() );

	setAngLimitAtomData(newAtoms.member("angLimit").object(),
						true,
						0,
						oldData.member("ignoreLimits").asBool() ? -1e14f : oldData.member("minAngle").asReal(),
						oldData.member("ignoreLimits").asBool() ?  1e14f : oldData.member("maxAngle").asReal(), 
						oldData.member("angularLimitsTauFactor").asReal()
						);

}

static void ConstraintInstance_400b1_400b2(
	hkVariant& oldObj,
	hkVariant& newObj,
	hkObjectUpdateTracker& tracker)
{
	hkClassAccessor newInstance(newObj);
	hkClassAccessor oldInstance(oldObj);

	const void* oldData = oldInstance.member("data").asPointer();
	if (s_compatVersionContext->oldObjectIsA(oldData,"hkPointToPlaneConstraintData"))
	{
		tracker.objectPointedBy(oldInstance.member("entities").asPointer(1), newInstance.member("entities").getAddress() );
		tracker.objectPointedBy(oldInstance.member("entities").asPointer(0), hkAddByteOffset( newInstance.member("entities").getAddress(), sizeof(void*) ) );
	}
}



static hkUint8 MotionTypeFromClassName(const char* className, const hkClassEnum& motionEnum )
{
	struct Pair { const char* className; const char* enumName; };
	const Pair table[] =
	{
		{"hkSphereMotion", "MOTION_SPHERE_INERTIA"},
		{"hkStabilizedSphereMotion", "MOTION_STABILIZED_SPHERE_INERTIA"},
		{"hkBoxMotion", "MOTION_BOX_INERTIA"},
		{"hkStabilizedBoxMotion", "MOTION_STABILIZED_BOX_INERTIA"},
		{"hkKeyframedRigidMotion", "MOTION_KEYFRAMED"},
		{"hkFixedRigidMotion", "MOTION_FIXED"},
		{"hkThinBoxMotion", "MOTION_THIN_BOX_INERTIA"},
		{HK_NULL, HK_NULL}
	};
	const char* enumName = "MOTION_INVALID";
	for( int i = 0; table[i].className != HK_NULL; ++i )
	{
		if( hkString::strCmp(table[i].className, className) == 0 )
		{
			enumName = table[i].enumName;
			break;
		}
	}
	int val = 0;
	motionEnum.getValueOfName(enumName, &val);
	HK_ASSERT2(0x23107483, val != 0,"Unrecognised motion type " << className );
	return hkUint8(val);
}

static void CopySimpleMembers( const hkClassAccessor& newClassAcc, const hkClassAccessor& oldClassAcc )
{
	const hkClass& newClass = newClassAcc.getClass();
	const hkClass& oldClass = oldClassAcc.getClass();
	for( int memberIdx = 0; memberIdx < newClass.getNumMembers(); ++memberIdx )
	{
		const hkClassMember& newMember = newClass.getMember( memberIdx );

		if( const hkClassMember* oldMemberPtr = oldClass.getMemberByName( newMember.getName() ) )
		{
			const hkClassMember& oldMember = *oldMemberPtr;

			if( newMember.getType() == oldMember.getType()
				&& newMember.getSubType() == oldMember.getSubType()
				&& newMember.getSizeInBytes() == oldMember.getSizeInBytes() )
			{
				hkClassMemberAccessor newMemberAcc = newClassAcc.member(&newMember);
				hkClassMemberAccessor oldMemberAcc = oldClassAcc.member(&oldMember);

				switch( newMember.getType() )
				{
				case hkClassMember::TYPE_BOOL:
				case hkClassMember::TYPE_CHAR:
				case hkClassMember::TYPE_INT8:
				case hkClassMember::TYPE_UINT8:
				case hkClassMember::TYPE_INT16:
				case hkClassMember::TYPE_UINT16:
				case hkClassMember::TYPE_INT32:
				case hkClassMember::TYPE_UINT32:
				case hkClassMember::TYPE_INT64:
				case hkClassMember::TYPE_UINT64:
				case hkClassMember::TYPE_REAL:
				case hkClassMember::TYPE_VECTOR4:
				case hkClassMember::TYPE_QUATERNION:
				case hkClassMember::TYPE_MATRIX3:
				case hkClassMember::TYPE_ROTATION:
				case hkClassMember::TYPE_QSTRANSFORM:
				case hkClassMember::TYPE_MATRIX4:
				case hkClassMember::TYPE_TRANSFORM:
				case hkClassMember::TYPE_ENUM:
					{
						hkString::memCpy(newMemberAcc.getAddress(), oldMemberAcc.getAddress(), newMember.getSizeInBytes() );
						break;
					}
				case hkClassMember::TYPE_ZERO:
					{
						break;
					}
				case hkClassMember::TYPE_STRUCT:
					{
						CopySimpleMembers( newMemberAcc.object(), oldMemberAcc.object() );
						break;
					}
				default:
					{
						HK_ASSERT(0,0);
					}
				}
			}
		}
	}
}

static void Motion_400b1_400b2(
									 hkVariant& oldObj,
									 hkVariant& newObj,
									 hkObjectUpdateTracker& tracker)
{
	hkClassAccessor newMotion(newObj);
	hkClassAccessor oldMotion(oldObj);
	const hkClass* oldMotionClass = oldObj.m_class;
	{ // type
		hkClassMemberAccessor newType = newMotion.member("type");
		newType.asUint8() = MotionTypeFromClassName(oldMotionClass->getName(), newType.getClassMember().getEnumClass() );
	}
	{ // motionstate
		hkClassMemberAccessor oldState = oldMotion.member("motionState");
		hkClassMemberAccessor newState = newMotion.member("motionState");
		CopySimpleMembers( newState.object(), oldState.object() );
		newState.member("linearDamping").asReal() = oldMotion.member("linearDamping").asReal();
		newState.member("angularDamping").asReal() = oldMotion.member("angularDamping").asReal();
	}
	{ // inertiaAndMassInv
		if(	hkString::strCmp("hkBoxMotion", oldMotionClass->getName()) == 0 || 
			hkString::strCmp("hkStabilizedBoxMotion", oldMotionClass->getName()) == 0 ||
			hkString::strCmp("hkThinBoxMotion", oldMotionClass->getName()) == 0 )
		{
			newMotion.member("inertiaAndMassInv").asVector4() = oldMotion.member("inertiaAndMassInv").asVector4();
		}
		else
		{
			hkClassMemberAccessor::Vector4 newInertiaAndMassInv;
			newInertiaAndMassInv.r[0] = oldMotion.member("particleMinInertiaDiagInv").asReal();
			newInertiaAndMassInv.r[1] = newInertiaAndMassInv.r[0];
			newInertiaAndMassInv.r[2] = newInertiaAndMassInv.r[0];
			newInertiaAndMassInv.r[3] = oldMotion.member("massInv").asReal();
			newMotion.member("inertiaAndMassInv").asVector4() = newInertiaAndMassInv;
		}
	}
	{ // lin/ang vel
		newMotion.member("linearVelocity").asVector4() = oldMotion.member("linearVelocity").asVector4();
		newMotion.member("angularVelocity").asVector4() = oldMotion.member("angularVelocity").asVector4();
	}
}

static void Entity_400b1_400b2(
							   hkVariant& oldObj,
							   hkVariant& newObj,
							   hkObjectUpdateTracker& tracker)
{
	hkClassMemberAccessor oldMotionMember(oldObj, "motion");
	void* oldMotionPtr = oldMotionMember.asPointer();
	const hkClass* oldMotionClass = s_compatVersionContext->findClassFromMotionObject(oldMotionPtr);
	if( oldMotionClass != HK_NULL )
	{
		hkClassMemberAccessor newMotion(newObj, "motion");
		hkVariant newMotionVariant = {newMotion.object().getAddress(), &newMotion.object().getClass()};
		hkVariant oldMotionVariant = {oldMotionPtr, oldMotionClass};
		Motion_400b1_400b2(oldMotionVariant, newMotionVariant, tracker);
		tracker.replaceObject( oldMotionPtr, HK_NULL, HK_NULL );
	}
}

#define REMOVED(TYPE) { 0,0, hkVersionUtil::VERSION_REMOVED, TYPE, HK_NULL }
#define BINARY_IDENTICAL(OLDSIG,NEWSIG,TYPE) { OLDSIG, NEWSIG, hkVersionUtil::VERSION_MANUAL, TYPE, HK_NULL }

namespace hkCompat_hk400b1_hk400b2
{

hkVersionUtil::ClassAction UpdateActions[] =
{
	//physics
	{ 0x4bcc8a37, 0x804c9b06, hkVersionUtil::VERSION_COPY, "hkWorldCinfo", WorldCinfoVersion_400b1_400b2 }, // several members changed, simulation type
	{ 0x8e3d544b, 0x4c1e648e, hkVersionUtil::VERSION_COPY, "hkCharacterProxyCinfo", CharacterCinfoVersion_440b1_400b2 },

	// vehicle
	{ 0x037ed0ee, 0x82fe40e0, hkVersionUtil::VERSION_COPY, "hkVehicleDataWheelComponentParams", HK_NULL }, // added slipAngle
	{ 0xad76bdca, 0xd6ea9f63, hkVersionUtil::VERSION_COPY, "hkVehicleData", HK_NULL }, // WheelComponentParams

	REMOVED("hkTriPatchTriangle"),
	REMOVED("hkHingeConstraintDataConstraintBasisA"),
	REMOVED("hkHingeConstraintDataConstraintBasisB"),
	REMOVED("hkHingeLimitsDataConstraintBasisA"),
	REMOVED("hkHingeLimitsDataConstraintBasisB"),
	REMOVED("hkLimitedHingeConstraintDataConstraintBasisA"),
	REMOVED("hkLimitedHingeConstraintDataConstraintBasisB"),
	REMOVED("hkPrismaticConstraintDataConstraintBasisA"),
	REMOVED("hkPrismaticConstraintDataConstraintBasisB"),
	REMOVED("hkRagdollConstraintDataConstraintBasisA"),
	REMOVED("hkRagdollConstraintDataConstraintBasisB"),
	REMOVED("hkRagdollLimitsDataConstraintBasisA"),
	REMOVED("hkRagdollLimitsDataConstraintBasisB"),
	REMOVED("hkRelativeOrientationConstraintData"),
	REMOVED("hkWheelConstraintDataConstraintBasisA"),
	REMOVED("hkWheelConstraintDataConstraintBasisB"),

	{ 0x8cfd83a5, 0x583131f8, hkVersionUtil::VERSION_COPY, "hkBallAndSocketConstraintData", BallAndSocketConstraintData_400b1_400b2 },
	{ 0xb95c56e9, 0x6286c3ed, hkVersionUtil::VERSION_COPY, "hkBallSocketChainData", BallSocketChainData_400b1_400b2 },
	{ 0x5e46058f, 0x816f4533, hkVersionUtil::VERSION_COPY, "hkBreakableConstraintData", BreakableConstraintData_400b1_400b2 },
	{ 0x50520e7d, 0x2d0d9c11, hkVersionUtil::VERSION_COPY, "hkConstraintInstance", ConstraintInstance_400b1_400b2 },
	{ 0x78e48550, 0x1abb6f60, hkVersionUtil::VERSION_COPY, "hkGenericConstraintData", GenericConstraintData_400b1_400b2 },
	{ 0x32ca9356, 0xeff16a0e, hkVersionUtil::VERSION_COPY, "hkHingeConstraintData", HingeConstraintData_400b1_400b2 },
	{ 0xc6b7095b, 0xd9510bde, hkVersionUtil::VERSION_COPY, "hkPoweredHingeConstraintData", PoweredHingeConstraintData_400b1_400b2 },
	{ 0xc0567fcb, 0xd9510bde, hkVersionUtil::VERSION_COPY, "hkLimitedHingeConstraintData", LimitedHingeConstraintData_400b1_400b2 },
	{ 0x6c9bb90f, 0xa61d656d, hkVersionUtil::VERSION_COPY, "hkHingeLimitsData", HingeLimitsData_400b1_400b2 },
	{ 0x8a7d73d8, 0xa80474ce, hkVersionUtil::VERSION_COPY, "hkMalleableConstraintData", MalleableConstraintData_400b1_400b2 },
	{ 0xc9d61d09, 0x8907e64c, hkVersionUtil::VERSION_COPY, "hkPointToPathConstraintData", PointToPathConstraintData_400b1_400b2 },
	{ 0x6d93acbf, 0x01a5a929, hkVersionUtil::VERSION_COPY, "hkPointToPlaneConstraintData", PointToPlaneConstraintData_400b1_400b2 },
	{ 0x86a24d53, 0xd0ffea9e, hkVersionUtil::VERSION_COPY, "hkPoweredChainData", PoweredChainData_400b1_400b2 },
	{ 0x8ae97a88, 0xe9717697, hkVersionUtil::VERSION_COPY, "hkPrismaticConstraintData", PrismaticConstraintData_400b1_400b2 },
	{ 0x519f80c6, 0x2c1d380b, hkVersionUtil::VERSION_COPY, "hkPulleyConstraintData", PulleyConstraintData_400b1_400b2 },
	{ 0xa4c8a325, 0x6cccbc01, hkVersionUtil::VERSION_COPY, "hkPoweredRagdollConstraintData", PoweredRagdollConstraintData_400b1_400b2 },
	{ 0x6bf721fa, 0x6cccbc01, hkVersionUtil::VERSION_COPY, "hkRagdollConstraintData", RagdollConstraintData_400b1_400b2 },
	{ 0xca988c50, 0x95be515b, hkVersionUtil::VERSION_COPY, "hkRagdollLimitsData", RagdollLimitsData_400b1_400b2 },
	{ 0x8529098a, 0x4fca7e0a, hkVersionUtil::VERSION_COPY, "hkStiffSpringChainData", StiffSpringChainData_400b1_400b2 },
	{ 0xf8227619, 0x8944ddfa, hkVersionUtil::VERSION_COPY, "hkStiffSpringConstraintData", StiffSpringConstraintData_400b1_400b2 },
	{ 0xc8243370, 0x78fca979, hkVersionUtil::VERSION_COPY, "hkWheelConstraintData", WheelConstraintData_400b1_400b2 },
	{ 0x82ef3c01, 0x27169465, hkVersionUtil::VERSION_COPY, "hkConstraintMotor", ConstraintMotor_400b1_400b2 },
	{ 0xde4be9fc, 0xf28ab3b7, hkVersionUtil::VERSION_COPY, "hkConstraintData", HK_NULL }, // added 

	// motionstate
	{ 0x0a3b3785, 0x332f16fa, hkVersionUtil::VERSION_COPY, "hkMotionState", HK_NULL }, // ang/lin damping added
	{ 0x33fff789, 0x73c94d9b, hkVersionUtil::VERSION_COPY, "hkShapePhantom", HK_NULL }, // contains a motionstate

	// motion
	{ 0xb68fb987, 0x9f0bf6ee, hkVersionUtil::VERSION_COPY, "hkBoxMotion", Motion_400b1_400b2 }, // no members
	{ 0x10e3bfce, 0x27f50bfa, hkVersionUtil::VERSION_COPY, "hkKeyframedRigidMotion", Motion_400b1_400b2 }, //
	{ 0xe6f30c22, 0x9f0bf6ee, hkVersionUtil::VERSION_COPY, "hkSphereMotion", Motion_400b1_400b2 }, //
	REMOVED("hkRigidMotion"), // in fact, renamed to hkMotion
	{ 0x953b00d8, 0x179f1a0b, hkVersionUtil::VERSION_COPY, "hkMotion", Motion_400b1_400b2 }, // members pushed up to base class
	{ 0x1c1ff493, 0xfce98414, hkVersionUtil::VERSION_COPY, "hkEntity", Entity_400b1_400b2 }, // motion moved inside, fixed flags removed

	{ 0x8bdd3e9a, 0x8bdd3e9a, hkVersionUtil::VERSION_VARIANT, "hkBoneAttachment", HK_NULL },
	{ 0xf598a34e, 0xf598a34e, hkVersionUtil::VERSION_VARIANT, "hkRootLevelContainer", HK_NULL },
	{ 0x853a899c, 0x853a899c, hkVersionUtil::VERSION_VARIANT, "hkRootLevelContainerNamedVariant", HK_NULL }, 
	{ 0x3d43489c, 0x3d43489c, hkVersionUtil::VERSION_VARIANT, "hkxMaterial", HK_NULL },
	{ 0x914da6c1, 0x914da6c1, hkVersionUtil::VERSION_VARIANT, "hkxAttribute", HK_NULL },
	{ 0x1667c01c, 0x1667c01c, hkVersionUtil::VERSION_VARIANT, "hkxAttributeGroup", HK_NULL }, 
	{ 0x0a62c79f, 0x0a62c79f, hkVersionUtil::VERSION_VARIANT, "hkxNode", HK_NULL }, 
	{ 0xe085ba9f, 0xe085ba9f, hkVersionUtil::VERSION_VARIANT, "hkxMaterialTextureStage", HK_NULL },

	BINARY_IDENTICAL(0xfee60709, 0xf2a92154, "hkPackfileSectionHeader"),

	// hkbehavior classes
	// We assume that nobody could have serialized anything using beta 1 so just make it compile nicely.

	{ 0xbe368383, 0x6a48b9cc, hkVersionUtil::VERSION_COPY, "hkbBlendingTransition", HK_NULL },
	{ 0xdbc8239b, 0x854b920e, hkVersionUtil::VERSION_COPY, "hkbPoweredRagdollModifier", HK_NULL },
	{ 0x6df0560c, 0x0015833d, hkVersionUtil::VERSION_COPY, "hkbRigidBodyRagdollModifier", HK_NULL },
	{ 0xd53589db, 0xa435f17d, hkVersionUtil::VERSION_COPY, "hkbStateMachine", HK_NULL },
	{ 0x635bd2ce, 0x0d44f6e7, hkVersionUtil::VERSION_COPY, "hkbVariableSetTarget", HK_NULL },
	{ 0x1985ec3f, 0xd776a823, hkVersionUtil::VERSION_COPY, "hkbVariableSet", HK_NULL }, // m_variables member copies (hkbVariableSetVariable)
	{ 0x98c8f7df, 0x6164be0e, hkVersionUtil::VERSION_COPY, "hkbVariableSetVariable", HK_NULL }, // m_targets member copies (hkbVariableSetTarget)
	REMOVED("hkbRigidBodyRagdollModifierControlData"),
	REMOVED("hkbSharedModifier"),
	REMOVED("hkbSharedGenerator"),

	{ 0,0, 0, HK_NULL, HK_NULL }
};

static hkVersionUtil::ClassRename renames[] =
{
	//{ "hkRigidMotion", "hkMotion" },
	{ "hkPoweredHingeConstraintData", "hkLimitedHingeConstraintData" },
	{ "hkPoweredRagdollConstraintData", "hkRagdollConstraintData" },
	{ HK_NULL, HK_NULL }
};

extern const hkVersionUtil::UpdateDescription hkVersionUpdateDescription;
const hkVersionUtil::UpdateDescription hkVersionUpdateDescription =
{
	renames,
	UpdateActions,
	&hkHavok400b2ClassList
};


static hkResult HK_CALL update(
	hkArray<hkVariant>& objectsInOut,
	hkObjectUpdateTracker& tracker )
{
	CompatVersionContext context(objectsInOut);
	s_compatVersionContext = &context;
	hkResult res = hkVersionUtil::updateSingleVersion( objectsInOut, tracker, hkVersionUpdateDescription );
	s_compatVersionContext = HK_NULL;

	if (res == HK_SUCCESS)
	{
		// version motions which have not moved into entities.
		hkArray<hkVariant>& motionsInOut = context.getUnusedMotions();
		res = hkVersionUtil::updateSingleVersion( motionsInOut, tracker, hkVersionUpdateDescription );
		hkVariant* motions = objectsInOut.expandBy(motionsInOut.getSize());
		for (int i = 0; i < motionsInOut.getSize(); ++i)
		{
			motions[i] = motionsInOut[i];
		}
	}
	
	return res;
}

extern const hkVersionRegistry::Updater hkVersionUpdater;
const hkVersionRegistry::Updater hkVersionUpdater =
{
	hkHavok400b1Classes::VersionString,
	hkHavok400b2Classes::VersionString,
	update
};

} // namespace hkCompat_hk400b1_hk400b2

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
