// Keyboard Controller

#include "KeyboardController.h"
#include "PlayerTank.h"
#include "EnemyManager.h"
#include "ScreenLog.h"
#include "PlayerManager.h"


KeyboardController::KeyboardController()
	:Enabled(false), debugLog(false)
{
	SubmitUpdateRegistration();
	SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, InputEventType::KEY_PRESS);
	SubmitKeyRegistration(AZUL_KEY::KEY_F3, InputEventType::KEY_PRESS);
}

KeyboardController::~KeyboardController()
{

}

void KeyboardController::Update()
{
	if (Enabled)
	{
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
		{
			pPlayer->MoveForward();
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
		{
			pPlayer->MoveBackward();
		}

		if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
		{
			pPlayer->TurnLeft();
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
		{
			pPlayer->TurnRight();
		}

		if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_UP))
			pPlayer->LookUp();
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_DOWN))
			pPlayer->LookDown();

		if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_LEFT))
			pPlayer->LookLeft();
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_RIGHT))
			pPlayer->LookRight();
	}

	if(debugLog)
		ScreenLog::Add("Enemies remaining: %i", EnemyManager::EnemiesLeft());
}

void KeyboardController::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_SPACE:
		if(Enabled)
			pPlayer->Fire();
		break;
	case AZUL_KEY::KEY_F2:
		if (Enabled)
			PlayerManager::SwitchView();
		break;
	}
}

void KeyboardController::Toggle()
{
	Enabled = !Enabled;
}

void KeyboardController::SetPlayer(PlayerTank* p)
{
	pPlayer = p;
}