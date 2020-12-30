// Screen Log

#ifndef _ScreenLog
#define _ScreenLog

#include <list>

class SpriteFont;
class SpriteString;

class ScreenLog
{
	friend class ScreenLogAttorney;
private:
	static ScreenLog* ptrInstance;

	static ScreenLog& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ScreenLog;
		return *ptrInstance;
	}

	ScreenLog();
	ScreenLog(const ScreenLog& other) = delete;
	ScreenLog& operator=(const ScreenLog& other) = delete;
	~ScreenLog();

	static void Render();
	static void Delete() { Instance().privDelete(); }

	void privDelete();

	using MessageCollection = std::list<std::string>;
	MessageCollection messages;

	SpriteFont* font;
	SpriteString* ss;
	int anchorX;
	int anchorY;
	static char DebugBuff[];
	
public:
	/// <summary>
	/// Adds a string to the Screen Log
	/// </summary>
	/// <param name="A"> String to be added. Dynamic parameters added with "%". </param>
	/// <param name=""> Parameters to be added to the string. </param>
	static void Add(char* A, ...);
};

#endif _ScreenLog