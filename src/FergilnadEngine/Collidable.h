// Collidable

#ifndef _Collidable
#define _Collidable

#include "CollisionManager.h"
#include "CollidableGroup.h"
#include "SceneAttorney.h"
#include "RegistrationState.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"

class CollisionRegistrationCommand;
class CollisionDeregistrationCommand;
class OctreeNode;

class Collidable
{
	friend class CollidableAttorney;
public:
	Collidable();
	virtual ~Collidable();

	enum VolumeType
	{
		BSPHERE,
		AABB,
		OBB
	};

	/// <summary>
	/// Submits a GameObject for Collision Registration.
	/// </summary>
	void SubmitCollisionRegistration();

	/// <summary>
	/// Submits a GameObject for Collision Deregistration.
	/// </summary>
	void SubmitCollisionDeregistration();

	/// <summary>
	/// Method that is called when the GameObject collides with another collidable GameObject.
	/// </summary>
	/// <param name=""> Can be any user defined GameObject that has Collision turned on. </param>
	virtual void Collision(Collidable*) {};
	
	/// <summary>
	/// Method that is called when the GameObject collides with the Scene terrain
	/// </summary>
	/// <param name=""></param>
	virtual void CollisionTerrain() {};

	/// <summary>
	/// Sets the GameObject's Collider model 
	/// </summary>
	/// <param name="mod"> Pointer the model object of the GameObject. </param>
	void SetColliderModel(Model* mod, VolumeType type);

	/// <summary>
	/// Renders the node in the collision octree that the object is inside
	/// </summary>
	void ShowNode();

	

private:
	Collidable(const Collidable& other) = delete;
	Collidable& operator=(const Collidable& other) = delete;

	void SceneRegistration();
	void SceneDeregistration();

	/// <summary>
	/// Gives the selected collision volume of the Collidable
	/// </summary>
	/// <returns>A reference to the selected Collision Volume</returns>
	const CollisionVolume& GetCollisionVolume();

	/// <summary>
	/// Gives the default BSphere of the Collidable
	/// </summary>
	/// <returns>A reference to the default BSphere</returns>
	const CollisionVolumeBSphere* GetCollisionSphere();

	CollisionVolume* pColVolume;
	CollisionVolumeBSphere* pBSphere;
	CollisionVolumeAABB* pAABB;
	CollisionVolumeOBB* pOBB;
	Model* pColModel;

	CollisionRegistrationCommand* pRegCmd;
	CollisionDeregistrationCommand* pDeregCmd;

	CollidableGroup::CollidableCollectionRef pDeleteRef;
	RegistrationState RegStateCurr;

	CollisionManager::FGNTypeID myID;

	/* ---- Used for Collision Octree ---- */
	struct OctreeData
	{
		OctreeNode* parentNode;  // pointer to the node that the object is in
		bool inTree; // the collidable is in the octree
	};

	/// <summary>
	/// Sets the parent node in the octree of the Collidable
	/// </summary>
	/// <param name="parent">Pointer to a node in the octree</param>
	void SetParentNode(OctreeNode* parent);

	/// <summary>
	/// Gives the node in the octree that the Collidable is in
	/// </summary>
	/// <returns>Pointer to the node</returns>
	OctreeNode* GetParentNode();

	OctreeData octreeData;

	/// <summary>
	/// Inserts the Collidable into the octree
	/// </summary>
	void InsertIntoOctree();

	/// <summary>
	/// Removes the Collidable from the octree
	/// </summary>
	void RemoveFromOctree();

protected:
	/// <summary>
	/// Updates the collision data matrix for a GameObject.
	/// </summary>
	/// <param name="mat"> Constant Matrix reference, usually a world matrix. </param>
	void UpdateCollisionData(const Matrix& mat);

	template <typename C>
	void SetCollidableGroup()
	{
		myID = SceneAttorney::Registration::GetCollisionManager()->GetTypeID<C>();
	}
};

#endif _Collidable