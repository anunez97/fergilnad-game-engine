// Transition Controller

#ifndef _TransitionController
#define _TransitionController

#include "Controller.h"
#include "AzulCore.h"

class TransitionController : public Controller
{
public:
	TransitionController();
	TransitionController(const TransitionController& other) = delete;
	TransitionController& operator=(const TransitionController& other) = delete;
	~TransitionController();

	virtual void KeyPressed(AZUL_KEY);
};

#endif _TransitionController