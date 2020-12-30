// Chase AI

#ifndef _ChaseAI
#define _ChaseAI

#include "BaseAI.h"

class ChaseAI : public BaseAI
{
public:
	ChaseAI();
	ChaseAI(const ChaseAI& other) = delete;
	ChaseAI& operator=(const ChaseAI& other) = delete;
	~ChaseAI() = default;

	void Execute(EnemyTank* t);

private:
	Vect target;
	const float playerDist;

};

#endif _ChaseAI