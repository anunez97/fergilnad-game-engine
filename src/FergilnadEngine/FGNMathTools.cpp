// FGNMathTools

#include "FGNMathTools.h"
#include "CollisionVolume.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBoundingBoxBase.h"
#include "VisualizerAttorney.h"
#include "ScreenLog.h"
#include "Terrain.h"

bool FGNMathTools::Intersect(const CollisionVolume& A, const CollisionVolume& B)
{
	return A.IntersectAccept(B);
}

bool FGNMathTools::Intersect(const CollisionVolume& A, const Vect& min, const Vect& max, const Matrix& world)
{
	return A.Intersect(min, max, world);
}

bool FGNMathTools::Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B)
{
	Vect c1 = A.GetCenter();
	Vect c2 = B.GetCenter();
	Vect c3 = c1 - c2;

	float r1 = A.GetRadius();
	float r2 = B.GetRadius();

	if (c3.dot(c3) < (r1 + r2) * (r1 + r2))
		return true;
	else
		return false;
}

bool FGNMathTools::Intersect(const CollisionVolumeAABB& A, const CollisionVolumeBSphere& B)
{
	Vect center = B.GetCenter();
	Vect max = A.GetCornerMax();
	Vect min = A.GetCornerMin();

	Vect v = ClampPoint(center, min.X(), min.Y(), min.Z(), max.X(), max.Y(), max.Z());

	return PointBSphereIntersect(v, B);
}

bool FGNMathTools::Intersect(const CollisionVolumeAABB& A, const CollisionVolumeAABB& B)
{
	Vect amin = A.GetCornerMin();
	Vect amax = A.GetCornerMax();
	Vect bmin = B.GetCornerMin();
	Vect bmax = B.GetCornerMax();

	return IntervalTest(amin.X(), amax.X(), bmin.X(), bmax.X()) 
		&& IntervalTest(amin.Y(), amax.Y(), bmin.Y(), bmax.Y())
		&& IntervalTest(amin.Z(), amax.Z(), bmin.Z(), bmax.Z());
}

bool FGNMathTools::PointBSphereIntersect(const Vect v, const CollisionVolumeBSphere& A)
{
	// Distance between the point and the center of the bsphere
	float dist = (v - A.GetCenter()).mag();

	// if distance is less than or equal to the radius, the point is in the bsphere
	if (dist <= A.GetRadius())
		return true;
	else
		return false;
}

bool FGNMathTools::Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeOBB& B)
{
	Matrix worldInv = B.GetWorld().getInv();

	Vect localCenter = A.GetCenter() * worldInv;

	Vect v = ClampPoint(localCenter, B.GetCornerMin().X(), B.GetCornerMin().Y(), B.GetCornerMin().Z(), B.GetCornerMax().X(), B.GetCornerMax().Y(), B.GetCornerMax().Z());

	v *= B.GetWorld();

	return PointBSphereIntersect(v, A);
}

bool FGNMathTools::Intersect(const CollisionVolumeAABB& A, const CollisionVolumeOBB& B)
{
	Vect v1 = Vect(1.0f, 0, 0);
	Vect v2 = Vect(0, 1.0f, 0);
	Vect v3 = Vect(0, 0, 1.0f);

	Vect v4 = B.GetWorld().get(ROW_0);
	Vect v5 = B.GetWorld().get(ROW_1);
	Vect v6 = B.GetWorld().get(ROW_2);

	Vect v7 = v1.cross(v4);
	Vect v8 = v1.cross(v5);
	Vect v9 = v1.cross(v6);

	Vect v10 = v2.cross(v4);
	Vect v11 = v2.cross(v5);
	Vect v12 = v2.cross(v6);

	Vect v13 = v3.cross(v4);
	Vect v14 = v3.cross(v5);
	Vect v15 = v3.cross(v6);

	if (!AABBOBBOverlapTest(v1, A, B))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v2, A, B))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v3, A, B))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v4, A, B))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v5, A, B))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v6, A, B))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v7, A, B))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v8, A, B))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v9, A, B))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v10, A, B))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v11, A, B))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v12, A, B))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v13, A, B))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v14, A, B))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v15, A, B))
	{
		return false;
	}

	return true;
}

