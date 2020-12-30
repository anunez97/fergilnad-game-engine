// Score Manager

#ifndef _ScoreManager
#define _ScoreManager

class ScoreManager
{
private:
	static ScoreManager* ptrInstance;

	static ScoreManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ScoreManager();
		return *ptrInstance;
	}

	ScoreManager();
	ScoreManager(const ScoreManager& other) = delete;
	ScoreManager& operator=(const ScoreManager& other) = delete;
	~ScoreManager();

	void privAddScore(int points);

	int score;

public:
	static void AddScore(int points) { Instance().privAddScore(points); }
	static int GetScore() { return Instance().score; }
	static void Reset();
	static void Delete();

};

#endif _ScoreManager