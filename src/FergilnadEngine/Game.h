#ifndef GAME_H
#define GAME_H

#include "AzulCore.h"

class Fergilnad: public Engine
{
private:
	static Fergilnad* ptrInstance;

	static Fergilnad& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new Fergilnad();
		return *ptrInstance;
	}

	Fergilnad();
	Fergilnad(const Fergilnad& other) = delete;
	Fergilnad& operator=(const Fergilnad& other) = delete;
	~Fergilnad() = default;

	// Azul methods
	virtual void Initialize();
	virtual void LoadContent();
	virtual void Update();
	virtual void Draw();
	virtual void UnLoadContent();

	int privGetHeight();
	int privGetWidth();
	float privGetTime();

	void privSetClear(float r, float g, float b, float a);
	void privSetWidthHeight(int w, int h);
	void privSetWindowName(const char* name);

	// User defined 
	void GameInitialize();
	void GameEnd();
	void LoadResources();

public:
	static void Run();

	static int GetHeight() { Instance().privGetHeight(); }
	static int GetWidth() { Instance().privGetWidth(); }
	static float GetTime() { Instance().privGetTime(); }

	static void SetClear(float r, float g, float b, float a) { Instance().privSetClear(r, g, b, a); }
	static void SetWidthHeight(int w, int h) { Instance().privSetWidthHeight(w, h); }
	static void SetWindowName(const char* name) { Instance().privSetWindowName(name); }


	/*
public:
	// constructor
	Game()
	{};

	// Methods Users need to overload
    virtual void Initialize();
    virtual void LoadContent();
	virtual void Update();
    virtual void Draw();
    virtual void UnLoadContent();

	// User defined (Specific to each game)
	void LoadResources();


private:	
	// legacy
	Game( const char* windowName, const int Width,const int Height);

	*/
};

#endif