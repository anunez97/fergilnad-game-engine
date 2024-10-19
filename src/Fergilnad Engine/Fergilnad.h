#ifndef FERGILNAD_H
#define FERGILNAD_H

#include "AzulCore.h"

class Fergilnad: public Engine
{
	friend class FergilnadAttorney;
private:
	static Fergilnad* ptrInstance;

	static Fergilnad& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new Fergilnad();
		return *ptrInstance;
	}

	Fergilnad() {};
	Fergilnad(const Fergilnad& other) = delete;
	Fergilnad& operator=(const Fergilnad& other) = delete;
	~Fergilnad() = default;

	// Azul methods
	virtual void Initialize();
	void LoadDefaultAssets();
	virtual void LoadContent();
	virtual void Update();
	virtual void Draw();
	virtual void UnLoadContent();


	// User defined 
	void GameInitialize();
	void GameEnd();
	void LoadResources();

	static float GetTime() { return Instance().GetTimeInSeconds(); }

public:
	static void Run();

	/// <summary>
	/// Gets the window height.
	/// </summary>
	/// <returns> Returns the height of the game window as an int. </returns>
	static int GetHeight() { return Instance().getHeight(); }

	/// <summary>
	/// Gets the width of the game window.
	/// </summary>
	/// <returns> Returns the width of the game window as an int. </returns>
	static int GetWidth() { return Instance().getWidth(); }

	/// <summary>
	/// Sets the color of the game window.
	/// </summary>
	/// <param name="r"> Red RGBA value. </param>
	/// <param name="g"> Green RGBA value. </param>
	/// <param name="b"> Blue RGBA value. </param>
	/// <param name="a"> Alpha RGBA value. </param>
	static void SetClear(float r, float g, float b, float a) { Instance().SetClearColor(r, g, b, a); }

	/// <summary>
	/// Set the width and height of the game window.
	/// </summary>
	/// <param name="w">  Width of the game window. </param>
	/// <param name="h"> Height of the game window. </param>
	static void SetWidthHeight(int w, int h) { Instance().setWidthHeight(w, h); }

	/// <summary>
	/// Set the name of the game window.
	/// </summary>
	/// <param name="name"> Name of the game window. </param>
	static void SetWindowName(const char* name) { Instance().setWindowName(name); }
};

#endif