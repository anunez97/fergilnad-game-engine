// Game Object Entry Command

#ifndef _GameObjectEntryCommand
#define _GameObjectEntryCommand

#include "SceneRegistrationCommand.h"

class GameObject;

class GameObjectEntryCommand : public SceneRegistrationCommand
{
public:
	GameObjectEntryCommand() {};
	GameObjectEntryCommand(const GameObjectEntryCommand& other) = delete;
	GameObjectEntryCommand& operator=(const GameObjectEntryCommand& other) = delete;
	~GameObjectEntryCommand() {};

	GameObjectEntryCommand(GameObject* go);

	void Execute();

private:
	GameObject* pGO;
};

#endif _GameObjectEntryCommand
