// Alarm Restart Command

#include "AlarmRestartCommand.h"
#include "AlarmableAttorney.h"

AlarmRestartCommand::AlarmRestartCommand(Alarmable* al, AlarmableManager::ALARM_ID id)
	:pAlarm(al), al_id(id)
{
}

void AlarmRestartCommand::SetAlarmTime(float t)
{
	time = t;
}

void AlarmRestartCommand::Execute()
{
	AlarmableAttorney::Registration::RestartAlarm(pAlarm, al_id, time);
}