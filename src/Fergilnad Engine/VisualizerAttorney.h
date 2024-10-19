// Visualizer

#ifndef _VisualizerAttorney
#define _VisualizerAttorney

#include "Visualizer.h"

class VisualizerAttorney
{
	friend class Fergilnad;
	static void VisualizeAll() { Visualizer::VisualizeAll(); }
	static void Delete() { Visualizer::Delete(); }
	
public:
	class Render
	{
		friend class VisualizeBSphereCommand;
		friend class VisualizeAABBCommand;

		static void BSphere(Matrix &m, const Vect &col) { Visualizer::RenderBSphere(m, col); }
		static void AABB(Matrix& m, const Vect& col) { Visualizer::RenderAABB(m, col); }
	};

public:
	class Show
	{
		friend class CollisionVolumeBSphere;
		friend class CollisionVolumeAABB;
		friend class CollisionVolumeOBB;
		friend class FGNMathTools;
		friend class CollisionTestPairCommand;
		friend class CollisionTestSelfCommand;
		friend class Terrain;
		friend class OctreeNode;
		friend class CollisionOctree;
		friend class CollisionTestTerrain;
		friend class OctreePairTestCommand;
		friend class OctreeSelfTestCommand;

		static void BSphere(const CollisionVolumeBSphere& S, const Vect& col) { Visualizer::ShowBSphere(S, col); }
		static void AABB(const CollisionVolumeAABB& A, const Vect& col) { Visualizer::ShowAABB(A, col); }
		static void AABB(const Vect& min, const Vect& max, const Vect& col) { Visualizer::ShowAABB(min, max, col); }
		static void OBB(const CollisionVolumeOBB& O, const Vect& col) { Visualizer::ShowOBB(O, col); }
		static void Point(const Vect& v, const Vect& col) { Visualizer::ShowPoint(v, col); }
		static void Axis(const Vect& v, const Vect& col) { Visualizer::ShowAxis(v, col); }
		static void Line(const Vect& start, const Vect& end, const Vect& col) { Visualizer::ShowLine(start, end, col); }
	};
};

#endif _VisualizerAttorney