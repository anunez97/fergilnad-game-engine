// Alarm Registration Command

#ifndef _AlarmDeregistrationCommand
#define _AlarmDeregistrationCommand

#include "SceneRegistrationCommand.h"
#include "AlarmableManager.h"

class Alarmable;

class AlarmDeregistrationCommand : public SceneRegistrationCommand
{
public:
	AlarmDeregistrationCommand() {};
	AlarmDeregistrationCommand(const AlarmDeregistrationCommand& other) = delete;
	AlarmDeregistrationCommand& operator=(const AlarmDeregistrationCommand& other) = delete;
	~AlarmDeregistrationCommand() {};

	AlarmDeregistrationCommand(Alarmable* al, AlarmableManager::ALARM_ID id);

	virtual void Execute();

private:
	Alarmable* pAlarm;
	AlarmableManager::ALARM_ID al_id;

};

#endif _AlarmDeregistrationCommand