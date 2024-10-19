// Time Manager

#include "TimeManager.h"
#include "FreezeTime.h"

TimeManager* TimeManager::ptrInstance = nullptr;

TimeManager::TimeManager()
	:frameCount(0), currentTime(0), previousTime(0)
{
	FrzTime = new FreezeTime();
}

void TimeManager::privProcessTime(float sys_time)
{
	frameCount++;
	previousTime = currentTime;
	currentTime = FrzTime->GetTimeInSeconds(sys_time);

	frameTime = currentTime - previousTime;

	//DebugMsg::out("Frame time is %f, \n", frameTime);
	//DebugMsg::out("FPS: %f\n", frameTime * 1000);

}

void TimeManager::Delete()
{
	delete Instance().FrzTime;
	delete ptrInstance;
	ptrInstance = nullptr;
}