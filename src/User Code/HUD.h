// HUD

#ifndef _HUD
#define _HUD

class HealthDisplay;
class ReloadDisplay;
class RadarDisplay;
class ReticleDisplay;
class ObjectiveDisplay;
class ScoreDisplay;

class HUD
{
private:
	static HUD* ptrInstance;

	static HUD& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new HUD();
		return *ptrInstance;
	}

	HUD();
	HUD(const HUD& other) = delete;
	HUD& operator=(const HUD& other) = delete;
	~HUD();

	void privRenderHUD();

	void privUpdateScore(int score);
	void privUpdateReload();
	void privInitialize();
	void privDelete();

	HealthDisplay* healthDisplay;
	ReloadDisplay* reloadDisplay;
	RadarDisplay* radarDisplay;
	ReticleDisplay* reticleDisplay;
	ObjectiveDisplay* objectiveDisplay;
	ScoreDisplay* scoreDisplay;

public:
	static void Render() { Instance().privRenderHUD(); }
	static void UpdateScore(int score) { Instance().privUpdateScore(score); }
	static void UpdateReload() { Instance().privUpdateReload(); }
	static void Delete() { Instance().privDelete(); }
	static void Initialize() { Instance().privInitialize(); }
};

#endif _HUD