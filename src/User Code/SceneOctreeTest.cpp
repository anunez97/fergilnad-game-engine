// Scene Octree Test

#include "SceneOctreeTest.h"

#include "Fergilnad.h"
#include "WorldPlane.h"

SceneOctreeTest::SceneOctreeTest()
{
}

SceneOctreeTest::~SceneOctreeTest()
{
	DebugMsg::out("SceneOctreeTest destructor\n");
}

void SceneOctreeTest::Initialize()
{
	Camera* pCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	pCam->setViewport(0, 0, Fergilnad::GetWidth(), Fergilnad::GetHeight());
	pCam->setPerspective(35.0f, float(Fergilnad::GetWidth()) / float(Fergilnad::GetHeight()), 1.0f, 5000.0f);
	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(50.0f, 50.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);

	pCam->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	SetCurrentCamera(pCam);
	GetCurrentCamera()->updateCamera();

	pPlane = new WorldPlane();

	SetCollisionArea(5);
}

void SceneOctreeTest::SceneEnd()
{
	delete pPlane;
}