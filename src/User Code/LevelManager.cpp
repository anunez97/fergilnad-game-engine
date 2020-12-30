// Level Manager

#include "LevelManager.h"
#include "SceneManager.h"
#include "LevelOne.h"
#include "LevelTwo.h"

LevelManager* LevelManager::ptrInstance = nullptr;

LevelManager::LevelManager()
{
	level = 0;
}

LevelManager::~LevelManager()
{

}

void LevelManager::privLoadLevel(Level lvl)
{
	switch (lvl)
	{
	case Level::LEVEL1:
		SceneManager::SetNextScene(new LevelOne());
		break;
	case Level::LEVEL2:
		SceneManager::SetNextScene(new LevelTwo());
		break;
	}
}

void LevelManager::privLoadNextLevel()
{
	SceneManager::SetNextScene(GetLevel(++level));
}

Scene* LevelManager::GetLevel(int lvl)
{
	Level l = static_cast<Level>(lvl);

	switch (l)
	{
	case Level::LEVEL1:
		return new LevelOne();
	case Level::LEVEL2:
		return new LevelTwo();
	default:
		return new LevelOne();
	}
}

void LevelManager::privDelete()
{
	delete ptrInstance;

	ptrInstance = nullptr;
}