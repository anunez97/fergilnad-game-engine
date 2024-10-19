// Inputable

#include "Inputable.h"
#include "InputRegistrationCommand.h"
#include "InputDeregistrationCommand.h"
#include "SceneManager.h"
#include "SceneAttorney.h"

Inputable::Inputable()
{
}

Inputable::~Inputable()
{
	DebugMsg::out("Inputable destructor");

	std::map<AZUL_KEY, RegistrationData*>::iterator it;
	for (it = PressMap.begin(); it != PressMap.end(); it++)
	{

		delete (*it).second->pRegistrationCommand;
		delete (*it).second->pDeregistrationCommand;
		delete (*it).second;
	}

	for (it = ReleaseMap.begin(); it != ReleaseMap.end(); it++)
	{
		delete (*it).second->pRegistrationCommand;
		delete (*it).second->pDeregistrationCommand;
		delete (*it).second;
	}
}

Inputable::RegistrationData* Inputable::GetData(AZUL_KEY k, InputEventType e)
{
	if (e == InputEventType::KEY_PRESS)
	{
		if (PressMap.count(k) == 0)
		{
			PressMap[k] = new RegistrationData();
			PressMap[k]->pRegistrationCommand = new InputRegistrationCommand(this);
			PressMap[k]->pDeregistrationCommand = new InputDeregistrationCommand(this);
		}
		
		return PressMap[k];
	}
	else
	{
		if (ReleaseMap.count(k) == 0)
		{
			ReleaseMap[k] = new RegistrationData();
			ReleaseMap[k]->pRegistrationCommand = new InputRegistrationCommand(this);
			ReleaseMap[k]->pDeregistrationCommand = new InputDeregistrationCommand(this);
		}

		return ReleaseMap[k];
	}
}

void Inputable::SubmitKeyRegistration(AZUL_KEY k, InputEventType e)
{
	RegistrationData* pData = GetData(k, e);

	assert(pData->RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
	pData->pRegistrationCommand->SetKey(k);
	pData->pRegistrationCommand->SetEvent(e);
	SceneAttorney::Command::Submit(SceneManager::GetCurrentScene(), pData->pRegistrationCommand);
	pData->RegStateCurr = RegistrationState::PENDING_REGISTRATION;
	
}

void Inputable::SubmitKeyDeregistration(AZUL_KEY k, InputEventType e)
{
	RegistrationData* pData = GetData(k, e);

	assert(pData->RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);
	pData->pDeregistrationCommand->SetKey(k);
	pData->pDeregistrationCommand->SetEvent(e);
	SceneAttorney::Command::Submit(SceneManager::GetCurrentScene(), pData->pDeregistrationCommand);
	pData->RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}

void Inputable::SceneRegistration(AZUL_KEY k, InputEventType e)
{
	RegistrationData* pData = GetData(k, e);

	assert(pData->RegStateCurr == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::InputRegistration::Register(SceneManager::GetCurrentScene(), this, k, e, pData->pDeleteRef);
	pData->RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Inputable::SceneDeregistration(AZUL_KEY k, InputEventType e)
{
	RegistrationData* pData = GetData(k, e);

	assert(pData->RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::InputRegistration::Deregister(SceneManager::GetCurrentScene(), k, e, pData->pDeleteRef);
	pData->RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;

	DebugMsg::out("key deregistered\n", k);
}