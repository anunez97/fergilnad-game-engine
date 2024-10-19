// Alarm Restart Command

#ifndef _AlarmRestartCommand
#define _AlarmRestartCommand

#include "SceneRegistrationCommand.h"
#include "AlarmableManager.h"

class Alarmable;

class AlarmRestartCommand : public SceneRegistrationCommand
{
public:
	AlarmRestartCommand() {};
	AlarmRestartCommand(const AlarmRestartCommand& other) = delete;
	AlarmRestartCommand& operator=(const AlarmRestartCommand& other) = delete;
	~AlarmRestartCommand() {};

	AlarmRestartCommand(Alarmable* al, AlarmableManager::ALARM_ID id);

	void SetAlarmTime(float t);

	virtual void Execute();

private:
	Alarmable* pAlarm;
	AlarmableManager::ALARM_ID al_id;
	float time;
};

#endif _AlarmRestartCommand