// Enemy Manager

#include "EnemyManager.h"
#include "EnemyTankFactory.h"
#include "ScoreManager.h"
#include "EnemyTank.h"
#include "LevelTransition.h"

EnemyManager* EnemyManager::ptrInstance = nullptr;

EnemyManager::EnemyManager()
	:enemiesCount(0)
{

}

void EnemyManager::SpawnChaser(Vect pos)
{
	EnemyTankFactory::CreateChaser(pos);
	Instance().enemiesCount++;
}

void EnemyManager::SpawnLongRanger(Vect pos)
{
	EnemyTankFactory::CreateRanger(pos);
	Instance().enemiesCount++;
}

void EnemyManager::SpawnPatroller(Vect pos)
{
	EnemyTankFactory::CreatePatroller(pos);
	Instance().enemiesCount++;
}

void EnemyManager::privEnemyKilled(EnemyTank* t)
{
	ScoreManager::AddScore(t->GetType());
	Instance().enemiesCount--;
}

void EnemyManager::privDelete()
{
	delete ptrInstance;

	ptrInstance = nullptr;
}