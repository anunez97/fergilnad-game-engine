// World Plane

#ifndef _WorldPlane
#define _WorldPlane

#include "GameObject.h"
#include "Terrain.h"
#include "CollisionOctree.h"

class Axis;
class Tank;

class WorldPlane : public GameObject
{
public:
	WorldPlane();
	WorldPlane(const WorldPlane& other) = default;
	WorldPlane& operator=(const WorldPlane& other) = default;
	~WorldPlane();

	virtual void Draw();
	virtual void KeyPressed(AZUL_KEY k);

private:
	Axis* pAxis;
	GraphicsObject_TextureFlat* pPlane;
	Model* pModel;
	ShaderObject* pShader;
	Texture* pTexture;
	Terrain* pTerrain;
	CollisionOctree* pOctree;
	Matrix world;
	Vect testpos;
	Tank* tank;
	Tank* tank2;
	Tank* tank3;
	Tank* tank4;
};

#endif _WorldPlane