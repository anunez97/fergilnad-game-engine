// Game Object Exit Command

#include "GameObjectExitCommand.h"
#include "GameObjectAttorney.h"

GameObjectExitCommand::GameObjectExitCommand(GameObject* go)
	:pGO(go)
{
}

void GameObjectExitCommand::Execute()
{
	GameObjectAttorney::DisconnectToScene(pGO);
	//pGO->DisconnectToScene();
}