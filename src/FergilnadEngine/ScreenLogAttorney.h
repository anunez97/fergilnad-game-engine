// Screen Log Attorney

#ifndef _ScreenLogAttorney
#define _ScreenLogAttorney

#include "ScreenLog.h"

class ScreenLogAttorney 
{
	friend class Fergilnad;

	static void Render() { ScreenLog::Render(); }
	static void Delete() { ScreenLog::Delete(); }
};

#endif _ScreenLogAttorney