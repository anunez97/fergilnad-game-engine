// Alarmable

#include "Alarmable.h"
#include "AlarmRegistrationCommand.h"
#include "AlarmDeregistrationCommand.h"
#include "AlarmRestartCommand.h"
#include "SceneManager.h"
#include "SceneAttorney.h"

Alarmable::Alarmable()
{
	for (int i = 0; i < AlarmableManager::ALARM_NUMBER; i++)
	{
		RegData[i].RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
		RegData[i].pRegistrationCmd = new AlarmRegistrationCommand(this, static_cast<AlarmableManager::ALARM_ID>(i));
		RegData[i].pDeregistrationCmd = new AlarmDeregistrationCommand(this, static_cast<AlarmableManager::ALARM_ID>(i));
		RegData[i].pRestartCmd = new AlarmRestartCommand(this, static_cast<AlarmableManager::ALARM_ID>(i));
		RegData[i].state = INACTIVE;
	}
}

Alarmable::~Alarmable()
{
	DebugMsg::out("Alarmable destructor\n");
	for (int i = 0; i < AlarmableManager::ALARM_NUMBER; i++)
	{
		delete RegData[i].pRegistrationCmd;
		delete RegData[i].pDeregistrationCmd;
		delete RegData[i].pRestartCmd;
	}
}

void Alarmable::SubmitAlarmRegistration(ALARM_ID id, float t)
{
	assert(RegData[id].RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
	RegData[id].pRegistrationCmd->SetAlarmTime(t);
	SceneAttorney::Command::Submit(SceneManager::GetCurrentScene(), RegData[id].pRegistrationCmd);
	RegData[id].RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Alarmable::SubmitAlarmDeregistration(ALARM_ID id)
{
	assert(RegData[id].RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::Command::Submit(SceneManager::GetCurrentScene(), RegData[id].pDeregistrationCmd);
	RegData[id].RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}

void Alarmable::SubmitAlarmRestart(ALARM_ID id, float t)
{
	assert(RegData[id].RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);
	RegData[id].pRestartCmd->SetAlarmTime(t);
	SceneAttorney::Command::Submit(SceneManager::GetCurrentScene(), RegData[id].pRestartCmd);
}

void Alarmable::AlarmRegistration(AlarmableManager::ALARM_ID id, float t)
{
	assert(RegData[id].RegStateCurr == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::AlarmRegistration::Register(SceneManager::GetCurrentScene(), t, this, id, RegData[id].pDeleteRef);
	RegData[id].state = ACTIVE;
	RegData[id].RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Alarmable::AlarmDeregistration(AlarmableManager::ALARM_ID id)
{
	assert(RegData[id].RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);

	// Deregisters the alarm if it is active
	if (RegData[id].state == ACTIVE)
	{
		SceneAttorney::AlarmRegistration::Deregister(SceneManager::GetCurrentScene(), RegData[id].pDeleteRef);
		RegData[id].state = INACTIVE;
	}

	RegData[id].RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Alarmable::TriggerAlarm(AlarmableManager::ALARM_ID id)
{
	//RegData[id].RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
	RegData[id].state = INACTIVE;

	switch (id)
	{
	case AlarmableManager::ALARM_0:
		this->Alarm0();
		break;
	case AlarmableManager::ALARM_1:
		this->Alarm1();
		break;
	case AlarmableManager::ALARM_2:
		this->Alarm2();
		break;
	}
}

void Alarmable::RestartAlarm(AlarmableManager::ALARM_ID id, float t)
{
	SceneAttorney::AlarmRegistration::Register(SceneManager::GetCurrentScene(), t, this, id, RegData[id].pDeleteRef);
	RegData[id].state = ACTIVE;
}