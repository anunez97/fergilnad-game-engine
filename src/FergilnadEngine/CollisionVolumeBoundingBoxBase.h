/*// Collision Volume Bounding Box Base

#ifndef _CollisionVolumeBoundingBoxBase
#define _CollisionVolumeBoundingBoxBase

#include "CollisionVolume.h"
#include <vector>

class CollisionVolumeBoundingBoxBase : public CollisionVolume
{
public:
	CollisionVolumeBoundingBoxBase() {};
	CollisionVolumeBoundingBoxBase(const CollisionVolumeBoundingBoxBase& other) = delete;
	CollisionVolumeBoundingBoxBase& operator=(const CollisionVolumeBoundingBoxBase& other) = delete;
	virtual ~CollisionVolumeBoundingBoxBase() {};

	virtual Matrix GetWorld() const = 0;

	virtual Vect GetDiagonal() const = 0;
	virtual Vect GetCornerMin() const = 0;
	virtual Vect GetCornerMax() const = 0;
	virtual Vect GetCenter() const = 0;

	virtual Vect GetXAxis() const = 0;
	virtual Vect GetYAxis() const = 0;
	virtual Vect GetZAxis() const = 0;

	virtual float GetScaleFactor() const = 0;

protected:
	Matrix World;
	Vect CornerMax;
	Vect CornerMin;
	Vect Center;
	Vect HalfDiagonal;

	Vect xaxis;
	Vect yaxis;
	Vect zaxis;

	float ScaleFactor;
};

#endif _CollisionVolumeBoundingBoxBase*/