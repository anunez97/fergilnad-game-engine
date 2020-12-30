// Collision Volume

#ifndef _CollisionVolume
#define _CollisionVolume

#include "AzulCore.h"

class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class CollisionVolumeBoundingBoxBase;

class CollisionVolume : public Align16
{
public:
	CollisionVolume() {};
	CollisionVolume(const CollisionVolume& other) = delete;
	CollisionVolume& operator=(const CollisionVolume& other) = delete;
	virtual ~CollisionVolume() {};

	virtual void ComputeData(Model* mod, const Matrix& mat) = 0;
	virtual void DebugView(const Vect& col) const = 0;

	virtual bool IntersectAccept(const CollisionVolume& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const = 0;
	virtual bool Intersect(const Vect& min, const Vect& max, const Matrix& world) const = 0;

};

#endif _CollisionVolume