// Player Managaer

#ifndef _PlayerManager
#define _PlayerManager

#include "AzulCore.h"

class PlayerTank;

class PlayerManager
{
private:
	static PlayerManager* ptrInstance;

	static PlayerManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new PlayerManager();
		return *ptrInstance;
	}

	PlayerManager();
	PlayerManager(const PlayerManager& other) = delete;
	PlayerManager& operator=(const PlayerManager& other) = delete;
	~PlayerManager();

	void privPlayerDead();

	void privSwitchView();
	void privUpdateCameras();
	void privDelete();

	PlayerTank* pPlayer;

	Camera* camThirdPerson;
	Camera* camFirstPerson;

public:
	static int GetReloadPercent();
	static PlayerTank* GetPlayer();
	static void InitializePlayer();
	static void Reset();
	static void SwitchView() { Instance().privSwitchView(); }
	static void PlayerDead() { Instance().privPlayerDead(); }
	static void UpdateCameras() { Instance().privUpdateCameras(); }
	static void Delete() { Instance().privDelete(); }

};

#endif _PlayerManager