// God Cam

#ifndef _GodCam
#define _GodCam

#include "GameObject.h"

class CameraManager;

class GodCam : public GameObject
{
public:
	GodCam() = default;
	GodCam(const GodCam& other) = delete;
	GodCam& operator=(const GodCam& other) = delete;
	~GodCam();

	GodCam(CameraManager* pCamMgr);

	/// <summary>
	/// Updates the camera
	/// </summary>
	void Update();

	/// <summary>
	/// Moves the camera forward
	/// </summary>
	void MoveForward();
	/// <summary>
	/// Moves the camera backwards
	/// </summary>
	void MoveBackward();

	/// <summary>
	/// Turns the camera left
	/// </summary>
	void TurnLeft();

	/// <summary>
	/// Turns the camera right
	/// </summary>
	void TurnRight();

	/// <summary>
	/// Turns the camera up
	/// </summary>
	void LookUp();

	/// <summary>
	/// Turns the camera down
	/// </summary>
	void LookDown();

	void KeyPressed(AZUL_KEY k);

	/// <summary>
	/// Returns the camera
	/// </summary>
	/// <returns></returns>
	Camera* GetCamera();

private:
	Vect Position;
	Matrix Rotate;

	CameraManager* pCamMgr;
	Camera* pCam;
	bool Active;
	const float speed;
	const float rotangle;

};

#endif _GodCam