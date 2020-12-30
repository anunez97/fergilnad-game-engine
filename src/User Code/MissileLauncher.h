// Missile Launcher

#ifndef _MissileLauncher
#define _MissileLauncher

#include "GameObject.h"

class MissileLauncher : public GameObject
{
public:
	MissileLauncher();
	MissileLauncher(const MissileLauncher& other) = delete;
	MissileLauncher& operator=(const MissileLauncher& other) = delete;
	~MissileLauncher();

private:

};

#endif _MissileLauncher