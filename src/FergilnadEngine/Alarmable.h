// Alarmable

#ifndef _Alarmable
#define _Alarmable

#include "AzulCore.h"
#include "RegistrationState.h"
#include "AlarmableManager.h"

class AlarmRegistrationCommand;
class AlarmDeregistrationCommand;
class AlarmRestartCommand;

class Alarmable
{
	friend class AlarmableAttorney;
public:
	Alarmable();
	virtual ~Alarmable();

	virtual void Alarm0() {};
	virtual void Alarm1() {};
	virtual void Alarm2() {};

	using ALARM_ID = AlarmableManager::ALARM_ID;

	/// <summary>
	/// Submit an alarm for registration.
	/// </summary>
	/// <param name="id"> ID number of the alarm to be registered. </param>
	/// <param name="t"> Sets the time for the alarm to be triggered. </param>
	void SubmitAlarmRegistration(ALARM_ID id, float t);

	/// <summary>
	/// Submits an alarm for deregistration.
	/// </summary>
	/// <param name="id"> ID number of the alarm to be deregistered. </param>
	void SubmitAlarmDeregistration(ALARM_ID id);

	/// <summary>
	/// Submits an alarm to be restarted
	/// </summary>
	/// <param name="id"> ID number for the alarm. </param>
	/// <param name="t"> New time for alarm. </param>
	void SubmitAlarmRestart(ALARM_ID id, float t);

private:
	Alarmable(const Alarmable& other) = delete;
	Alarmable& operator=(const Alarmable& other) = delete;

	enum AlarmState
	{
		ACTIVE,   // Alarm has not been triggered yet
		INACTIVE  // Alarm is not been set
	};

	struct RegistrationData
	{
		RegistrationState RegStateCurr;
		AlarmableManager::StorageEntryRef pDeleteRef;
		AlarmRegistrationCommand* pRegistrationCmd;
		AlarmDeregistrationCommand* pDeregistrationCmd;
		AlarmRestartCommand* pRestartCmd;
		AlarmState state;
	};

	RegistrationData RegData[AlarmableManager::ALARM_NUMBER];

	/// <summary>
	/// Registers the alarm to the scene
	/// </summary>
	/// <param name="id">The alarm's ID</param>
	/// <param name="t">Time until the alarm is triggered, in seconds</param>
	void AlarmRegistration(AlarmableManager::ALARM_ID id, float t);

	/// <summary>
	/// Deregisters the alarm from the scene
	/// </summary>
	/// <param name="id">The ID of the alarm</param>
	void AlarmDeregistration(AlarmableManager::ALARM_ID id);

	/// <summary>
	/// Activates the given alarm
	/// </summary>
	/// <param name="id">The ID for the alarm</param>
	void TriggerAlarm(AlarmableManager::ALARM_ID id);

	/// <summary>
	/// Resets an alarm so it will be triggered again.
	/// </summary>
	/// <param name="id"> ID number of the alarm to be restarted. </param>
	/// <param name="t"> Time until the alarm is triggered. </param>
	void RestartAlarm(ALARM_ID id, float t);
};

#endif _Alarmable