// Enemy Tank Object Pool

#ifndef _EnemyTankObjectPool
#define _EnemyTankObjectPool

#include "AzulCore.h"
#include <stack>

class EnemyTank;

class EnemyTankObjectPool
{
public:
	EnemyTankObjectPool();
	EnemyTankObjectPool(const EnemyTankObjectPool& other) = delete;
	EnemyTankObjectPool& operator=(const EnemyTankObjectPool& other) = delete;
	~EnemyTankObjectPool();

	EnemyTank* GetTank();
	void ReturnTank(EnemyTank* t);

private:
	std::stack<EnemyTank*> recycledTanks;
	Model* pBodyModel;
	Model* pTurretModel;
	ShaderObject* pShader;
	Texture* pTexture;

};

#endif _EnemyTankObjectPool