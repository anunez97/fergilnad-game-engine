// Scene Manager Attorney

#ifndef _SceneManagerAttorney
#define _SceneManagerAttorney

#include "SceneManager.h"

class SceneManagerAttorney
{
public:
	class Engine
	{
		friend class Fergilnad;
	private:
		static void InitStartScene() { SceneManager::InitStartScene(); }
		static void Update() { SceneManager::Update(); }
		static void Draw() { SceneManager::Draw(); }
		static void Delete() { SceneManager::Delete(); }
	};

public:
	class SceneChange
	{
		friend class SceneChangeCommand;
	private:
		static void ChangeScene(Scene* s) { SceneManager::ChangeScene(s); }
	};
};

#endif _SceneManagerAttorney