// Central Game Manager

#include "CentralGameManager.h"
#include "HUD.h"
#include "ScoreManager.h"
#include "KeyboardController.h"
#include "PlayerManager.h"

CentralGameManager::CentralGameManager()
{
	pKBController = new KeyboardController();
	pKBController->SetPlayer(PlayerManager::GetPlayer());
	PlayerManager::InitializePlayer();
	SubmitDrawRegistration();
	SubmitUpdateRegistration();
	SubmitKeyRegistration(AZUL_KEY::KEY_F2, InputEventType::KEY_PRESS);
	HUD::Initialize();
}

CentralGameManager::~CentralGameManager()
{
	PlayerManager::Reset();
	delete pKBController;
}

void CentralGameManager::Update()
{
	//HUD::UpdateScore(ScoreManager::GetScore());
	//HUD::UpdateReload();
}

void CentralGameManager::Draw2D()
{
	HUD::Render();
}

void CentralGameManager::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_F2:
		pKBController->Toggle();
		break;
	}
	
}