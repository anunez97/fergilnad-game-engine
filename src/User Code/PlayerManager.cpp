// Player Manager

#include "PlayerManager.h"
#include "PlayerTank.h"
#include "Fergilnad.h"
#include "SceneTest.h"

PlayerManager* PlayerManager::ptrInstance = nullptr;

PlayerManager::PlayerManager()
	:pPlayer(0)
{
	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(50.0f, 50.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);

	camFirstPerson = new Camera(Camera::Type::PERSPECTIVE_3D);
	camFirstPerson->setViewport(0, 0, Fergilnad::GetWidth(), Fergilnad::GetHeight());
	camFirstPerson->setPerspective(35.0f, float(Fergilnad::GetWidth()) / float(Fergilnad::GetHeight()), 1.0f, 5000.0f);
	camFirstPerson->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);

	camThirdPerson = new Camera(Camera::Type::PERSPECTIVE_3D);
	camThirdPerson->setViewport(0, 0, Fergilnad::GetWidth(), Fergilnad::GetHeight());
	camThirdPerson->setPerspective(35.0f, float(Fergilnad::GetWidth()) / float(Fergilnad::GetHeight()), 1.0f, 5000.0f);
	camThirdPerson->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
}

PlayerManager::~PlayerManager()
{
}

int PlayerManager::GetReloadPercent()
{
	return Instance().pPlayer->GetReloadTime();
}

PlayerTank* PlayerManager::GetPlayer()
{
	if (Instance().pPlayer == 0)
		Instance().pPlayer = new PlayerTank();

	return Instance().pPlayer;
}

void PlayerManager::InitializePlayer()
{
	SceneManager::GetCurrentScene()->SetCurrentCamera(Instance().camThirdPerson);
	Instance().pPlayer->SubmitEntry();
}

void PlayerManager::Reset()
{
	delete Instance().pPlayer;
	Instance().pPlayer = 0;
}

void PlayerManager::privSwitchView()
{
	SceneManager::GetCurrentScene()->SetCurrentCamera(camFirstPerson);
}

void PlayerManager::privPlayerDead()
{
	pPlayer->SubmitExit();
	SceneManager::SetNextScene(new SceneTest());
}

void PlayerManager::privUpdateCameras()
{

}

void PlayerManager::privDelete()
{
	delete pPlayer;
	delete camFirstPerson;
	delete camThirdPerson;

	delete ptrInstance;

	ptrInstance = nullptr;
}