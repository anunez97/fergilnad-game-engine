// Alarm Registration Command

#include "AlarmRegistrationCommand.h"
#include "AlarmableAttorney.h"

AlarmRegistrationCommand::AlarmRegistrationCommand(Alarmable* al, AlarmableManager::ALARM_ID id)
	:pAlarm(al), al_id(id)
{
}

void AlarmRegistrationCommand::SetAlarmTime(float t)
{
	time = t;
}

void AlarmRegistrationCommand::Execute()
{
	AlarmableAttorney::Registration::AlarmRegistration(pAlarm, al_id, time);
}