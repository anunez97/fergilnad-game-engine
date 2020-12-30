// Scene Octree Test

#ifndef _SceneOctreeTest
#define _SceneOctreeTest

#include "Scene.h"

class WorldPlane;

class SceneOctreeTest : public Scene
{
public:
	SceneOctreeTest();
	SceneOctreeTest(const SceneOctreeTest& other) = delete;
	SceneOctreeTest& operator=(const SceneOctreeTest& other) = delete;
	~SceneOctreeTest();

	virtual void Initialize();
	virtual void SceneEnd();

private:
	WorldPlane* pPlane;

};

#endif _SceneOctreeTest