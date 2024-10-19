// Collision Volume OBB

#include "CollisionVolumeOBB.h"
#include "VisualizerAttorney.h"
#include "FGNMathTools.h"
#include "ScreenLog.h"

void CollisionVolumeOBB::ComputeData(Model* mod, const Matrix& mat)
{
	World = mat;

	ScaleFactor = mat.get(ROW_0).magSqr();
	
	// Center in world space
	Center = (HalfDiagonal + mod->getMinAABB()) * mat;

}

void CollisionVolumeOBB::DebugView(const Vect& col) const
{
	VisualizerAttorney::Show::OBB(*this, col);
}

bool CollisionVolumeOBB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return FGNMathTools::Intersect(other, *this);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return FGNMathTools::Intersect(other, *this);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return FGNMathTools::Intersect(*this, other);
}

bool CollisionVolumeOBB::Intersect(const Vect& min, const Vect& max, const Matrix& world) const
{
	return FGNMathTools::Intersect(min, max, world, *this);
}

void CollisionVolumeOBB::SetMinMax(Model* mod)
{
	// All in local space
	CornerMin = mod->getMinAABB();
	CornerMax = mod->getMaxAABB();

	HalfDiagonal = .5f * (mod->getMaxAABB() - mod->getMinAABB());
}

Matrix CollisionVolumeOBB::GetWorld() const
{
	return World;
}

Vect CollisionVolumeOBB::GetCornerMax() const
{
	return CornerMax;
}

Vect CollisionVolumeOBB::GetCornerMin() const
{
	return CornerMin;
}

Vect CollisionVolumeOBB::GetCenter() const
{
	return Center;
}

Vect CollisionVolumeOBB::GetDiagonal() const
{
	return HalfDiagonal;
}

float CollisionVolumeOBB::GetScaleFactor() const
{
	return ScaleFactor;
}