// Frigate

#ifndef _Frigate
#define _Frigate

#include "GameObject.h"

class FrigateBSphere;
class Bullet;
class EnemyTank;

class Frigate : public GameObject
{
public:
	Frigate();
	Frigate(const Frigate& other) = delete;
	Frigate& operator=(const Frigate& other) = delete;
	~Frigate();

	virtual void Update();
	virtual void Draw();

	void Alarm0();
	void Alarm1();

	virtual void KeyPressed(AZUL_KEY k);
	virtual void KeyReleased(AZUL_KEY k);

	virtual void Collision(Collidable* ) {};
	virtual void Collision(EnemyTank* t);
	virtual void Collision(Frigate* fr);

	void SetWorld(Matrix world);

private:
	FrigateBSphere* pBSphere;
	GraphicsObject_TextureLight* pSpaceFrigateLight;
	Model* pModel;
	ShaderObject* pShader;
	Texture* pTexture;
	Vect Pos;

	Vect up3DCam;
	Vect lookAt3DCam;
	Vect pos3DCam;

	Matrix WorldMat;
	Matrix ScaleMat;
	Matrix RotateMat;

	const float ShipTransSpeed;
	const float ShipRotAng;

	bool BsphereToggle;
	bool bdebugCol;
};

#endif _Frigate