// God Cam

#include "GodCam.h"
#include "Fergilnad.h"
#include "CameraManager.h"

GodCam::GodCam(CameraManager* pCamMgr)
	:speed(1.0f), rotangle(0.025f), Active(false)
{
	this->pCamMgr = pCamMgr;

	pCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	pCam->setViewport(0, 0, Fergilnad::GetWidth(), Fergilnad::GetHeight());
	pCam->setPerspective(35.0f, float(Fergilnad::GetWidth()) / float(Fergilnad::GetHeight()), 1.0f, 5000.0f);

	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Position.set(0.0f, 0.0f, 0.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);

	pCam->setOrientAndPosition(up3DCam, lookAt3DCam, Position);

	Rotate = Matrix(IDENTITY);

	SubmitKeyRegistration(AZUL_KEY::KEY_F1, InputEventType::KEY_PRESS);
	
}

GodCam::~GodCam()
{
	delete pCam;
}

void GodCam::Update()
{
	if (Active)
	{
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
		{
			MoveForward();
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
		{
			MoveBackward();
		}

		if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
		{
			TurnLeft();
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
		{
			TurnRight();
		}

		if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_UP))
		{
			LookUp();
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_DOWN))
		{
			LookDown();
		}

		SceneManager::GetCurrentScene()->UpdateCameraPos(Vect(0.0f, 1.0f, 0.0f), Position + (Vect(0, 0, 1.0f) * Rotate), Position);
	}
}

void GodCam::KeyPressed(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_F1)
	{
		Active = !Active;

		if (Active)
		{
			pCamMgr->SwitchtoGodCam();
			SubmitUpdateRegistration();
		}
		else
		{
			pCamMgr->SwitchFromGodCam();
			SubmitUpdateDeregistration();
		}
	}
}

void GodCam::MoveForward()
{
	Position += Vect(0, 0, 1) * Rotate * speed;
}

void GodCam::MoveBackward()
{
	Position += Vect(0, 0, 1) * Rotate * -speed;
}

void GodCam::TurnLeft()
{
	Rotate *= Matrix(ROT_Y, rotangle);
}

void GodCam::TurnRight()
{
	Rotate *= Matrix(ROT_Y, -rotangle);
}

void GodCam::LookUp()
{
	Rotate *= Matrix(ROT_AXIS_ANGLE, Rotate.get(ROW_0), -rotangle);
}

void GodCam::LookDown()
{
	Rotate *= Matrix(ROT_AXIS_ANGLE, Rotate.get(ROW_0), rotangle);
}

Camera* GodCam::GetCamera()
{
	return pCam;
}