// Missile Launcher

#ifndef _BaseAI
#define _BaseAI

#include "AzulCore.h"

class EnemyTank;

class BaseAI
{
public:
	BaseAI() = default;
	BaseAI(const BaseAI& other) = delete;
	BaseAI& operator=(const BaseAI& other) = delete;
	~BaseAI() = default;

	virtual void Execute(EnemyTank*) {};

};

#endif _MissileLauncher