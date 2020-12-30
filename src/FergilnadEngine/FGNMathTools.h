// FGNMathTools

#ifndef _FGNMathTools
#define _FGNMathTools

#include "AzulCore.h"

class CollisionVolume;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class CollisionVolumeBoundingBoxBase;
class Terrain;

/// <summary>
/// Math Tools class that has mathematical functions that are commonly needed (intersection for collisions).
/// </summary>
class FGNMathTools
{
public:
	/// <summary>
	/// Intersect tests if two Collision Volumes are intersecting.
	/// </summary>
	/// <param name="A"> Reference to the first CollisionVolume. </param>
	/// <param name="B"> Reference to the second CollisionVolume. </param>
	/// <returns></returns>
	static bool Intersect(const CollisionVolume& A, const CollisionVolume& B);
	
	/// <summary>
	/// Used for terrain collision testing.  Checks collision volume against AABB of terrain cell
	/// </summary>
	/// <param name="A"> Collision Volume</param>
	/// <param name="min"> Min corner of terrain cell</param>
	/// <param name="max"> Max corner of terrain cell</param>
	/// <returns></returns>
	static bool Intersect(const CollisionVolume& A, const Vect& min, const Vect& max, const Matrix& world);

	/// <summary>
	/// Intersect tests if two BSpheres are intersecting.
	/// </summary>
	/// <param name="A">Reference to the first BSphere. </param>
	/// <param name="B"> Reference to the second BSphere. </param>
	/// <returns></returns>
	static bool Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B);

	/// <summary>
	/// Intersect tests if an AABB and BSphere intersect.
	/// </summary>
	/// <param name="A"> Reference to the AABB.</param>
	/// <param name="B"> Reference to the BSphere.</param>
	/// <returns></returns>
	static bool Intersect(const CollisionVolumeAABB& A, const CollisionVolumeBSphere& B);

	/// <summary>
	/// Tests whether a point is inside a BSphere.
	/// </summary>
	/// <param name="v"> Point to be tested </param>
	/// <param name="A"> Reference to the BSphere. </param>
	/// <returns></returns>
	static bool PointBSphereIntersect(const Vect v, const CollisionVolumeBSphere& A);

	/// <summary>
	/// Intersect tests if two AABBs are intersecting.
	/// </summary>
	/// <param name="A"> Reference to the first AABB. </param>
	/// <param name="B"> Reference to the second AABB. </param>
	/// <returns></returns>
	static bool Intersect(const CollisionVolumeAABB& A, const CollisionVolumeAABB& B);

	/// <summary>
	/// Intersect tests if a BSphere and OBB intersect
	/// </summary>
	/// <param name="A"> Reference to the BSphere</param>
	/// <param name="B"> Reference to the OBB</param>
	/// <returns></returns>
	static bool Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeOBB& B);

	/// <summary>
	/// Intersect tests if an AABB and OBB intersect
	/// </summary>
	/// <param name="A"> Reference to the AABB</param>
	/// <param name="B"> Reference to the OBB</param>
	/// <returns></returns>
	static bool Intersect(const CollisionVolumeAABB& A, const CollisionVolumeOBB& B);

	/// <summary>
	/// Intersect tests if two OBBs intersect
	/// </summary>
	/// <param name="A"> Reference to the first OBB</param>
	/// <param name="B"> Reference to the second OBB</param>
	/// <returns></returns>
	static bool Intersect(const CollisionVolumeOBB& A, const CollisionVolumeOBB& B);

	/// <summary>
	/// Interval test that returns whether interval [a, b] overlaps with interval [c, d].
	/// </summary>
	/// <param name="a"> Left end point for the first interval. </param>
	/// <param name="b"> Right end point for the first interval. </param>
	/// <param name="c"> Left end point for the second interval. </param>
	/// <param name="d"> Right end point for the second interval. </param>
	/// <returns></returns>
	static bool IntervalTest(float a, float b, float c, float d);

	/// <summary>
	/// Clamps a Vector to the intervals, [minx, maxx], [miny, maxy], [minz, maxz].
	/// </summary>
	/// <param name="v"> Vector to be clamped </param>
	/// <param name="minx"> Left end point for the x interval. </param>
	/// <param name="miny"> Right end point for the x interval. </param>
	/// <param name="minz"> Left end point for the y interval. </param>
	/// <param name="maxx"> Right end point for the y interval. </param>
	/// <param name="maxy"> Left end point for the z interval. </param>
	/// <param name="maxz"> Right end point for the z interval. </param>
	/// <returns></returns>
	static Vect ClampPoint(Vect v, float minx, float miny, float minz, float maxx, float maxy, float maxz);

	/// <summary>
	/// Clamps a float to an interval [min, max]
	/// </summary>
	/// <param name="c"></param>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	static float Clamp(float f, float min, float max);

	/// <summary>
	/// Gives the projection vector of v on w
	/// </summary>
	/// <param name="v"> Vector that will be projected </param>
	/// <param name="w"> Vector that v is projected on </param>
	/// <returns></returns>
	static Vect Projection(Vect v, Vect w);

	/// <summary>
	/// Returns the length of a projection of v on w
	/// </summary>
	/// <param name="v"> Vector that will be projected </param>
	/// <param name="w"> Vector that will be projected on </param>
	/// <returns></returns>
	static float ProjectionLength(Vect v, Vect w);

	/// <summary>
	/// Test to determine if two OBBs intersect along a given axis (SAT)
	/// </summary>
	/// <param name="axis"> Axis to test intersection </param>
	/// <param name="A"> First OBB </param>
	/// <param name="B"> Second OBB </param>
	/// <returns></returns>
	static bool OBBOverlapTest(Vect axis, const CollisionVolumeOBB& A, const CollisionVolumeOBB& B);

	//static bool BBOverlapTest(Vect axis, const CollisionVolumeBoundingBoxBase& A, const CollisionVolumeBoundingBoxBase& B);

	/// <summary>
	/// Test to determine if two OBBs intersect along a given axis (SAT)
	/// </summary>
	/// <param name="axis"> Axis to test intersection </param>
	/// <param name="A"> First OBB </param>
	/// <param name="B"> Second OBB </param>
	/// <returns></returns>
	static bool AABBOBBOverlapTest(Vect axis, const CollisionVolumeAABB& A, const CollisionVolumeOBB& B);

	static bool AABBOBBOverlapTest(Vect axis, const Vect& min, const Vect& max, const Matrix& world, const CollisionVolumeOBB& A);

	/// <summary>
	/// Gives the length of the max projection.  Used for SAT testing
	/// </summary>
	/// <param name="v"> Axis to be projected on </param>
	/// <param name="A"> OBB to be tested </param>
	/// <returns></returns>
	static float MaxProjectionLength(Vect v, const CollisionVolumeOBB& A);

	/// <summary>
	/// Gives the length of the max projection. Used for SAT testing
	/// </summary>
	/// <param name="v"> Axis to be projected on</param>
	/// <param name="A"> AABB to be tested</param>
	/// <returns></returns>
	static float MaxProjectionLength(Vect v, const CollisionVolumeAABB& A);

	static float MaxProjectionLength(Vect v, const Vect& min, const Vect& max, const Matrix& world);

	/// <summary>
	/// Gives the number of vertices in a n x n square
	/// </summary>
	/// <param name="n"> Number of pixels on one side of a square</param>
	/// <returns></returns>
	static int NumVertsSquare(int n);

	/// <summary>
	/// Gives the number of triangles in a n x n square
	/// </summary>
	/// <param name="n"> Number of pixels for one side of a square</param>
	/// <returns></returns>
	static int NumTrisSquare(int n);

	/// <summary>
	/// Esentially a collision test for an AABB against a BSphere
	/// </summary>
	/// <param name="min">Min corner for the AABB</param>
	/// <param name="max">Max corner for the AABB</param>
	/// <param name="A"> BSphere</param>
	/// <returns></returns>
	static bool Intersect(Vect min, Vect max, const CollisionVolumeBSphere& A);

	/// <summary>
	/// Esentially a collision test for an AABB against an AABB
	/// </summary>
	/// <param name="min">Min corner for the AABB</param>
	/// <param name="max">Max corner for the AABB</param>
	/// <param name="A"> AABB</param>
	/// <returns></returns>
	static bool Intersect(Vect min, Vect max, const CollisionVolumeAABB& A);

	/// <summary>
	/// Esentially a collision test for an AABB against an OBB
	/// </summary>
	/// <param name="min">Min corner for the AABB</param>
	/// <param name="max">Max corner for the AABB</param>
	/// <param name="A"> OBB</param>
	/// <returns></returns>
	static bool Intersect(const Vect& min, const Vect& max, const Matrix& world, const CollisionVolumeOBB& A);

	/// <summary>
	/// Returns whether a point is inside an AABB
	/// </summary>
	/// <param name="p"> Point to be tested</param>
	/// <param name="min"> Min point for the AABB</param>
	/// <param name="max"> Max point for the AABB</param>
	/// <returns></returns>
	static bool PointInAABB(const Vect& p, const Vect& min, const Vect& max);

	/// <summary>
	/// Returns whether a value is inside an interval
	/// </summary>
	/// <param name="f"> Value to be tested</param>
	/// <param name="min"> Min value for the interval</param>
	/// <param name="max"> Max value for the interval</param>
	/// <returns></returns>
	static bool ValueIntervalTest(const float f, const float min, const float max);
};

#endif _FGNMathTools