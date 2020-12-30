// Camera Manager

#include "CameraManager.h"
#include "Fergilnad.h"
#include "GodCam.h"

CameraManager::CameraManager()
{
	pGodCam = 0;
	pPrevCamera = 0;

	// 3D Camera
	DefaultCamera = new Camera(Camera::Type::PERSPECTIVE_3D);
	DefaultCamera->setViewport(0, 0, Fergilnad::GetWidth(), Fergilnad::GetHeight());
	DefaultCamera->setPerspective(35.0f, float(Fergilnad::GetWidth()) / float(Fergilnad::GetHeight()), 1.0f, 5000.0f);

	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(50.0f, 50.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);

	DefaultCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);

	pCamCurrent = DefaultCamera;

	//2D Camera
	pCam2D = new Camera(Camera::Type::ORTHOGRAPHIC_2D);
	assert(pCam2D);

	pCam2D->setViewport(0, 0, Fergilnad::GetWidth(), Fergilnad::GetHeight());
	pCam2D->setOrthographic(-0.5f * Fergilnad::GetWidth(), 0.5f * Fergilnad::GetWidth(), -0.5f * Fergilnad::GetHeight(), 0.5f * Fergilnad::GetHeight(), 1.0f, 1000.0f);

	Vect up2DCam(0.0f, 1.0f, 0.0f);
	Vect pos2DCam(0.0f, 0.0f, 0.0f);
	Vect lookAt2DCam(0.0f, 0.0f, -1.0f);
	pCam2D->setOrientAndPosition(up2DCam, lookAt2DCam, pos2DCam);

	pCam2D->updateCamera();
}

CameraManager::~CameraManager()
{
	// If the default camera is different than the current camera
	if (pCamCurrent != DefaultCamera && pCamCurrent != pGodCam->GetCamera())
		delete pCamCurrent;

	delete DefaultCamera;
	delete pCam2D;
	delete pGodCam;

	if (pPrevCamera != 0)
		delete pPrevCamera;
}

Camera* CameraManager::GetCurrentCamera()
{
	return pCamCurrent;
}

Camera* CameraManager::GetCurrentCamera2D()
{
	return pCam2D;
}

void CameraManager::SetCurrentCamera(Camera* newcam)
{
	if (pGodCam == 0)
		pGodCam = new GodCam(this);

	pCamCurrent = newcam;
}

void CameraManager::SetOrientAndPosition(Vect up, Vect lookat, Vect pos)
{
	pCamCurrent->setOrientAndPosition(up, lookat, pos);
	pCamCurrent->updateCamera();
}

void CameraManager::SwitchtoGodCam()
{
	pPrevCamera = pCamCurrent;
	pCamCurrent = pGodCam->GetCamera();
}

void CameraManager::SwitchFromGodCam()
{
	pCamCurrent = pPrevCamera;
	pPrevCamera = 0;
}