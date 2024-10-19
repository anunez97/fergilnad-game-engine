// Scene Change Null Command

#ifndef _SceneChangeNullCommand
#define _SceneChangeNullCommand

#include "SceneChangeCommandBase.h"

class SceneChangeNullCommand : public SceneChangeCommandBase
{
public:
	SceneChangeNullCommand() {};
	SceneChangeNullCommand(const SceneChangeNullCommand& other) = delete;
	SceneChangeNullCommand& operator=(const SceneChangeNullCommand& other) = delete;
	~SceneChangeNullCommand() {};

	virtual void Execute() {};

private:


};

#endif _SceneChangeNullCommand