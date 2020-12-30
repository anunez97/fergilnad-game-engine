// Long Range AI

#include "LongRangeAI.h"
#include "EnemyTank.h"
#include "PlayerTank.h"

LongRangeAI::LongRangeAI()
	:playerDist(500.0f), maxDist(700.0f)
{
}

void LongRangeAI::Execute(EnemyTank* t)
{
	target = t->GetPlayer()->GetPos();

	t->LookAt(target);

	float dist = (t->GetPlayer()->GetPos() - t->GetPos()).mag();

	if (dist < playerDist)
	{
		Vect dir = t->GetPos() - target;
		dir.norm();

		dir *= 2;

		t->MoveTo(t->GetPos() + dir);
	}
	else if (dist > maxDist)
	{
		t->MoveTo(target);
	}
}