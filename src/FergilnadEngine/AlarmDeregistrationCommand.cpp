// Alarm Deregistration Command

#include "AlarmDeregistrationCommand.h"
#include "AlarmableAttorney.h"

AlarmDeregistrationCommand::AlarmDeregistrationCommand(Alarmable* al, AlarmableManager::ALARM_ID id)
	:pAlarm(al), al_id(id)
{
}

void AlarmDeregistrationCommand::Execute()
{
	AlarmableAttorney::Registration::AlarmDeregistration(pAlarm, al_id);
}