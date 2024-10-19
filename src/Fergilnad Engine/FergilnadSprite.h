// Fergilnad Sprite

#ifndef _FergilnadSprite
#define _FergilnadSprite

#include "AzulCore.h"

class FergilnadSprite
{
public:
	FergilnadSprite() = default;
	FergilnadSprite(const FergilnadSprite& other) = delete;
	FergilnadSprite& operator=(const FergilnadSprite& other) = delete;
	~FergilnadSprite();

	FergilnadSprite(std::string imgKey);
	
	/// <summary>
	/// Renders the Sprite 
	/// </summary>
	/// <param name="cam"> Pointer to the 2D Camera. </param>
	void Render(Camera* cam);

	/// <summary>
	/// Sets the Sprite's angle
	/// </summary>
	/// <param name="a"> Angle to rotate the sprite. </param>
	void SetAngle(float a);

	/// <summary>
	/// Sets the Sprite's center.
	/// </summary>
	/// <param name="offsetx"> X Position. </param>
	/// <param name="offsety"> Y Position. </param>
	void SetCenter(float offsetx, float offsety);

	/// <summary>
	/// Sets the Sprite's position
	/// </summary>
	/// <param name="x"> X Position </param>
	/// <param name="y"> Y Position </param>
	void SetPosition(float x, float y);

	/// <summary>
	/// Sets the scale factor for the sprite.
	/// </summary>
	/// <param name="scalex"> X scale. </param>
	/// <param name="scaley"> Y scale. </param>
	void SetScaleFactor(float scalex, float scaley);

	/// <summary>
	/// Sets the size of the width and height of the Sprite
	/// </summary>
	/// <param name="width"> Sets the width of the Sprite. </param>
	/// <param name="height"> Sets the height of the Sprite. </param>
	void SetScalePixel(float width, float height);

	/// <summary>
	/// Gets the Sprite's angle.
	/// </summary>
	/// <returns></returns>
	float GetAngle();

	/// <summary>
	/// Gets the Sprite's width.
	/// </summary>
	/// <returns></returns>
	float GetWidth();

	/// <summary>
	/// Gets the Sprite's height.
	/// </summary>
	/// <returns></returns>
	float GetHeight();

private:
	GraphicsObject_Sprite* pGOSprite;
	float angle;
	float posX;
	float posY;
	float centerX;
	float centerY;
	float scaleX;
	float scaleY;
	float scalePX;
	float scalePY;

};

#endif _FergilnadSprite