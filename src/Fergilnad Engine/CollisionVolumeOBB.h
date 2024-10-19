// Collision Volume OBB

#ifndef _CollisionVolumeOBB
#define _CollisionVolumeOBB

#include "CollisionVolume.h"

class CollisionVolumeOBB : public CollisionVolume
{
public:
	CollisionVolumeOBB() = default;
	CollisionVolumeOBB(const CollisionVolumeOBB& other) = delete;
	CollisionVolumeOBB& operator=(const CollisionVolumeOBB& other) = delete;
	~CollisionVolumeOBB() = default;

	void ComputeData(Model* mod, const Matrix& mat);
	void DebugView(const Vect& col) const;

	bool IntersectAccept(const CollisionVolume& other) const;
	bool IntersectVisit(const CollisionVolumeBSphere& other) const;
	bool IntersectVisit(const CollisionVolumeAABB& other) const;
	bool IntersectVisit(const CollisionVolumeOBB& other) const;
	bool Intersect(const Vect& min, const Vect& max, const Matrix& world) const;

	void SetMinMax(Model* mod);

	Matrix GetWorld() const;

	Vect GetCornerMax() const;
	Vect GetCornerMin() const;
	Vect GetCenter() const;
	Vect GetDiagonal() const;

	float GetScaleFactor() const;

private:
	Matrix World;

	Vect CornerMin;
	Vect CornerMax;
	Vect HalfDiagonal;
	Vect Center;

	float ScaleFactor;

};

#endif _CollisionVolumeOBB