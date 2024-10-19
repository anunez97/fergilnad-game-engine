#include "AzulCore.h"
#include "Fergilnad.h"
#include "SceneManagerAttorney.h"
#include "TimeManagerAttorney.h"
#include "ShaderManagerAttorney.h"
#include "ModelManagerAttorney.h"
#include "TextureManagerAttorney.h"
#include "ImageManagerAttorney.h"
#include "VisualizerAttorney.h"
#include "BSphereCommandFactory.h"
#include "AABBCommandFactory.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "SpriteFontManagerAttorney.h"
#include "ScreenLogAttorney.h"
#include "TerrainManagerAttorney.h"

Fergilnad* Fergilnad::ptrInstance = nullptr;

//-----------------------------------------------------------------------------
// Fergilnad::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Fergilnad::Initialize()
{
	this->GameInitialize();
}

//-----------------------------------------------------------------------------
// Fergilnad::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Fergilnad::LoadContent()
{
	this->LoadDefaultAssets();

	this->LoadResources();

	SceneManagerAttorney::Engine::InitStartScene();

	//---------------------------------------------------------------------------------------------------------
	// Setup the current 3D perspective Camera
	//---------------------------------------------------------------------------------------------------------
}

void Fergilnad::LoadDefaultAssets()
{
	ModelManager::Load("SpriteModel", Model::PreMadeModels::UnitSquareXY);
	ModelManager::Load("Sphere", Model::PreMadeModels::UnitSphere);
	ModelManager::Load("Cube", Model::PreMadeModels::UnitBox_WF);

	TextureManager::Load("blue", 0, 0, 255);

	ShaderManager::Load("SpriteShader", "spriteRender");
}

//-----------------------------------------------------------------------------
// Fergilnad::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Fergilnad::Update()
{
	TimeManagerAttorney::ProcessTime(this->GetTime());

	SceneManagerAttorney::Engine::Update();

}

//-----------------------------------------------------------------------------
// Fergilnad::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Fergilnad::Draw()
{
	VisualizerAttorney::VisualizeAll();

	SceneManagerAttorney::Engine::Draw();

	ScreenLogAttorney::Render();
}

//-----------------------------------------------------------------------------
// Fergilnad::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Fergilnad::UnLoadContent()
{
	ModelManagerAttorney::Delete();
	ShaderManagerAttorney::Delete();
	TextureManagerAttorney::Delete();
	ImageManagerAttorney::Delete();
	SpriteFontManagerAttorney::Delete();
	TerrainManagerAttorney::Delete();

	SceneManagerAttorney::Engine::Delete();

	TimeManagerAttorney::Delete();

	VisualizerAttorney::Delete();

	ScreenLogAttorney::Delete();

	BSphereCommandFactory::Delete();
	AABBCommandFactory::Delete();


	this->GameEnd();
}

void Fergilnad::Run()
{
	Instance().run();

	delete ptrInstance;
}
