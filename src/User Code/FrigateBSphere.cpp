#include "FrigateBSphere.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "Scene.h"

FrigateBSphere::FrigateBSphere()
	:BsphereToggle(false)
{
	pBSphereModel = ModelManager::Get("Sphere");
	pBSphereShader = ShaderManager::Get("ColorConstant");
	BSphereColor = Vect(0.0f, 0.0f, 1.0f, 1.0f);

	pSpaceShip_BSphere = new GraphicsObject_WireframeConstantColor(pBSphereModel, pBSphereShader, BSphereColor);

	Drawable::SubmitDrawRegistration();
}

void FrigateBSphere::Draw()
{
	pSpaceShip_BSphere->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void FrigateBSphere::SetWorld(Matrix world)
{
	pSpaceShip_BSphere->SetWorld(world);
}

void FrigateBSphere::SetToggle(bool toggle)
{
	BsphereToggle = toggle;
}

FrigateBSphere::~FrigateBSphere()
{
	DebugMsg::out("Frigate Bounding Sphere destructor\n");
	delete pSpaceShip_BSphere;
}