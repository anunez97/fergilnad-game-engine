// Controller

#ifndef _Controller
#define _Controller

#include "GameObject.h"

class Controller : public GameObject
{
public:
	Controller() = default;
	Controller(const Controller& other) = delete;
	Controller& operator=(const Controller& other) = delete;
	~Controller() = default;
};

#endif _Controller