// Collision Volume AABB

#include "CollisionVolumeAABB.h"
#include "VisualizerAttorney.h"
#include "FGNMathTools.h"
#include "ScreenLog.h"
#include "CollisionVolumeBSphere.h"

CollisionVolumeAABB::CollisionVolumeAABB()
{
	CornerMin.set(0, 0, 0);
	CornerMax.set(0, 0, 0);
	Center.set(0, 0, 0);
}

CollisionVolumeAABB::CollisionVolumeAABB(const CollisionVolumeAABB& other)
{
	this->CornerMax = other.CornerMax;
	this->CornerMin = other.CornerMin;
	this->Center = other.Center;
}

CollisionVolumeAABB::CollisionVolumeAABB(Vect min, Vect max)
{
	CornerMax = max;
	CornerMin = min;
	Center = min + ((max - min) * .5f);
}

void CollisionVolumeAABB::ComputeData(Model* mod, const Matrix& mat)
{
	World = mat;

	ScaleFactor = mat.get(ROW_0).magSqr();

	Vect v = mod->getVectList()[0];
	v *= mat;

	float minX = v.X();
	float minY = v.Y();
	float minZ = v.Z();
	float maxX = v.X();
	float maxY = v.Y();
	float maxZ = v.Z();

	for (int i = 1; i < mod->getVectNum(); i++)
	{
		v = mod->getVectList()[i];

		v *= mat;

		if (minX > v.X())
		{
			minX = v.X();
		}
		else if (maxX < v.X())
		{
			maxX = v.X();
		}

		if (minY > v.Y())
		{
			minY = v.Y();
		}
		else if (maxY < v.Y())
		{
			maxY = v.Y();
		}

		if (minZ > v.Z())
		{
			minZ = v.Z();
		}
		else if (maxZ < v.Z())
		{
			maxZ = v.Z();
		}
	}
	CornerMin.set(minX, minY, minZ);
	CornerMax.set(maxX, maxY, maxZ);

	//Center = (GetDiagonal() + GetLocalMin()) * mat;
	Center = (GetDiagonal() + (CornerMin * mat.getInv())) * mat;
}

void CollisionVolumeAABB::ComputeData(const CollisionVolumeBSphere* bsphere)
{
	if (CornerMin.X() > bsphere->GetCenter().X() - bsphere->GetRadius())
		CornerMin.X() = bsphere->GetCenter().X() - bsphere->GetRadius();
	else if (CornerMax.X() < bsphere->GetCenter().X() + bsphere->GetRadius())
		CornerMax.X() = bsphere->GetCenter().X() + bsphere->GetRadius();

	if (CornerMin.Y() > bsphere->GetCenter().Y() - bsphere->GetRadius())
		CornerMin.Y() = bsphere->GetCenter().Y() - bsphere->GetRadius();
	else if (CornerMax.Y() < bsphere->GetCenter().Y() + bsphere->GetRadius())
		CornerMax.Y() = bsphere->GetCenter().Y() + bsphere->GetRadius();

	if (CornerMin.Z() > bsphere->GetCenter().Z() - bsphere->GetRadius())
		CornerMin.Z() = bsphere->GetCenter().Z() - bsphere->GetRadius();
	else if (CornerMax.Z() < bsphere->GetCenter().Z() + bsphere->GetRadius())
		CornerMax.Z() = bsphere->GetCenter().Z() + bsphere->GetRadius();
}

void CollisionVolumeAABB::SetInitialSphere(const CollisionVolumeBSphere* bsphere)
{
	CornerMin.set(bsphere->GetCenter() - Vect(bsphere->GetRadius(), bsphere->GetRadius(), bsphere->GetRadius()));
	CornerMax.set(bsphere->GetCenter() + Vect(bsphere->GetRadius(), bsphere->GetRadius(), bsphere->GetRadius()));
}

void CollisionVolumeAABB::Reset()
{
	CornerMin.set(0, 0, 0, 0);
	CornerMax.set(0, 0, 0, 0);
}

void CollisionVolumeAABB::DebugView(const Vect& col) const
{
	VisualizerAttorney::Show::AABB(*this, col);
}

bool CollisionVolumeAABB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return FGNMathTools::Intersect(*this, other);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return FGNMathTools::Intersect(*this, other);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return FGNMathTools::Intersect(*this, other);
}

bool CollisionVolumeAABB::Intersect(const Vect& min, const Vect& max, const Matrix&) const
{
	return FGNMathTools::Intersect(min, max, *this);
}

Vect CollisionVolumeAABB::GetCornerMax() const
{
	return CornerMax;
}

Vect CollisionVolumeAABB::GetCornerMin() const
{
	return CornerMin;
}

Matrix CollisionVolumeAABB::GetWorld() const
{
	return World;
}

Vect CollisionVolumeAABB::GetCenter() const
{
	return Center;
}

Vect CollisionVolumeAABB::GetDiagonal() const
{
	return .5f * ((CornerMax * World.getInv()) - (CornerMin * World.getInv()));
}

float CollisionVolumeAABB::GetScaleFactor() const
{
	return ScaleFactor;
}