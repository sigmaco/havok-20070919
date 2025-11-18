/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2007 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/Constraint/hkpConstraintData.h>
#include <Physics/ConstraintSolver/Constraint/Atom/hkpConstraintAtom.h>

void hkpConstraintData::addInstance( hkpConstraintInstance* constraint, hkpConstraintRuntime* runtime, int sizeOfRuntime ) const 
{
	if ( runtime )
	{
		hkString::memSet( runtime, 0, sizeOfRuntime );
	}
}

hkpSolverResults* hkpConstraintData::getSolverResults( hkpConstraintRuntime* runtime )
{
	return static_cast<hkpSolverResults*>(runtime);
}


#define HK_SKIP_ATOM_BY_TYPE(atomType, atomClassName)\
{\
case hkpConstraintAtom::atomType:\
{\
	const atomClassName* atom = static_cast<const atomClassName*>(currentAtom);\
	currentAtom = atom->next();\
}\
	break;\
}

#define HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE(atomType, atomClassName)\
{\
case hkpConstraintAtom::atomType:\
	{\
		const atomClassName* atom = static_cast<const atomClassName*>(currentAtom);\
		atom->addToConstraintInfo(infoOut);\
		currentAtom = atom->next();\
	}\
	break;\
}

void hkpConstraintData::getConstraintInfoUtil( const hkpConstraintAtom* atoms, int sizeOfAllAtoms, hkpConstraintData::ConstraintInfo& infoOut)
{
	infoOut.m_atoms = const_cast<hkpConstraintAtom*>(atoms);
	infoOut.m_sizeOfAllAtoms = sizeOfAllAtoms;
	infoOut.clear();
	infoOut.addHeader();

	if (atoms->m_type == hkpConstraintAtom::TYPE_CONTACT)
	{
		hkpSimpleContactConstraintAtom* contactAtom = static_cast<hkpSimpleContactConstraintAtom*>( const_cast<hkpConstraintAtom*>(atoms) );
		contactAtom->addToConstraintInfo(infoOut);
	}
	else
	{
		const hkpConstraintAtom* atomsEnd    = hkAddByteOffsetConst<const hkpConstraintAtom>( atoms, sizeOfAllAtoms );
		for( const hkpConstraintAtom* currentAtom = atoms; currentAtom < atomsEnd; )
		{
NEXT_SWITCH:
			switch(currentAtom->m_type)
			{
			case hkpConstraintAtom::TYPE_INVALID: 
				{
					// If this is blank padding between atoms, then move to the next 16-byte aligned atom
					currentAtom = reinterpret_cast<hkpConstraintAtom*>( HK_NEXT_MULTIPLE_OF(16, hkUlong(currentAtom)) );
					goto NEXT_SWITCH;
				}

				HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_BALL_SOCKET,				hkpBallSocketConstraintAtom      );
				HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_STIFF_SPRING,			hkpStiffSpringConstraintAtom		);

				HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_LIN,						hkpLinConstraintAtom             );
				HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_LIN_SOFT,				hkpLinSoftConstraintAtom         );
				HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_LIN_LIMIT,				hkpLinLimitConstraintAtom        );
				HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_LIN_FRICTION,			hkpLinFrictionConstraintAtom		);
				HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_LIN_MOTOR,				hkpLinMotorConstraintAtom		);

				HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_2D_ANG,					hkp2dAngConstraintAtom			);

				HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_ANG,						hkpAngConstraintAtom				);
				HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_ANG_LIMIT,				hkpAngLimitConstraintAtom        );
				HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_CONE_LIMIT,				hkpConeLimitConstraintAtom		);
				HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_TWIST_LIMIT,				hkpTwistLimitConstraintAtom		);
				HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_ANG_FRICTION,			hkpAngFrictionConstraintAtom     );
				HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_ANG_MOTOR,				hkpAngMotorConstraintAtom        );

				HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_RAGDOLL_MOTOR,			hkpRagdollMotorConstraintAtom	);
				HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_PULLEY,					hkpPulleyConstraintAtom			);

				//
				//	modifiers
				//

				// : no next() method
				//HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_MODIFIER_SOFT_CONTACT,    hkpSoftContactModifierConstraintAtom    );
				//HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_MODIFIER_MASS_CHANGER,    hkpMassChangerModifierConstraintAtom    );
				//HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_MODIFIER_VISCOUS_SURFACE, hkpViscousSurfaceModifierConstraintAtom );
				//HK_GET_CONSTRAINT_INFO_FROM_ATOM_BY_TYPE( TYPE_MODIFIER_MOVING_SURFACE,  hkpMovingSurfaceModifierConstraintAtom  );

				HK_SKIP_ATOM_BY_TYPE( TYPE_SET_LOCAL_TRANSFORMS,	hkpSetLocalTransformsConstraintAtom		);
				HK_SKIP_ATOM_BY_TYPE( TYPE_SET_LOCAL_ROTATIONS,		hkpSetLocalRotationsConstraintAtom		);
				HK_SKIP_ATOM_BY_TYPE( TYPE_SET_LOCAL_TRANSLATIONS,	hkpSetLocalTranslationsConstraintAtom	);

			case hkpConstraintAtom::TYPE_BRIDGE:
			case hkpConstraintAtom::TYPE_MODIFIER_SOFT_CONTACT:
			case hkpConstraintAtom::TYPE_MODIFIER_MASS_CHANGER:
			case hkpConstraintAtom::TYPE_MODIFIER_VISCOUS_SURFACE:
			case hkpConstraintAtom::TYPE_MODIFIER_MOVING_SURFACE:
				{
					// this is assumed to be the last atom
					currentAtom = atomsEnd;
					HK_ASSERT2(0x74890f9d, false, "What do we do here ?");
					break;
				}

			default:
				HK_ASSERT2(0xad67de77,0,"Illegal atom.");
			}
		}
	}
}

#undef  HK_SKIP_ATOM_BY_TYPE
#undef  HK_GET_CONSTRAINT_INFOR_FROM_ATOM_BY_TYPE



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
