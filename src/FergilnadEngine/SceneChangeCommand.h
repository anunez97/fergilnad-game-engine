// Scene Change Command

#ifndef _SceneChangeCommand
#define _SceneChangeCommand

#include "SceneChangeCommandBase.h"

class Scene;

class SceneChangeCommand : public SceneChangeCommandBase
{
public:
	SceneChangeCommand();
	SceneChangeCommand(const SceneChangeCommand& other) = delete;
	SceneChangeCommand& operator=(const SceneChangeCommand& other) = delete;
	~SceneChangeCommand() {};

	virtual void Execute();
	void SetScene(Scene* s);
	Scene* GetScene();

private:
	Scene* pScene;

};

#endif _SceneChangeCommand