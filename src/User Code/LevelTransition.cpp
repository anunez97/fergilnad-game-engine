// Level Transition

#include "LevelTransition.h"
#include "TransitionController.h"
#include "LevelCompleteDisplay.h"

LevelTransition::~LevelTransition()
{
	DebugMsg::out("Level Transition destructor\n");
}

void LevelTransition::Initialize()
{
	pTranCon = new TransitionController();
	pDisplay = new LevelCompleteDisplay();
}

void LevelTransition::SceneEnd()
{
	delete pTranCon;
	delete pDisplay;
}