bool FGNMathTools::Intersect(const CollisionVolumeOBB& A, const CollisionVolumeOBB& B)
{
	Vect v1 = A.GetWorld().get(ROW_0);
	Vect v2 = A.GetWorld().get(ROW_1);
	Vect v3 = A.GetWorld().get(ROW_2);

	Vect v4 = B.GetWorld().get(ROW_0);
	Vect v5 = B.GetWorld().get(ROW_1);
	Vect v6 = B.GetWorld().get(ROW_2);

	Vect v7 = v1.cross(v4);
	Vect v8 = v1.cross(v5);
	Vect v9 = v1.cross(v6);

	Vect v10 = v2.cross(v4);
	Vect v11 = v2.cross(v5);
	Vect v12 = v2.cross(v6);

	Vect v13 = v3.cross(v4);
	Vect v14 = v3.cross(v5);
	Vect v15 = v3.cross(v6);

	if (!OBBOverlapTest(v1, A, B))
	{
		return false;
	}
	else if (!OBBOverlapTest(v2, A, B))
	{
		return false;
	}
	else if (!OBBOverlapTest(v3, A, B))
	{
		return false;
	}
	else if (!OBBOverlapTest(v4, A, B))
	{
		return false;
	}
	else if (!OBBOverlapTest(v5, A, B))
	{
		return false;
	}
	else if (!OBBOverlapTest(v6, A, B))
	{
		return false;
	}
	else if (!OBBOverlapTest(v7, A, B))
	{
		return false;
	}
	else if (!OBBOverlapTest(v8, A, B))
	{
		return false;
	}
	else if (!OBBOverlapTest(v9, A, B))
	{
		return false;
	}
	else if (!OBBOverlapTest(v10, A, B))
	{
		return false;
	}
	else if (!OBBOverlapTest(v11, A, B))
	{
		return false;
	}
	else if (!OBBOverlapTest(v12, A, B))
	{
		return false;
	}
	else if (!OBBOverlapTest(v13, A, B))
	{
		return false;
	}
	else if (!OBBOverlapTest(v14, A, B))
	{
		return false;
	}
	else if (!OBBOverlapTest(v15, A, B))
	{
		return false;
	}

	return true;
}

bool FGNMathTools::IntervalTest(float a, float b, float c, float d)
{
	if (b < c)
		return false;
	else if (d < a)
		return false;
	else
		return true;
}

Vect FGNMathTools::ClampPoint(Vect v, float minx, float miny, float minz, float maxx, float maxy, float maxz)
{
	return Vect(Clamp(v.X(), minx, maxx), Clamp(v.Y(), miny, maxy), Clamp(v.Z(), minz, maxz));
}

float FGNMathTools::Clamp(float f, float min, float max)
{
	if (f < min)
		return min;
	else if (f > max)
		return max;
	else
		return f;
}

bool FGNMathTools::OBBOverlapTest(Vect axis, const CollisionVolumeOBB& A, const CollisionVolumeOBB& B)
{
	if (axis.magSqr() > FLT_EPSILON)
	{
		float D = Projection(B.GetCenter() - A.GetCenter(), axis).mag();

		float p1 = A.GetScaleFactor() * MaxProjectionLength(axis, A);
		float p2 = B.GetScaleFactor() * MaxProjectionLength(axis, B);

		return D <= p1 + p2;
	}
	return true;
}

bool FGNMathTools::AABBOBBOverlapTest(Vect axis, const CollisionVolumeAABB& A, const CollisionVolumeOBB& B)
{

	if (axis.magSqr() > FLT_EPSILON)
	{
		float D = abs((B.GetCenter() - A.GetCenter()).dot(axis));

		float p1 = A.GetScaleFactor() * MaxProjectionLength(axis, A);
		float p2 = B.GetScaleFactor() * MaxProjectionLength(axis, B);

		/*float D = abs((B.GetCenter() - A.GetCenter()).dot(axis));

		float p1 = A.GetScaleFactor() * MaxProjectionLength(axis, A);
		float p2 = B.GetScaleFactor() * MaxProjectionLength(axis, B);
		return D <= p1 + p2;*/

		return D <= p1 + p2;
	}
	return true;
}

bool FGNMathTools::AABBOBBOverlapTest(Vect axis, const Vect& min, const Vect& max, const Matrix& world, const CollisionVolumeOBB& A)
{
	if (axis.magSqr() > FLT_EPSILON)
	{
		Vect center = min + ((max - min) * .5f);

		float D = abs((A.GetCenter() - center).dot(axis));

		// use min and max
		float scale = Matrix(SCALE, (max - min)).get(ROW_0).magSqr();

		float p1 = scale * MaxProjectionLength(axis, min, max, world);

		float p2 = A.GetScaleFactor() * MaxProjectionLength(axis, A);

		return D <= p1 + p2;
	}
	return true;
}

