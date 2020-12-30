// Drawable

#include "Drawable.h"
#include "SceneManager.h"
#include "SceneAttorney.h"
#include "DrawRegistrationCommand.h"
#include "DrawDeregistrationCommand.h"

Drawable::Drawable()
{
	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;

	// Commands to be reused
	pRegistrationCmd = new DrawRegistrationCommand(this);
	pDeregistrationCmd = new DrawDeregistrationCommand(this);
}

Drawable::~Drawable()
{

	DebugMsg::out("Drawable destructor\n");
	delete pRegistrationCmd;
	delete pDeregistrationCmd;
}

void Drawable::SubmitDrawRegistration()
{
	assert(RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::Command::Submit(SceneManager::GetCurrentScene(), pRegistrationCmd);
	RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Drawable::SubmitDrawDeregistration()
{
	assert(RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::Command::Submit(SceneManager::GetCurrentScene(), pDeregistrationCmd);
	RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}

void Drawable::SceneRegistration()
{
	assert(RegStateCurr == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::DrawRegistration::Register(SceneManager::GetCurrentScene(), this, pDeleteRef);
	RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Drawable::SceneDeregistration()
{
	assert(RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::DrawRegistration::Deregister(SceneManager::GetCurrentScene(), pDeleteRef);
	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}