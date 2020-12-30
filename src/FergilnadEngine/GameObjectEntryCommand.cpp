// Game Object Entry Command

#include "GameObjectEntryCommand.h"
#include "GameObjectAttorney.h"

GameObjectEntryCommand::GameObjectEntryCommand(GameObject* go)
	:pGO(go)
{
}

void GameObjectEntryCommand::Execute()
{
	GameObjectAttorney::ConnectToScene(pGO);
	//pGO->ConnectToScene();
}