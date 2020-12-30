// Frigate Bounding Sphere

#ifndef _FrigateBSphere
#define _FrigateBSphere

#include "AzulCore.h"
#include "GameObject.h"

class FrigateBSphere : public GameObject
{
public:
	FrigateBSphere();
	FrigateBSphere(const FrigateBSphere& other) = default;
	FrigateBSphere& operator=(const FrigateBSphere& other) = default;
	~FrigateBSphere();

	virtual void Draw();

	void SetWorld(Matrix world);
	void SetToggle(bool toggle);

private:
	GraphicsObject_WireframeConstantColor* pSpaceShip_BSphere;
	Model* pBSphereModel;
	ShaderObject* pBSphereShader;
	Vect BSphereColor;
	bool BsphereToggle;
};

#endif _FrigateBSphere