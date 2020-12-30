// Collision Volume BSphere

#include "CollisionVolumeBSphere.h"
#include "VisualizerAttorney.h"
#include "FGNMathTools.h"

CollisionVolumeBSphere::CollisionVolumeBSphere()
{
	Center.set(0, 0, 0);
	Radius = 0.0f;
}

void CollisionVolumeBSphere::ComputeData(Model* mod, const Matrix& mat)
{
	Center = mod->getCenter();
	Radius = mod->getRadius();

	float scale = mat.get(ROW_0).mag();
	Center *= mat;
	Radius *= scale;

	Vect v1 = mat.get(ROW_0) * (1.0f / scale);
	v1.set(v1.X(), v1.Y(), v1.Z(), 0);
	Vect v2 = mat.get(ROW_1) * (1.0f / scale);
	v2.set(v2.X(), v2.Y(), v2.Z(), 0);
	Vect v3 = mat.get(ROW_2) * (1.0f / scale);
	v3.set(v3.X(), v3.Y(), v3.Z(), 0);
	Vect v4(0, 0, 0);

	Rotate = { v1, v2, v3, v4 };

	//VisualizerAttorney::Show::BSphere(*this, Color::Green);
}

void CollisionVolumeBSphere::DebugView(const Vect& col) const
{
	VisualizerAttorney::Show::BSphere(*this, col);
}

bool CollisionVolumeBSphere::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return FGNMathTools::Intersect(*this, other);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return FGNMathTools::Intersect(other, *this);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return FGNMathTools::Intersect(*this, other);
}

bool CollisionVolumeBSphere::Intersect(const Vect& min, const Vect& max, const Matrix&) const
{
	return FGNMathTools::Intersect(min, max, *this);
}

const Matrix& CollisionVolumeBSphere::GetRotate() const
{
	return Rotate;
}

const Vect& CollisionVolumeBSphere::GetCenter() const
{
	return Center;
}

float CollisionVolumeBSphere::GetRadius() const
{
	return Radius;
}

void CollisionVolumeBSphere::TempTest(Vect c, float r)
{
	Center = c;
	Radius = r;
	Rotate = Matrix(IDENTITY);
}