float FGNMathTools::MaxProjectionLength(Vect v, const CollisionVolumeOBB& A)
{
	Vect v1 = v;
	v1.W() = 0;

	Vect d = A.GetDiagonal();

	v1 *= A.GetWorld().getInv();

	return (abs(d.X() * v1.X()) + abs(d.Y() * v1.Y()) + abs(d.Z() * v1.Z())) / v.mag();
}

float FGNMathTools::MaxProjectionLength(Vect v, const CollisionVolumeAABB& A)
{
	Vect v1 = v;
	v1.W() = 0;

	Vect d = A.GetDiagonal();

	v1 *= A.GetWorld().getInv();

	return abs(d.dot(v1));
}

float FGNMathTools::MaxProjectionLength(Vect v, const Vect& min, const Vect& max, const Matrix& world)
{
	Vect v1 = v;
	v1.W() = 0;

	Vect diag = (max - min) * .5f;
	diag *= world.getInv();
	//Vect d = A.GetDiagonal();

	v1 *= world.getInv();

	return abs(diag.dot(v1));
}

Vect FGNMathTools::Projection(Vect v, Vect w)
{
	return ProjectionLength(v, w) * w.getNorm();
}

float FGNMathTools::ProjectionLength(Vect v, Vect w)
{
	return ((abs(v.X() * w.X()) + abs(v.Y() * w.Y()) + abs(v.Z() * w.Z()))) / w.mag();
}

int FGNMathTools::NumVertsSquare(int n)
{
	return n * n;
}

int FGNMathTools::NumTrisSquare(int n)
{
	return 2 * (n - 1) * (n - 1);
}

bool FGNMathTools::Intersect(Vect min, Vect max, const CollisionVolumeBSphere& A)
{
	Vect center = A.GetCenter();

	Vect v = ClampPoint(center, min.X(), min.Y(), min.Z(), max.X(), max.Y(), max.Z());

	return PointBSphereIntersect(v, A);
}

bool FGNMathTools::Intersect(Vect min, Vect max, const CollisionVolumeAABB& A)
{
	Vect amin = A.GetCornerMin();
	Vect amax = A.GetCornerMax();

	return IntervalTest(amin.X(), amax.X(), min.X(), max.X())
		&& IntervalTest(amin.Y(), amax.Y(), min.Y(), max.Y())
		&& IntervalTest(amin.Z(), amax.Z(), min.Z(), max.Z());
}

bool FGNMathTools::Intersect(const Vect& min, const Vect& max, const Matrix& world, const CollisionVolumeOBB& A)
{
	Vect v1 = Vect(1.0f, 0, 0);
	Vect v2 = Vect(0, 1.0f, 0);
	Vect v3 = Vect(0, 0, 1.0f);

	Vect v4 = A.GetWorld().get(ROW_0);
	Vect v5 = A.GetWorld().get(ROW_1);
	Vect v6 = A.GetWorld().get(ROW_2);

	Vect v7 = v1.cross(v4);
	Vect v8 = v1.cross(v5);
	Vect v9 = v1.cross(v6);

	Vect v10 = v2.cross(v4);
	Vect v11 = v2.cross(v5);
	Vect v12 = v2.cross(v6);

	Vect v13 = v3.cross(v4);
	Vect v14 = v3.cross(v5);
	Vect v15 = v3.cross(v6);

	if (!AABBOBBOverlapTest(v1, min, max, world, A))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v2, min, max, world, A))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v3, min, max, world, A))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v4, min, max, world, A))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v5, min, max, world, A))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v6, min, max, world, A))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v7, min, max, world, A))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v8, min, max, world, A))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v9, min, max, world, A))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v10, min, max, world, A))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v11, min, max, world, A))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v12, min, max, world, A))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v13, min, max, world, A))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v14, min, max, world, A))
	{
		return false;
	}
	else if (!AABBOBBOverlapTest(v15, min, max, world, A))
	{
		return false;
	}

	return true;
}

bool FGNMathTools::PointInAABB(const Vect& p, const Vect& min, const Vect& max)
{
	if (!ValueIntervalTest(p.X(), min.X(), max.X()))
		return false;
	else if (!ValueIntervalTest(p.Y(), min.Y(), max.Y()))
		return false;
	else if (!ValueIntervalTest(p.Z(), min.Z(), max.Z()))
		return false;
	else
		return true;
}

bool FGNMathTools::ValueIntervalTest(const float f, const float min, const float max)
{
	if (f < min)
		return false;
	else if (f > max)
		return false;
	else 
		return true;
}