// Enemy Tank Object Pool

#include "EnemyTankObjectPool.h"
#include "EnemyTank.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

EnemyTankObjectPool::EnemyTankObjectPool()
{
}

EnemyTankObjectPool::~EnemyTankObjectPool()
{
	while (!recycledTanks.empty())
	{
		delete recycledTanks.top();
		recycledTanks.pop();
	}
}

EnemyTank* EnemyTankObjectPool::GetTank()
{
	EnemyTank* t;

	if (recycledTanks.empty())
	{
		t = new EnemyTank(ModelManager::Get("tankbody"), ModelManager::Get("tankturret"), ShaderManager::Get("TextureLight"), TextureManager::Get("red"));
	}
	else
	{
		t = recycledTanks.top();
		recycledTanks.pop();
	}

	return t;
}

void EnemyTankObjectPool::ReturnTank(EnemyTank* t)
{
	recycledTanks.push(t);
}