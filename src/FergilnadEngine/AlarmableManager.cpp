// Alarmable Manager

#include "AlarmableManager.h"
#include "AlarmableAttorney.h"
#include "TimeManager.h"

AlarmableManager::AlarmableManager()
{
}

AlarmableManager::~AlarmableManager()
{
	DebugMsg::out("AlarmableManager destroyed\n");
}

void AlarmableManager::ProcessAlarms()
{
	float time = TimeManager::GetTime();
	AlarmableManager::AlarmEvent ev;

	StorageEntryRef it = timeline.begin();

	while (it != timeline.end())
	{
		ev = (*it).second;

		// if the alarm time is passed, trigger it
		if (time >= (*it).first)
		{
			AlarmableAttorney::GameLoop::TriggerAlarm(ev.first, ev.second);
			Deregister(it);
		}
		// if an alarm in the map isnt triggered, stop processing
		else
			break;
		
		// beginning of the map will always be a different entry
		it = timeline.begin();
	}
}

void AlarmableManager::Register(float t, Alarmable* al, ALARM_ID id, StorageEntryRef& ref)
{
	// Add the current time and alarm time
	float time = TimeManager::GetTime() + t;

	// Create the alarm event
	AlarmEvent ev = std::pair<Alarmable*, ALARM_ID>(al, id);

	ref = timeline.insert(timeline.end(), std::pair<float, AlarmEvent>(time, ev));
}

void AlarmableManager::Deregister(const StorageEntryRef& ref)
{
	timeline.erase(ref);
}