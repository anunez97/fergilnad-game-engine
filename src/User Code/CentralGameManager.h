// Central Game Manager

#ifndef _CentralGameManager
#define _CentralGameManager

#include "GameObject.h"

class KeyboardController;

class CentralGameManager : public GameObject
{
public:
	CentralGameManager();
	CentralGameManager(const CentralGameManager& other) = delete;
	CentralGameManager& operator=(const CentralGameManager& other) = delete;
	~CentralGameManager();

	virtual void Update();
	virtual void Draw2D();
	virtual void KeyPressed(AZUL_KEY k);


private:
	KeyboardController* pKBController;
};

#endif _CentralGameManager