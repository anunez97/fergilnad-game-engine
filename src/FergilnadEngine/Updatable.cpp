// Updatable

#include "Updatable.h"
#include "SceneManager.h"
#include "SceneAttorney.h"
#include "UpdateRegistrationCommand.h"
#include "UpdateDeregistrationCommand.h"

Updatable::Updatable()
{
	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;

	// Commands to be reused
	pRegistrationCmd = new UpdateRegistrationCommand(this);
	pDeregistrationCmd = new UpdateDeregistrationCommand(this);
}

Updatable::~Updatable()
{
	DebugMsg::out("Updatable destructor\n");
	delete pRegistrationCmd;
	delete pDeregistrationCmd;
}

void Updatable::SubmitUpdateRegistration()
{
	assert(RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::Command::Submit(SceneManager::GetCurrentScene(), pRegistrationCmd);
	RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Updatable::SubmitUpdateDeregistration()
{
	assert(RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::Command::Submit(SceneManager::GetCurrentScene(), pDeregistrationCmd);
	RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}

void Updatable::SceneRegistration()
{
	assert(RegStateCurr == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::UpdateRegistration::Register(SceneManager::GetCurrentScene(), this, pDeleteRef);
	RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Updatable::SceneDeregistration()
{
	assert(RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::UpdateRegistration::Deregister(SceneManager::GetCurrentScene(), pDeleteRef);
	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}