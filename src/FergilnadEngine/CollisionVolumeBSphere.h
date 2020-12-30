// Collision Volume BSphere

#ifndef _CollisionVolumeBSphere
#define _CollisionVolumeBSphere

#include "CollisionVolume.h"

class CollisionVolumeBSphere : public CollisionVolume
{
public:
	CollisionVolumeBSphere();
	CollisionVolumeBSphere(const CollisionVolumeBSphere& other) = delete;
	CollisionVolumeBSphere& operator=(const CollisionVolumeBSphere& other) = delete;
	~CollisionVolumeBSphere() = default;

	void ComputeData(Model* mod, const Matrix& mat);
	void DebugView(const Vect& col) const;

	bool IntersectAccept(const CollisionVolume& other) const;
	bool IntersectVisit(const CollisionVolumeBSphere& other) const;
	bool IntersectVisit(const CollisionVolumeAABB& other) const;
	bool IntersectVisit(const CollisionVolumeOBB& other) const;
	bool Intersect(const Vect& min, const Vect& max, const Matrix& world) const;

	const Matrix& GetRotate() const;
	const Vect& GetCenter() const;
	float GetRadius() const;

	void TempTest(Vect c, float r);

private:
	Matrix Rotate;
	Vect Center;
	float Radius;

};

#endif _CollisionVolumeBSphere