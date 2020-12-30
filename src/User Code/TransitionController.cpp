// Transition Controller

#include "TransitionController.h"
#include "LevelManager.h"

TransitionController::TransitionController()
{
	SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, InputEventType::KEY_PRESS);
}

TransitionController::~TransitionController()
{
	SubmitKeyDeregistration(AZUL_KEY::KEY_SPACE, InputEventType::KEY_PRESS);
}

void TransitionController::KeyPressed(AZUL_KEY)
{
	LevelManager::LoadNextLevel();
}

