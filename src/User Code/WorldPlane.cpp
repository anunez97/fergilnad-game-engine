// World Plane

#include "WorldPlane.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Axis.h"
#include "SceneTest.h"
#include "Visualizer.h"
#include "PlayerManager.h"
#include "PlayerTank.h"
#include "Tank.h"

WorldPlane::WorldPlane()
{
	//pOctree = new CollisionOctree();
	//pOctree->CreateTree(10, 10.0f);
	//pAxis = new Axis();
	pModel = ModelManager::Get("Plane2");
	pShader = ShaderManager::Get("TextureFlat");
	pTexture = TextureManager::Get("grass");
	Vect v1(52.0f, 46.63f, 51.65f);
	Vect v2(52.0f, 400.63f, 51.65f);
	Vect v3(49.0f, -84.63f, 49.65f);
	Vect v4(-49.0f, -84.63f, 49.65f);
	tank = new Tank();
	tank2 = new Tank();
	tank3 = new Tank();
	tank4 = new Tank();
	tank->MoveTo(v1);
	tank2->MoveTo(v2);
	tank3->MoveTo(v3);
	tank4->MoveTo(v4);
	tank->RegisterCollision();
	tank2->RegisterCollision();
	tank3->RegisterCollision();
	tank4->RegisterCollision();
	//pOctree->InsertObject(tank);
	pPlane = new GraphicsObject_TextureFlat(pModel, pShader, pTexture);
	//pTerrain = new Terrain(16, 0.0f, "grass", 1.0f, 1.0f);
	//pTerrain = new Terrain("../../Assets/Textures/test.tga", 16);
	//pTerrain = new Terrain("../../Assets/Textures/test", 16);
	//pTerrain = new Terrain("Textures/HMTest16.tga", 16, 5.0f, 5.0f, "grass", 5.0f, 5.0f);
	//pTerrain = new Terrain("Textures/HMTest.tga", 256, 35.0f, 0.0f, "grass", 5.0f, 5.0f);

	testpos.set(-127.6f, 20.63f, 0.0f);

	world = Matrix(SCALE, 1.0f, 1.0f, 1.0f);
	pPlane->SetWorld(world);

	Drawable::SubmitDrawRegistration();
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ENTER, InputEventType::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_BACKSLASH, InputEventType::KEY_PRESS);
}

void WorldPlane::Draw()
{
	//pOctree->Render();
	//pPlane->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
	//pTerrain->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
	//pTerrain->GetCellFromPos(PlayerManager::GetPlayer()->GetPos());
	//Visualizer::ShowPoint(PlayerManager::GetPlayer()->GetPos(), Color::Red);
}

void WorldPlane::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_ENTER:
		tank2->SubmitCollisionDeregistration();
		break;
	case AZUL_KEY::KEY_BACKSLASH:
		tank3->MoveTo(Vect(52.0f, 150.63f, 51.65f));
		DebugMsg::out("Tank moved to new octant ");
		break;
	}
}

WorldPlane::~WorldPlane()
{
	DebugMsg::out("WorldPlane destructor\n");
	//Drawable::SubmitDrawDeregistration();
	delete pPlane;
	//delete pAxis;
	//delete pTerrain;
	//delete pOctree;
	delete tank;
	delete tank2;
	delete tank3;
	delete tank4;
}