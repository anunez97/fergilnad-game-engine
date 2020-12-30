// Axis

#include "Axis.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "Scene.h"

Axis::Axis()
{
	pModel = ModelManager::Get("Axis");
	pShader = ShaderManager::Get("ColorNoTexture");
	pAxis = new GraphicsObject_ColorNoTexture(pModel, pShader);

	Matrix world(IDENTITY);
	pAxis->SetWorld(world);

	Drawable::SubmitDrawRegistration();
}

void Axis::Draw()
{
	pAxis->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

Axis::~Axis()
{
	DebugMsg::out("Axis destructor\n");
	Drawable::SubmitDrawDeregistration();
	delete pAxis;
}