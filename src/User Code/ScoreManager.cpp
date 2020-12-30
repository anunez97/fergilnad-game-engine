// ScoreManager

#include "ScoreManager.h"

ScoreManager* ScoreManager::ptrInstance = nullptr;

ScoreManager::ScoreManager()
	:score(0)
{

}

ScoreManager::~ScoreManager()
{

}

void ScoreManager::privAddScore(int points)
{
	score += points;
}

void ScoreManager::Reset()
{
	Instance().score = 0;
}

void ScoreManager::Delete()
{
	delete ptrInstance;

	ptrInstance = nullptr;
}