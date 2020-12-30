// Long Range AI

#ifndef _LongRangeAI
#define _LongRangeAI

#include "BaseAI.h"

class LongRangeAI : public BaseAI
{
public:
	LongRangeAI();
	LongRangeAI(const LongRangeAI& other) = delete;
	LongRangeAI& operator=(const LongRangeAI& other) = delete;
	~LongRangeAI() = default;

	virtual void Execute(EnemyTank* t);

private:
	Vect target;
	const float playerDist;
	const float maxDist;

};

#endif _LongRangeAI