// Axis

#ifndef _Axis
#define _Axis

#include "GameObject.h"

class Axis : public GameObject
{
public:
	Axis();
	Axis(const Axis& other) = default;
	Axis& operator=(const Axis& other) = default;
	~Axis();

	virtual void Draw();

private:
	GraphicsObject_ColorNoTexture* pAxis;
	Model* pModel;
	ShaderObject* pShader;
};

#endif _Axis