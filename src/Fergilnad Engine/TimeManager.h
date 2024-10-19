// Time Manager

#ifndef _TimeManager
#define _TimeManager

#include "AzulCore.h"

class FreezeTime;

class TimeManager
{
	friend class TimeManagerAttorney;
private:
	static TimeManager* ptrInstance;

	static TimeManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new TimeManager;
		return *ptrInstance;
	}

	TimeManager();
	TimeManager(const TimeManager& other) = delete;
	TimeManager& operator=(const TimeManager& other) = delete;
	~TimeManager() = default;

	void privProcessTime(float sys_time);

	/// <summary>
	/// Processes the time passed while the engine is running
	/// </summary>
	static void ProcessTime(float sys_time) { Instance().privProcessTime(sys_time); };

	/// <summary>
	/// Deletes the singleton
	/// </summary>
	static void Delete();

	FreezeTime* FrzTime;

	float currentTime;
	float previousTime;
	float frameTime;

	int frameCount;

public:
	/// <summary>
	/// Gets the time passed in game.
	/// </summary>
	/// <returns> Returns the time passed as a float. </returns>
	static float GetTime() { return Instance().currentTime; };

	/// <summary>
	/// Gets the time between frames.
	/// </summary>
	/// <returns> Returns the time between frames as a float. </returns>
	static float GetFrameTime() { return Instance().frameTime; };
};

#endif _TimeManager
