// Level Transition

#ifndef _LevelTransition
#define _LevelTransition

#include "Scene.h"

class TransitionController;
class LevelCompleteDisplay;

class LevelTransition : public Scene
{
public:
	LevelTransition() = default;
	LevelTransition(const LevelTransition& other) = delete;
	LevelTransition& operator=(const LevelTransition& other) = delete;
	~LevelTransition();

	virtual void Initialize();
	virtual void SceneEnd();

private:
	TransitionController* pTranCon;
	LevelCompleteDisplay* pDisplay;

};

#endif _LevelTransition