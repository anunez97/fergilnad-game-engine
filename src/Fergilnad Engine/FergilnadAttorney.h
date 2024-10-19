// Fergilnad Attorney

#ifndef _FergilnadAttorney
#define _FergilnadAttorney

#include "Fergilnad.h"

class FergilnadAttorney
{
	friend class FreezeTime;
private:
	static float GetTime() { return Fergilnad::GetTime(); }
};

#endif _FergilnadAttorney
