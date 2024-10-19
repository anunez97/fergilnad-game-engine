#include "AzulCore.h"
#include "Fergilnad.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "ModelManager.h"

// Global varables just for the demo:
// Note: Don't do this!
// Global vars should always be avoided in a finished product! 
Camera *pCam3D;

GraphicsObject_TextureFlat *pGObj_Plane;
GraphicsObject_ColorNoTexture *pGObj_Axis;
GraphicsObject_TextureLight *pGObj_SpaceFrigateLight;
GraphicsObject_WireframeConstantColor *pGObj_SpaceshipBSphere;

// Spaceship vars
Matrix ShipScale;
Vect ShipPos;
Matrix ShipRot;
const float ShipTransSpeed = 1;
const float ShipRotAng = .05f;
bool BsphereToggle = false;

// Camera vars
const Vect CamShipOffset(0, 70, -150);
const Vect CamLookAt(0, 0, 0);

//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Fergilnad::Initialize()
{
	// Game Window Device setup
	//this->setWindowName("Matrices and Movement");
	//this->setWidthHeight(800, 600);
	//this->SetClearColor(0.4f, 0.4f, 0.8f, 1.0f);

	// Use this area, for one time non-graphic creation
	this->GameInitialize();
}

//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Fergilnad::LoadContent()
{
	this->LoadResources();

	//---------------------------------------------------------------------------------------------------------
	// Graphics Objects
	//---------------------------------------------------------------------------------------------------------

	pGObj_Plane = new GraphicsObject_TextureFlat(ModelManager::Get("Plane"), ShaderManager::Get("TextureFlat"), TextureManager::Get("Grid"));
	pGObj_Axis = new GraphicsObject_ColorNoTexture(ModelManager::Get("Axis"), ShaderManager::Get("ColorNoTexture"));

	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_SpaceFrigateLight = new GraphicsObject_TextureLight(ModelManager::Get("SpaceFrigate"), ShaderManager::Get("TextureLight"), TextureManager::Get("SpaceFrigate"), LightColor, LightPos);

	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);
	pGObj_SpaceshipBSphere = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Sphere"), ShaderManager::Get("ColorConstant"), Blue);


	// Creating matrices for in-world placement
	Matrix world;

	// Axis and Plane
	world = Matrix(IDENTITY);
	pGObj_Axis->SetWorld(world);
	world = Matrix(SCALE, 400, 400, 400);
	pGObj_Plane->SetWorld(world);

	// Spaceship
	ShipScale.set(SCALE, 0.5f, 0.5f, 0.5f);
	ShipRot.set(IDENTITY);
	ShipPos.set(0, 20, 0);
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);


	//---------------------------------------------------------------------------------------------------------
	// Setup the current 3D perspective Camera
	//---------------------------------------------------------------------------------------------------------

	pCam3D = new Camera(Camera::Type::PERSPECTIVE_3D);
	pCam3D->setViewport(0, 0, this->getWidth(), this->getHeight());
	pCam3D->setPerspective(35.0f, float(this->getWidth()) / float(this->getHeight()), 1.0f, 5000.0f);

	// Orient Camera
	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(50.0f, 50.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);
	pCam3D->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	pCam3D->updateCamera();  // Note: if the camera moves/changes, we need to call update again
}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Fergilnad::Update()
{
	// Ship translation movement (not using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
		ShipPos += Vect(0, 0, 1) * ShipRot * ShipTransSpeed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	{
		ShipPos += Vect(0, 0, 1) * ShipRot * -ShipTransSpeed;
	}

	// Ship Rotation movement (not using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
	{
		ShipRot *= Matrix(ROT_Y, ShipRotAng);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
	{
		ShipRot *= Matrix(ROT_Y, -ShipRotAng);
	}

	// Spaceship adjust matrix
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);

	/*
	// Placing the camera relative to the spaceship
	Matrix ShipRotPos = ShipRot * Matrix(TRANS, ShipPos);  // This is the worldmat without scaling
	Vect vNewCamPos = CamLookAt * ShipRotPos;		// This moves the cam position relative to ship's position and rotation
	Vect vNewLookAt = CamShipOffset * ShipRotPos;   // This moves the look-at point relative to ship's position and rotation
	pCam3D->setOrientAndPosition( Vect(0, 1, 0), vNewCamPos, vNewLookAt);
	pCam3D->updateCamera();
	//*/

	//*
	// Adjusting the spaceship's bounding sphere
	Vect vBSSize = pGObj_SpaceFrigateLight->getModel()->getRadius() * Vect(1, 1, 1);
	Vect vBSPos = pGObj_SpaceFrigateLight->getModel()->getCenter();

	// Adjust the Bounding Sphere's position and scale to fit the Ship's center and scale
	Matrix worldBS = Matrix(SCALE, vBSSize) * Matrix(TRANS, vBSPos) * world;

	pGObj_SpaceshipBSphere->SetWorld(worldBS);

	// Toggle the bounding sphere's visibility
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_SPACE))
	{
		BsphereToggle = true;
		DebugMsg::out("Bounding sphere: On\n");
	}
	else
	{
		BsphereToggle = false;
		DebugMsg::out("Bounding sphere: Off\n");
	}
	//*/
}

//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Fergilnad::Draw()
{
	// draw all objects
	pGObj_Plane->Render(pCam3D);
	pGObj_Axis->Render(pCam3D);
	pGObj_SpaceFrigateLight->Render(pCam3D);

	if (BsphereToggle)
	{
		pGObj_SpaceshipBSphere->Render(pCam3D);
	}

}



//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Fergilnad::UnLoadContent()
{
	// general clean up.

	// (also: we should call 'delete' on all these global pointers we created... )
	delete pCam3D;

	delete pGObj_Plane;
	delete pGObj_Axis; 
	delete pGObj_SpaceFrigateLight;
	delete pGObj_SpaceshipBSphere;

	ShaderManager::Delete();
	TextureManager::Delete();
	ModelManager::Delete();

	// Again, we are missing the shaders, textures, etc...
}

void Fergiland::Run()
{
	Instance().Run();
}


