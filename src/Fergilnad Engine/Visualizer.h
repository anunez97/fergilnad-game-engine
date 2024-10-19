// Visualizer

#ifndef _Visualizer
#define _Visualizer

#include "AzulCore.h"
#include "Color.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include <list>

class VisualizeCommandBase;

class Visualizer : public Align16
{
	friend class VisualizerAttorney;

private:
	static Visualizer* ptrInstance;

	static Visualizer& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new Visualizer;
		return *ptrInstance;
	}

	Visualizer();
	Visualizer(const Visualizer& other) = delete;
	Visualizer& operator=(const Visualizer& other) = delete;
	~Visualizer();

	static void Delete();

	void privRenderBSphere(Matrix& S, const Vect& col);
	static void RenderBSphere(Matrix& m, const Vect& col) { Instance().privRenderBSphere(m, col); }

	void privRenderAABB(Matrix& m, const Vect& col);
	static void RenderAABB(Matrix& m, const Vect& col) { Instance().privRenderAABB(m, col); }

	void privRenderOBB(Matrix& m, const Vect& col);
	static void RenderOBB(Matrix& m, const Vect& col) { Instance().privRenderOBB(m, col); }

	static void privVisualizeAll();
	static void VisualizeAll() { Instance().privVisualizeAll(); }

	/// <summary>
	/// Submits a command to have a GameObjects BSphere be visualized.
	/// </summary>
	/// <param name="S"> Constant reference to the GameObjects BSphere. </param>
	/// <param name="col"> Color that the BSphere will be rendered in. </param>
	static void ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col);

	/// <summary>
	/// Submits a command to have a GameObject's AABB be visualized.
	/// </summary>
	/// <param name="A"> Reference to the AABB. </param>
	/// <param name="col"> Color that the AABB will be rendered in. </param>
	static void ShowAABB(const CollisionVolumeAABB& A, const Vect& col);

	/// <summary>
	/// Submits a command to have a GameObject's OBB be visualized
	/// </summary>
	/// <param name="O"> Constant reference to the OBB.</param>
	/// <param name="col"> Color that the OBB will be rendered in.</param>
	static void ShowOBB(const CollisionVolumeOBB& O, const Vect& col);
	
	/// <summary>
	/// Submits a command to show a point on scene
	/// </summary>
	/// <param name="v"> Point vector to be visualized</param>
	/// <param name="col"> Color that the point will be rendered in.</param>
	static void privShowPoint(const Vect& v, const Vect& col);

	static void ShowLine(const Vect& start, const Vect& end, const Vect& col);

	static void ShowAxis(const Vect& v, const Vect& col);

	static void ShowAABB(const Vect& min, const Vect& max, const Vect& col);

	static Vect DEFAULT_COLOR;

	GraphicsObject_WireframeConstantColor* WFUnitSphere;
	GraphicsObject_WireframeConstantColor* WFUnitCube;

	using VisualizerCmds = std::list<VisualizeCommandBase*>;
	VisualizerCmds cmdList;

public:
	/// <summary>
	/// Submits a command to have a GameObject's Collision Volume to be rendered.
	/// </summary>
	/// <param name="c"> Constant reference to the GameObject's Collision Volume. </param>
	/// <param name="col"> Color that the Collision Volume will be rendered in. </param>
	static void ShowCollisionVolume(const CollisionVolume& c, const Vect& col);

	/// <summary>
	/// Submits a command to show a point on scene
	/// </summary>
	/// <param name="v"> Point vector to be visualized</param>
	/// <param name="col"> Color that the point will be rendered in.</param>
	static void ShowPoint(const Vect& v, const Vect& col) { Instance().privShowPoint(v, col); }
};

#endif _Visualizer