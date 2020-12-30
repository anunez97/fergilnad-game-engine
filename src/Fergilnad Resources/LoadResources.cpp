// Load Resources

#include "Fergilnad.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "SpriteFontManager.h"
#include "TerrainManager.h"
#include "..//User Code/LevelOne.h"
#include "..//User Code/SceneDemo.h"
#include "..//User Code/SceneTest.h"
#include "..//User Code/SceneOctreeTest.h"
#include "..//User Code/HUD.h"
#include "..//User Code/LevelTransition.h"

void Fergilnad::LoadResources()
{
	// Models
	ModelManager::Load("Axis", "Axis.azul");
	ModelManager::Load("Plane", "Plane.azul");
	ModelManager::Load("SpaceFrigate", "space_frigate.azul");
	ModelManager::Load("tankbody", "t99body.azul");
	ModelManager::Load("tankturret", "t99turret.azul");
	ModelManager::Load("tank1", "tank.azul");
	ModelManager::Load("tank2", "tank2.azul");
	ModelManager::Load("bullet", "bullet_case.azul");
	ModelManager::Load("Plane2", 10000, 100, 100);

	// Shaders
	ShaderManager::Load("TextureFlat", "textureFlatRender");
	ShaderManager::Load("TextureLight", "textureLightRender");
	ShaderManager::Load("ColorConstant", "colorConstantRender");
	ShaderManager::Load("ColorNoTexture", "colorNoTextureRender");

	// Textures
	TextureManager::Load("SpaceFrigate", "space_frigate.tga");
	TextureManager::Load("Grid", "grid.tga");
	TextureManager::Load("TankBody", "body.tga");
	TextureManager::Load("Stitch", "stitch.tga");
	TextureManager::Load("red", 255, 0, 0);
	TextureManager::Load("grass", "grass.tga");
	TextureManager::Load("gray", 128, 128, 128, 100);
	TextureManager::Load("bullet", "bullet_tex.tgs");

	// Image
	ImageManager::Load("Stitch", TextureManager::Get("Stitch"));

	// SpriteFonts
	SpriteFontManager::Load("ComicSans45", "ComicSans45");
	SpriteFontManager::Load("Arial30", "Arial30");
	SpriteFontManager::Load("Arial15", "Arial15");

	// Terrain
	TerrainManager::Load("terraintest", "HMTest.tga", 256, 35.0f, 0.0f, "grass", 10.0f, 10.0f);

	// Scene
	SceneManager::SetStartScene(new SceneTest());
	//SceneManager::SetStartScene(new LevelOne());
	//SceneManager::SetStartScene(new SceneOctreeTest());
	//SceneManager::SetStartScene(new LevelTransition());

	// For testing dup keys and keys that dont exist
	//TextureManager::Load("TestTexCol", 255, 0, 128);
	//TextureManager::Get("nokey");

}