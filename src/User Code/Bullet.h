// Bullet

#ifndef _Bullet
#define _Bullet

#include "GameObject.h"

class EnemyTank;

class Bullet : public GameObject
{
public:
	Bullet();
	Bullet(const Bullet& other) = delete;
	Bullet& operator=(const Bullet& other) = delete;
	~Bullet();

	virtual void SceneEntry();
	virtual void SceneExit();

	virtual void Update();
	virtual void Draw();

	void Alarm0();

	virtual void Collision(Collidable*) {};
	virtual void Collision(EnemyTank* );

	void Initialize(Matrix rot, Vect pos);

private:
	//GraphicsObject_ColorNoTexture* pBulletLight;
	GraphicsObject_TextureFlat* pBulletLight;
	Model* pModel;
	ShaderObject* pShader;
	Texture* pTexture;
	Vect Pos;

	Matrix WorldMat;
	Matrix ScaleMat;
	Matrix RotateMat;

	const float BulletSpeed;
};

#endif _Bullet