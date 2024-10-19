// Collidable

#include "Collidable.h"
#include "CollidableGroup.h"
#include "CollisionManager.h"
#include "SceneAttorney.h"
#include "CollisionRegistrationCommand.h"
#include "CollisionDeregistrationCommand.h"
#include "VisualizerAttorney.h"

Collidable::Collidable()
{
	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;

	myID = CollisionManager::FGN_UNDEFINED;

	pRegCmd = new CollisionRegistrationCommand(this);
	pDeregCmd = new CollisionDeregistrationCommand(this);

	pBSphere = new CollisionVolumeBSphere();
	pAABB = new CollisionVolumeAABB();
	pOBB = new CollisionVolumeOBB();

	octreeData.parentNode = 0;
	octreeData.inTree = false;
}

Collidable::~Collidable()
{

	DebugMsg::out("Collidable destructor\n");
	delete pRegCmd;
	delete pDeregCmd;
	delete pBSphere;
	delete pAABB;
	delete pOBB;
}

void Collidable::SubmitCollisionRegistration()
{
	assert(RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::Command::Submit(SceneManager::GetCurrentScene(), pRegCmd);
	RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Collidable::SubmitCollisionDeregistration()
{
	assert(RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::Command::Submit(SceneManager::GetCurrentScene(), pDeregCmd);
	RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}

void Collidable::SceneRegistration()
{
	assert(RegStateCurr == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::Registration::GetCollisionManager()->GetColGroup(myID)->Register(this, pDeleteRef);

	InsertIntoOctree();

	RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Collidable::SceneDeregistration()
{
	assert(RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::Registration::GetCollisionManager()->GetColGroup(myID)->Deregister(pDeleteRef);

	RemoveFromOctree();

	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}

const CollisionVolume& Collidable::GetCollisionVolume()
{
	return *pColVolume;
}

const CollisionVolumeBSphere* Collidable::GetCollisionSphere()
{
	return pBSphere;
}

void Collidable::SetColliderModel(Model* mod, VolumeType type)
{
	pColModel = mod;

	switch (type)
	{
	case VolumeType::AABB:
		pColVolume = pAABB;
		break;
	case VolumeType::BSPHERE:
		pColVolume = pBSphere;
		break;
	case VolumeType::OBB:
		pOBB->SetMinMax(mod);
		pColVolume = pOBB;
		break;
	default:
		pColVolume = pBSphere;
	}
}

void Collidable::UpdateCollisionData(const Matrix& mat)
{
	// If the user selects the bsphere as the collision model, will not compute data twice for it
	if(pColVolume == pBSphere)
		pColVolume->ComputeData(pColModel, mat);
	else
	{
		pColVolume->ComputeData(pColModel, mat);
		pBSphere->ComputeData(pColModel, mat);
	}
}

/* ---- Used for Collision Octree ---- */
void Collidable::SetParentNode(OctreeNode* parent)
{
	octreeData.parentNode = parent;
}

OctreeNode* Collidable::GetParentNode()
{
	return octreeData.parentNode;
}

void Collidable::InsertIntoOctree()
{
	if (!octreeData.inTree)
	{
		SceneAttorney::Registration::GetCollisionManager()->InsertInTree(this);
		octreeData.inTree = true;
	}
}

void Collidable::RemoveFromOctree()
{
	if (octreeData.inTree)
	{
		SceneAttorney::Registration::GetCollisionManager()->RemoveFromTree(this);
		octreeData.inTree = false;
	}
}

void Collidable::ShowNode()
{
	SceneAttorney::Registration::GetCollisionManager()->ShowNode(this);
}