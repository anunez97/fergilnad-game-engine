// Time Manager Attorney

#ifndef _TimeManagerAttorney
#define _TimeManagerAttorney

#include "TimeManager.h"

class TimeManagerAttorney
{
private:
	friend class Fergilnad;
	static void ProcessTime(float sys_time) { TimeManager::ProcessTime(sys_time); }
	static void Delete() { TimeManager::Delete(); }
};

#endif _TimeManagerAttorney