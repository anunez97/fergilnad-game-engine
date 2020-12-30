// Enemy Tank Factory

#include "EnemyTankFactory.h"
#include "EnemyTank.h"
#include "PlayerTank.h"
#include "ChaseAI.h"
#include "LongRangeAI.h"
#include "PatrolAI.h"
#include "DummyAI.h"

#include "PlayerManager.h"

EnemyTankFactory* EnemyTankFactory::ptrInstance = nullptr;

EnemyTankFactory::EnemyTankFactory()
{
	pChaseAI = new ChaseAI();
	pLRAI = new LongRangeAI();
	pPatrolAI = new PatrolAI();
}

void EnemyTankFactory::privCreateChaser(const Vect pos)
{
	EnemyTank* t;

	t = tankPool.GetTank();

	t->Initialize(pos, pChaseAI, EnemyTank::Type::CHASER);
	t->SetPlayer(PlayerManager::GetPlayer());
	t->SubmitEntry();

	tankList.push_back(t);

	DebugMsg::out("Enemy spawned\n");
}

void EnemyTankFactory::privCreateRanger(const Vect pos)
{
	EnemyTank* t;

	t = tankPool.GetTank();

	//t->Initialize(pos, pLRAI, EnemyTank::Type::LONGRANGER);
	t->Initialize(pos, new DummyAI(), EnemyTank::Type::LONGRANGER);
	t->SetPlayer(PlayerManager::GetPlayer());
	t->SubmitEntry();

	tankList.push_back(t);

	DebugMsg::out("Enemy spawned\n");
}

void EnemyTankFactory::privCreatePatroller(const Vect pos)
{
	EnemyTank* t;

	t = tankPool.GetTank();

	t->Initialize(pos, pPatrolAI, EnemyTank::Type::PATROLLER);
	t->SetPlayer(PlayerManager::GetPlayer());
	t->SubmitEntry();

	tankList.push_back(t);

	DebugMsg::out("Enemy spawned\n");
}

void EnemyTankFactory::TankReturn(EnemyTank* t)
{
	Instance().tankList.remove(t);
	Instance().tankPool.ReturnTank(t);
}

void EnemyTankFactory::privDelete()
{
	delete pChaseAI;
	delete pLRAI;
	delete pPatrolAI;

	for (std::list<EnemyTank*>::iterator it = tankList.begin(); it != tankList.end(); it++)
	{
		delete (*it);
	}

	delete ptrInstance;
	ptrInstance = nullptr;
}