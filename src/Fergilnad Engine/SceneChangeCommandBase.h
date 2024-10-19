// Scene Change Command Base

#ifndef _SceneChangeCommandBase
#define _SceneChangeCommandBase

#include "CommandBase.h"

class SceneChangeCommandBase : public CommandBase
{
public:
	SceneChangeCommandBase() {};
	SceneChangeCommandBase(const SceneChangeCommandBase& other) = delete;
	SceneChangeCommandBase& operator=(const SceneChangeCommandBase& other) = delete;
	virtual ~SceneChangeCommandBase() {};
};

#endif _SceneChangeCommandBase