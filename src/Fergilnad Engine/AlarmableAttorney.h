// AlarmableAttorney

#ifndef _AlarmableAttorney
#define _AlarmableAttorney

#include "Alarmable.h"

class AlarmableAttorney
{
public:
	class GameLoop
	{
		friend class AlarmableManager;
	private:
		static void TriggerAlarm(Alarmable* pMgr, AlarmableManager::ALARM_ID id) { pMgr->TriggerAlarm(id); }
	};

public:
	class Registration
	{
		friend class AlarmRegistrationCommand;
		friend class AlarmDeregistrationCommand;
		friend class AlarmRestartCommand;
	private:
		static void AlarmRegistration(Alarmable* pMgr, AlarmableManager::ALARM_ID id, float t) { pMgr->AlarmRegistration(id, t); }
		static void AlarmDeregistration(Alarmable* pMgr, AlarmableManager::ALARM_ID id) { pMgr->AlarmDeregistration(id); }
		static void RestartAlarm(Alarmable* pMgr, AlarmableManager::ALARM_ID id, float t) { pMgr->RestartAlarm(id, t); }
	};
};

#endif _AlarmableAttorney