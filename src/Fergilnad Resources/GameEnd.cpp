// Fergilnad End

#include "Fergilnad.h"
#include "../User Code/BulletFactory.h"
#include "../User Code/HUD.h"
#include "../User Code/ScoreManager.h"
#include "../User Code/PlayerManager.h"
#include "../User Code/EnemyTankFactory.h"
#include "../User Code/EnemyManager.h"
#include "..//User Code/LevelManager.h"
#include "..//User Code/BulletAOEFactory.h"

void Fergilnad::GameEnd()
{
	// Use this area for final user-related clean-up
	DebugMsg::out("Game destroyed");
	BulletFactory::Delete();
	HUD::Delete();
	ScoreManager::Delete();
	PlayerManager::Delete();
	EnemyManager::Delete();
	EnemyTankFactory::Delete();
	LevelManager::Delete();
	BulletAOEFactory::Delete();

}