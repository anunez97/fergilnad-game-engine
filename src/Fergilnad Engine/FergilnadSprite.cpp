// Fergilnad Sprite

#include "FergilnadSprite.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "ImageManager.h"

FergilnadSprite::FergilnadSprite(std::string imgKey)
	:angle(0.0f), scaleX(1.0f), scaleY(1.0f), scalePX(1.0f), scalePY(1.0f), posX(0.0f), posY(0.0f)
{

	Rect* r = new Rect(0.0f, 0.0f, ImageManager::Get(imgKey)->pImageRect->width, ImageManager::Get(imgKey)->pImageRect->height);
	pGOSprite = new GraphicsObject_Sprite(ModelManager::Get("SpriteModel"), ShaderManager::Get("SpriteShader"), ImageManager::Get(imgKey), r);

	Matrix Scale = Matrix(SCALE, 1.0f, 1.0f, 1.0f);
	Matrix RotZ = Matrix(ROT_Z, 0.0f);
	Matrix Trans = Matrix(TRANS, pGOSprite->origPosX, pGOSprite->origPosY, 0.0f);

	centerX = pGOSprite->origPosX;
	centerY = pGOSprite->origPosY;

	Matrix world = Scale * RotZ * Trans;
	pGOSprite->SetWorld(world);

	delete r;
}

FergilnadSprite::~FergilnadSprite()
{
	DebugMsg::out("Sprite destructor\n");
	delete pGOSprite;
}

void FergilnadSprite::Render(Camera* cam)
{
	pGOSprite->Render(cam);
}

void FergilnadSprite::SetAngle(float a)
{
	angle = a;

	Matrix world = Matrix(SCALE, scaleX * scalePX, scaleY * scalePY, 1.0f) * Matrix(ROT_Z, angle) * Matrix(TRANS, posX + centerX, posY + centerY, 0.0f);

	pGOSprite->SetWorld(world);
}

void FergilnadSprite::SetCenter(float offsetx, float offsety)
{
	centerX = offsetx;
	centerY = offsety;

	Matrix world = Matrix(SCALE, scaleX * scalePX, scaleY * scalePY, 1.0f) * Matrix(ROT_Z, angle) * Matrix(TRANS, posX + centerX, posY + centerY, 0.0f);

	pGOSprite->SetWorld(world);
}

void FergilnadSprite::SetPosition(float x, float y)
{
	posX = x;
	posY = y;

	Matrix world = Matrix(SCALE, scaleX * scalePX, scaleY * scalePY, 1.0f) * Matrix(ROT_Z, angle) * Matrix(TRANS, posX + centerX, posY + centerY, 0.0f);

	pGOSprite->SetWorld(world);
}

void FergilnadSprite::SetScaleFactor(float scalex, float scaley)
{
	scaleX = scalex;
	scaleY = scaley;

	Matrix world = Matrix(SCALE, scaleX * scalePX, scaleY * scalePY, 1.0f) * Matrix(ROT_Z, angle) * Matrix(TRANS, posX + centerX, posY + centerY, 0.0f);

	pGOSprite->SetWorld(world);
}

void FergilnadSprite::SetScalePixel(float width, float height)
{
	scalePX = width / pGOSprite->origWidth;
	scalePY = height / pGOSprite->origHeight;

	Matrix world = Matrix(SCALE, scaleX * scalePX, scaleY * scalePY, 1.0f) * Matrix(ROT_Z, angle) * Matrix(TRANS, posX + centerX, posY + centerY, 0.0f);
	
	pGOSprite->SetWorld(world);

	DebugMsg::out("scale pixel set\n");
}

float FergilnadSprite::GetAngle()
{
	return angle;
}

float FergilnadSprite::GetWidth()
{
	return pGOSprite->origWidth;
}

float FergilnadSprite::GetHeight()
{
	return pGOSprite->origHeight;
}