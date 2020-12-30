// Alarm Registration Command

#ifndef _AlarmRegistrationCommand
#define _AlarmRegistrationCommand

#include "SceneRegistrationCommand.h"
#include "AlarmableManager.h"

class Alarmable;

class AlarmRegistrationCommand : public SceneRegistrationCommand
{
public:
	AlarmRegistrationCommand() {};
	AlarmRegistrationCommand(const AlarmRegistrationCommand& other) = delete;
	AlarmRegistrationCommand& operator=(const AlarmRegistrationCommand& other) = delete;
	~AlarmRegistrationCommand() {};

	AlarmRegistrationCommand(Alarmable* al, AlarmableManager::ALARM_ID id);

	void SetAlarmTime(float t);

	virtual void Execute();

private:
	Alarmable* pAlarm;
	AlarmableManager::ALARM_ID al_id;
	float time;

};

#endif _AlarmRegistrationCommand