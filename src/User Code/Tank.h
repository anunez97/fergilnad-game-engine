// Tank

#ifndef _Tank
#define _Tank

#include "AzulCore.h"
#include "GameObject.h"

class Frigate;

class Tank : public GameObject
{
public:
	Tank();
	Tank(const Tank& other) = delete;
	Tank& operator=(const Tank& other) = delete;
	~Tank();

	virtual void Update();
	virtual void Draw();

	virtual void KeyPressed(AZUL_KEY k);
	virtual void KeyReleased(AZUL_KEY k);

	virtual void Collision(Collidable* ) {};
	virtual void Collision(Frigate* fr);
	virtual void Collision(Tank* t);

	void MoveTo(Vect pos);
	void RegisterCollision();
	void UpdateWorld(Matrix rotate, Vect pos);

private:
	GraphicsObject_TextureFlat* pBody;
	//GraphicsObject_TextureFlat* pTurret;

	Matrix WorldMat;
	Matrix ScaleMat;
	Matrix RotateMat;

	Vect Pos;
	Vect turretend;

	const float speed;
	const float rotAngle;
	const float turretOffset;

};

#endif _Tank