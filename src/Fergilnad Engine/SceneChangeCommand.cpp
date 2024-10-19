// Scene Change Command

#include "SceneChangeCommand.h"
#include "SceneManagerAttorney.h"

SceneChangeCommand::SceneChangeCommand()
	:pScene(0)
{
}

void SceneChangeCommand::Execute()
{
	SceneManagerAttorney::SceneChange::ChangeScene(pScene);
}

void SceneChangeCommand::SetScene(Scene* s)
{
	pScene = s;
}

Scene* SceneChangeCommand::GetScene()
{
	return pScene;
}