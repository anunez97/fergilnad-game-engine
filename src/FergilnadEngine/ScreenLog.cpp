// Screen Log

#include "ScreenLog.h"
#include "SpriteFontManager.h"
#include "SpriteString.h"
#include "FergilnadSprite.h"
#include "Fergilnad.h"

ScreenLog* ScreenLog::ptrInstance = nullptr;
char ScreenLog::DebugBuff[256];

ScreenLog::ScreenLog()
	:anchorX(0)
{
	font = SpriteFontManager::Get("Arial15");
	ss = new SpriteString();

	anchorY = static_cast<int>(font->GetGlyph(' ')->GetHeight());
}

ScreenLog::~ScreenLog()
{
	delete ss;
}

void ScreenLog::Add(char* A, ...)
{
	va_list args;
	va_start(args, A);
	vsprintf_s(DebugBuff, A, args);
	va_end(args);

	std::string s(DebugBuff);
	Instance().messages.push_back(s);
}

void ScreenLog::Render()
{
	int lines = 1;

	for (MessageCollection::iterator it = Instance().messages.begin(); it != Instance().messages.end(); it++)
	{
		Instance().ss->Set(Instance().font, (*it), Instance().anchorX, Fergilnad::GetHeight() - (Instance().anchorY * lines));
		Instance().ss->Render();

		lines++;
	}

	Instance().messages.clear();

}

void ScreenLog::privDelete()
{
	delete ptrInstance;

	ptrInstance = nullptr;
}