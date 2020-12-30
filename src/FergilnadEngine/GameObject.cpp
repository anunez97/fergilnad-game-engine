// Game Object

#include "GameObject.h"
#include "SceneAttorney.h"
#include "SceneManager.h"
#include "SceneRegistrationBroker.h"
#include "GameObjectEntryCommand.h"
#include "GameObjectExitCommand.h"

GameObject::GameObject()
{
	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
	pRegistrationCommand = new GameObjectEntryCommand(this);
	pDeregistrationCommand = new GameObjectExitCommand(this);
}

GameObject::~GameObject()
{
	delete pRegistrationCommand;
	delete pDeregistrationCommand;
}

void GameObject::SubmitEntry()
{
	assert(RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::Command::Submit(SceneManager::GetCurrentScene(), pRegistrationCommand);
	RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void GameObject::SubmitExit()
{
	assert(RegStateCurr != RegistrationState::PENDING_REGISTRATION);
	if (RegStateCurr == RegistrationState::CURRENTLY_REGISTERED)
	{
		SceneAttorney::Command::Submit(SceneManager::GetCurrentScene(), pDeregistrationCommand);
		RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
	}
}

void GameObject::ConnectToScene()
{
	assert(RegStateCurr == RegistrationState::PENDING_REGISTRATION);
	RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
	this->SceneEntry();
}

void GameObject::DisconnectToScene()
{
	assert(RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
	this->SceneExit();
}