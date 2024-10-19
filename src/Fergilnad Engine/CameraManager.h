// Camera Manager

#ifndef _CameraManager
#define _CameraManager

#include "AzulCore.h"

class GodCam;

class CameraManager
{
public:
	CameraManager();
	CameraManager(const CameraManager& other) = delete;
	CameraManager& operator=(const CameraManager& other) = delete;
	~CameraManager();

	/// <summary>
	/// Method that gives access to the current scene's current 3D camera.
	/// </summary>
	/// <returns> Returns a pointer to the scene's current 3D Camera. </returns>
	Camera* GetCurrentCamera();

	/// <summary>
	/// Gives access to the current scene's current 2D Camera.
	/// </summary>
	/// <returns> Returns a pointer the scene's current 2D Camera. </returns>
	Camera* GetCurrentCamera2D();

	/// <summary>
	/// Allows the user to set a custom camera as the scene's current camera.  By default, the Camera Manager has a camera that is used if a new Camera is not given.
	/// </summary>
	/// <param name="newcam"> Pointer to the Camera object. </param>
	void SetCurrentCamera(Camera* newcam);

	/// <summary>
	/// Allows the user to set the orientation, and position of the scene's current 3D camera.
	/// </summary>
	/// <param name="up"> Camera's up direction. </param>
	/// <param name="lookat"> Position that will determine where the camera will be pointed. </param>
	/// <param name="pos"> Camera's position </param>
	void SetOrientAndPosition(Vect up, Vect lookat, Vect pos);

	void SwitchtoGodCam();
	void SwitchFromGodCam();

private:
	Camera* pCamCurrent;
	Camera* DefaultCamera;
	Camera* pCam2D;
	Camera* pPrevCamera;
	GodCam* pGodCam;
};

#endif