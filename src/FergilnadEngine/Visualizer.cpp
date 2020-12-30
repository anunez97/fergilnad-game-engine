// Visualizer

#include "Visualizer.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "VisualizeBSphereCommand.h"
#include "BSphereCommandFactory.h"
#include "AABBCommandFactory.h"
#include "VisualizeAABBCommand.h"
#include "ScreenLog.h"

Visualizer* Visualizer::ptrInstance = nullptr;
Vect Visualizer::DEFAULT_COLOR = Vect(0, 0, 255);

Visualizer::Visualizer()
	:WFUnitSphere(0)
{
	WFUnitSphere = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Sphere"), ShaderManager::Get("ColorConstant"), DEFAULT_COLOR);
	WFUnitCube = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Cube"), ShaderManager::Get("ColorConstant"), DEFAULT_COLOR);
}

Visualizer::~Visualizer()
{
	delete WFUnitSphere;
	delete WFUnitCube;
}

void Visualizer::Delete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

void Visualizer::privRenderBSphere(Matrix& S, const Vect& col = Visualizer::DEFAULT_COLOR)
{
	WFUnitSphere->SetColor(col);

	WFUnitSphere->SetWorld(S);

	WFUnitSphere->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void Visualizer::ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col = DEFAULT_COLOR)
{
	Matrix world = Matrix(SCALE, S.GetRadius(), S.GetRadius(), S.GetRadius()) * S.GetRotate() * Matrix(TRANS, S.GetCenter());

	Matrix& m = world;

	Instance().cmdList.push_back(BSphereCommandFactory::CreateCommand(m, col));
}

void Visualizer::privRenderAABB(Matrix& m, const Vect& col = Visualizer::DEFAULT_COLOR)
{
	WFUnitCube->SetColor(col);

	WFUnitCube->SetWorld(m);

	WFUnitCube->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void Visualizer::ShowAABB(const CollisionVolumeAABB& A, const Vect& col = DEFAULT_COLOR)
{
	Vect max = A.GetCornerMax();
	Vect min = A.GetCornerMin();

	Matrix world = Matrix(SCALE, max - min) * Matrix(ROT_Y, 0) * Matrix(TRANS, .5f * (max + min));

	Matrix& m = world;

	Instance().cmdList.push_back(AABBCommandFactory::CreateCommand(m, col));
}

void Visualizer::ShowAABB(const Vect& min, const Vect& max, const Vect& col = DEFAULT_COLOR)
{
	Matrix world = Matrix(SCALE, max - min) * Matrix(ROT_Y, 0) * Matrix(TRANS, .5f * (max + min));

	Matrix& m = world;

	Instance().cmdList.push_back(AABBCommandFactory::CreateCommand(m, col));
}

void Visualizer::privRenderOBB(Matrix& m, const Vect& col = Visualizer::DEFAULT_COLOR)
{
	WFUnitCube->SetColor(col);

	WFUnitCube->SetWorld(m);

	WFUnitCube->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void Visualizer::ShowOBB(const CollisionVolumeOBB& O, const Vect& col = DEFAULT_COLOR)
{
	Vect max = O.GetCornerMax();
	Vect min = O.GetCornerMin();

	Matrix local = Matrix(SCALE, max - min) * Matrix(TRANS, .5f * (max + min));
	local *= O.GetWorld();

	Matrix& m = local;

	Instance().cmdList.push_back(AABBCommandFactory::CreateCommand(m, col));
}

void Visualizer::privShowPoint(const Vect& v, const Vect& col = DEFAULT_COLOR)
{
	Matrix world = Matrix(SCALE, .1f, .1f, .1f) * Matrix(TRANS, v);

	Matrix& m = world;

	Instance().cmdList.push_back(BSphereCommandFactory::CreateCommand(m, col));
}

void Visualizer::ShowLine(const Vect& start, const Vect& end, const Vect& col = DEFAULT_COLOR)
{
	//Matrix world = Matrix(SCALE, .5f, .01f, .5f) * Matrix(TRANS, end - start);
	//Matrix world = Matrix(SCALE, Vect(.01f, 1.0f, .01f)) * Matrix(ROT_Y, 0) * Matrix(TRANS, .5f * (end + start));

	//Matrix& m = world;

	//Instance().cmdList.push_back(AABBCommandFactory::CreateCommand(m, col));

	float angle = start.dot(end) / (start.mag() * end.mag());

	Matrix world = Matrix(SCALE, Vect(.001f, 1.0f, .001f)) * Matrix(ROT_AXIS_ANGLE, end - start, angle) * Matrix(TRANS, (end + start) *.5f);

	Matrix& m = world;

	Instance().cmdList.push_back(AABBCommandFactory::CreateCommand(m, col));
}

void Visualizer::ShowAxis(const Vect& v, const Vect& col = DEFAULT_COLOR)
{
	//Matrix world = Matrix(SCALE, 0.5f, 0.5f, 0.5f) * Matrix(TRANS, v);
	Matrix world = Matrix(SCALE, Vect(0.0f, 0, 20.0f)) * Matrix(TRANS, v + Vect(0, 10.0f, 0));

	Matrix& m = world;

	Instance().cmdList.push_back(AABBCommandFactory::CreateCommand(m, col));
}

void Visualizer::ShowCollisionVolume(const CollisionVolume& c, const Vect& col = DEFAULT_COLOR)
{
	c.DebugView(col);
}

void Visualizer::privVisualizeAll()
{
	for (VisualizerCmds::iterator it = Instance().cmdList.begin(); it != Instance().cmdList.end(); it++)
	{
		(*it)->Execute();

		(*it)->Return();
	}

	Instance().cmdList.clear();
}