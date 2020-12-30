// Patrol AI

#include "PatrolAI.h"
#include "EnemyTank.h"
#include "PlayerTank.h"
#include "TimeManager.h"

PatrolAI::PatrolAI()
	:maxDist(400.0f), minDist(300.0f), angle(0.0f)
{
	angle = static_cast<float>(rand() % 360);
}

void PatrolAI::Execute(EnemyTank* t)
{
	target = t->GetPlayer()->GetPos();

	t->LookAt(target);

	Move((target - t->GetPos()).mag(), t);
}

void PatrolAI::Move(float dist, EnemyTank* t)
{
	// Enemy is too far away from the player
	if (dist > maxDist)
	{
		Vect dir = target - t->GetPos();
		dir.norm();

		t->MoveTo(t->GetPos() + dir);
	}
	// Enemy is too close to the player
	else if (dist < minDist)
	{
		Vect dir = t->GetPos() - target;
		dir.norm();

		t->MoveTo(t->GetPos() + dir);
	}
	else
	{
		Vect dir = Vect(t->GetPos().Z(), 0, -t->GetPos().X());
		dir.norm();

		Vect v = t->GetPos() - target;
		v.norm();
		v *= ((maxDist - minDist) / 2.0f) + minDist;

		t->MoveTo(v + dir);

	}
}