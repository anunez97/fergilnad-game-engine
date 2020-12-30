// Chase AI

#include "ChaseAI.h"

#include "EnemyTank.h"
#include "PlayerTank.h"

ChaseAI::ChaseAI()
	:playerDist(200.0f)
{
}

void ChaseAI::Execute(EnemyTank* t)
{
	target = t->GetPlayer()->GetPos();

	t->LookAt(target);

	if ((target - t->GetPos()).mag() > playerDist)
	{
		t->MoveTo(target);
	}
}