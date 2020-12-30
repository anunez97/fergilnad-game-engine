// Keyboard Controller

#ifndef _KeyboardController
#define _KeyboardController

#include "Controller.h"	

class PlayerTank;

class KeyboardController : public Controller
{
public:
	KeyboardController();
	KeyboardController(const KeyboardController& other) = delete;
	KeyboardController& operator=(const KeyboardController& other) = delete;
	~KeyboardController();

	virtual void Update();
	virtual void KeyPressed(AZUL_KEY k);

	void Toggle();
	void SetPlayer(PlayerTank* p);

private:
	PlayerTank* pPlayer;
	bool Enabled;
	bool debugLog;

};

#endif _KeyboardController