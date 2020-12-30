// Collision Volume AABB

#ifndef _CollisionVolumeAABB
#define _CollisionVolumeAABB

#include "CollisionVolume.h"

class CollisionVolumeAABB : public CollisionVolume
{
public:
	CollisionVolumeAABB();
	CollisionVolumeAABB(const CollisionVolumeAABB& other);
	CollisionVolumeAABB& operator=(const CollisionVolumeAABB& other) = delete;
	~CollisionVolumeAABB() {};

	CollisionVolumeAABB(Vect min, Vect max);

	void ComputeData(Model* mod, const Matrix& mat);
	void ComputeData(const CollisionVolumeBSphere* bsphere);
	void SetInitialSphere(const CollisionVolumeBSphere* bsphere);
	void Reset();

	void DebugView(const Vect& col) const;

	bool IntersectAccept(const CollisionVolume& other) const;
	bool IntersectVisit(const CollisionVolumeBSphere& other) const;
	bool IntersectVisit(const CollisionVolumeAABB& other) const;
	bool IntersectVisit(const CollisionVolumeOBB& other) const;
	bool Intersect(const Vect& min, const Vect& max, const Matrix& world) const;

	Vect GetCornerMax() const;
	Vect GetCornerMin() const;

	Vect GetCenter() const;
	Vect GetDiagonal() const;

	float GetScaleFactor() const;

	Matrix GetWorld() const;

private:
	Matrix World;
	Matrix Rotate;

	Vect CornerMax;
	Vect CornerMin;

	Vect Center;

	float ScaleFactor;
};

#endif _CollisionVolumeAABB