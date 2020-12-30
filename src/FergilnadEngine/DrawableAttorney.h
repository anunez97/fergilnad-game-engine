// DrawableAttorney

#ifndef _DrawableAttorney
#define _DrawableAttorney

#include "Drawable.h"

class DrawableAttorney
{
public:
	class GameLoop
	{
		friend class DrawableManager;
	private:
		static void Draw(Drawable* pMgr) { pMgr->Draw(); }
		static void Draw2D(Drawable* pMgr) { pMgr->Draw2D(); }
	};

public:
	class Registration
	{
		friend class DrawRegistrationCommand;
		friend class DrawDeregistrationCommand;
	private:
		static void SceneRegistration(Drawable* pMgr) { pMgr->SceneRegistration(); }
		static void SceneDeregistration(Drawable* pMgr) { pMgr->SceneDeregistration(); }
	};
};

#endif _DrawableAttorney