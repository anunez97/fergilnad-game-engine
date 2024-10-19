// Inputable Attorney

#ifndef _InputableAttorney
#define _InputableAttorney

#include "Inputable.h"
#include "InputEventType.h"

class InputableAttorney
{
public:
	class GameLoop
	{
		friend class SingleKeyEventManager;
	private:
		static void KeyPressed(Inputable* in, AZUL_KEY k) { in->KeyPressed(k); }
		static void KeyReleased(Inputable* in, AZUL_KEY k) { in->KeyReleased(k); }
	};

	class Registration
	{
		friend class InputRegistrationCommand;
		friend class InputDeregistrationCommand;
	private:
		static void SceneRegistration(Inputable* pMgr, AZUL_KEY k, InputEventType e) { pMgr->SceneRegistration(k, e); }
		static void SceneDeregistration(Inputable* pMgr, AZUL_KEY k, InputEventType e) { pMgr->SceneDeregistration(k, e); }
	};
};

#endif _InputableAttorney