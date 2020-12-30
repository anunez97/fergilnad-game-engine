// Level Manager

#ifndef _LevelManager
#define _LevelManager

class Scene;

class LevelManager
{
public:
	enum Level { LEVEL1, LEVEL2 };

private:
	static LevelManager* ptrInstance;

	static LevelManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new LevelManager();
		return *ptrInstance;
	}

	LevelManager();
	LevelManager(const LevelManager& other) = delete;
	LevelManager& other(const LevelManager& other) = delete;
	~LevelManager();

	void privLoadLevel(Level lvl);
	void privLoadNextLevel();
	void privDelete();

	Scene* GetLevel(int lvl);

	int level;

public:
	static void LoadNextLevel() { Instance().privLoadNextLevel(); }
	static void LoadLevel(Level lvl) { Instance().privLoadLevel(lvl); }
	static void Delete() { Instance().privDelete(); }
};

#endif _LevelManager