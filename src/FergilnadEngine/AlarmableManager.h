// Alarmable Manager

#ifndef _AlarmableManager
#define _AlarmableManager

#include "AzulCore.h"
#include <map>

class Alarmable;

class AlarmableManager
{
	friend class AlarmableManagerAttorney;

public:
	enum ALARM_ID { ALARM_0 = 0, ALARM_1 = 1, ALARM_2 = 2 };
	static const int ALARM_NUMBER = 3;

private:
	AlarmableManager(const AlarmableManager& other) = delete;
	AlarmableManager& operator=(const AlarmableManager& other) = delete;

	using AlarmEvent = std::pair<Alarmable*, ALARM_ID>;
	using TimeLineMap = std::multimap<float, AlarmEvent>;

	TimeLineMap timeline;

public:
	AlarmableManager();
	~AlarmableManager();
	
	using StorageEntryRef = TimeLineMap::iterator;

	/// <summary>
	/// Processes the alarms that have been registered
	/// </summary>
	void ProcessAlarms();

	/// <summary>
	/// Registers the alarm
	/// </summary>
	/// <param name="t">Time until the alarm is triggered in seconds</param>
	/// <param name="al">Pointer to the Alarmable object</param>
	/// <param name="id">The ID of the alarm that is being registered</param>
	/// <param name="ref">Entry reference to the map that contains the alarms for quick removal</param>
	void Register(float t, Alarmable* al, ALARM_ID id, StorageEntryRef& ref);

	/// <summary>
	/// Deregisters the alarm
	/// </summary>
	/// <param name="ref">Entry reference to the map that contains the alarm</param>
	void Deregister(const StorageEntryRef& ref);


};

#endif _AlarmableManager