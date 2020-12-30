// Enemy Tank Factory

#ifndef _EnemyTankFactory
#define _EnemyTankFactory

#include "AzulCore.h"
#include <list>
#include "EnemyTankObjectPool.h"

class EnemyTank;
class PlayerTank;
class ChaseAI;
class LongRangeAI;
class PatrolAI;

class EnemyTankFactory
{
private:
	static EnemyTankFactory* ptrInstance;

	static EnemyTankFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new EnemyTankFactory;
		return *ptrInstance;
	}

	EnemyTankFactory();
	EnemyTankFactory(const EnemyTankFactory& other) = delete;
	EnemyTankFactory& operator=(const EnemyTankFactory& other) = delete;
	~EnemyTankFactory() = default;

	void privCreateChaser(const Vect pos);
	void privCreateRanger(const Vect pos);
	void privCreatePatroller(const Vect pos);

	void privDelete();

	EnemyTankObjectPool tankPool;
	std::list<EnemyTank*> tankList;

	PlayerTank* player;
	ChaseAI* pChaseAI;
	LongRangeAI* pLRAI;
	PatrolAI* pPatrolAI;

public:
	static void CreateChaser(const Vect pos) { return Instance().privCreateChaser(pos); };
	static void CreateRanger(const Vect pos) { return Instance().privCreateRanger(pos); };
	static void CreatePatroller(const Vect pos) { return Instance().privCreatePatroller(pos); };
	static void TankReturn(EnemyTank* t);
	static void Delete() { Instance().privDelete(); }
};

#endif _EnemyTankFactory