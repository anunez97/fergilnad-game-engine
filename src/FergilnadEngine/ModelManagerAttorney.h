// Model Manager Attorney

#ifndef _ModelManagerAttorney
#define _ModelManagerAttorney

#include "ModelManager.h"

class ModelManagerAttorney
{
	friend class Fergilnad;

private:
	static void Delete() { ModelManager::Delete(); }
};

#endif _ModelManagerAttorney