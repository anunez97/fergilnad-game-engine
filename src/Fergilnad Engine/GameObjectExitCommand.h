// Game Object Exit Command

#ifndef _GameObjectExitCommand
#define _GameObjectExitCommand

#include "SceneRegistrationCommand.h"

class GameObject;

class GameObjectExitCommand : public SceneRegistrationCommand
{
public:
	GameObjectExitCommand() = default;
	GameObjectExitCommand(const GameObjectExitCommand& other) = delete;
	GameObjectExitCommand& operator=(const GameObjectExitCommand& other) = delete;
	~GameObjectExitCommand() {};

	GameObjectExitCommand(GameObject* go);

	void Execute();

private:
	GameObject* pGO;
};

#endif _GameObjectExitCommand