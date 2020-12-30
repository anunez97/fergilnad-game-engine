// Scene Null

#ifndef _SceneNull
#define _SceneNull

#include "Scene.h"

class SceneNull : public Scene
{
public:
	SceneNull() {};
	SceneNull(const SceneNull& other) = delete;
	Scene& operator=(const SceneNull& other) = delete;
	~SceneNull() {};

	virtual void Initialize() {};
	virtual void SceneEnd() {};
};

#endif _SceneNull