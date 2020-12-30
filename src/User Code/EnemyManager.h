// Enemy Manager

#ifndef _EnemyManager
#define _EnemyManager

#include "AzulCore.h"

class EnemyTank;

class EnemyManager
{
private:
	static EnemyManager* ptrInstance;

	static EnemyManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new EnemyManager();
		return *ptrInstance;
	}

	EnemyManager();
	EnemyManager(const EnemyManager& other) = delete;
	EnemyManager& operator=(const EnemyManager& other) = delete;
	~EnemyManager() = default;

	void privEnemyKilled(EnemyTank* t);

	void privDelete();

	int enemiesCount;

public:
	static void SpawnChaser(Vect pos);
	static void SpawnLongRanger(Vect pos);
	static void SpawnPatroller(Vect pos);

	static void EnemyKilled(EnemyTank* t) { Instance().privEnemyKilled(t); }
	static int EnemiesLeft() { return Instance().enemiesCount; }

	static void Delete() { Instance().privDelete(); }
};

#endif _EnemyManager