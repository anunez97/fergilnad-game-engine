// Patrol AI

#ifndef _PatrolAI
#define _PatrolAI

#include "BaseAI.h"

class PatrolAI : public BaseAI
{
public:
	PatrolAI();
	PatrolAI(const PatrolAI& other) = delete;
	PatrolAI& operator=(const PatrolAI& other) = delete;
	~PatrolAI() = default;

	virtual void Execute(EnemyTank* t);
	void Move(float dist, EnemyTank* t);

private:
	Vect target;

	const float maxDist;
	const float minDist;
	float angle;

};

#endif _PatrolAI