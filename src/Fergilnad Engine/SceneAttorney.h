// SceneAttorney

#ifndef _SceneAttorney
#define _SceneAttorney

#include "Scene.h"
#include "SceneManager.h"
#include "SceneManagerAttorney.h"
#include "InputEventType.h"

class SceneAttorney
{
public:
	class UpdateRegistration
	{
		friend class Updatable;
	private:
		static void Register(Scene* sc, Updatable* up, UpdatableManager::StorageListRef& ref) { sc->Register(up, ref); }
		static void Deregister(Scene* sc, UpdatableManager::StorageListRef ref) { sc->Deregister(ref); }
	};

public:
	class DrawRegistration
	{
		friend class Drawable;
	private:
		static void Register(Scene* sc, Drawable* dr, DrawableManager::StorageListRef& ref) { sc->Register(dr, ref); }
		static void Deregister(Scene* sc, DrawableManager::StorageListRef ref) { sc->Deregister(ref); }
	};

public:
	class AlarmRegistration
	{
		friend class Alarmable;
	private:
		static void Register(Scene* sc, float t, Alarmable* al, AlarmableManager::ALARM_ID id, AlarmableManager::StorageEntryRef& ref) { sc->Register(t, al, id, ref); }
		static void Deregister(Scene* sc, AlarmableManager::StorageEntryRef ref) { sc->Deregister(ref); }
	};

public:
	class InputRegistration
	{
		friend class Inputable;
	private:
		static void Register(Scene* sc, Inputable* in, AZUL_KEY k, InputEventType e, SingleKeyEventManager::StorageRef ref) { sc->Register(in, k, e, ref); }
		static void Deregister(Scene* sc, AZUL_KEY k, InputEventType e, SingleKeyEventManager::StorageRef ref) { sc->Deregister(k, e, ref); }
	};

public:
	class Registration
	{
		friend class Collidable;
		friend class OctreeNode;
	private:
		static CollisionManager* GetCollisionManager() { return SceneManager::GetCurrentScene()->pColMgr; }
	};

public:
	class GameLoop
	{
		friend class SceneManager;
	private:
		static void Update(Scene* s) { s->Update(); }
		static void Draw(Scene* s) { s->Draw(); }
	};

public:
	class Command
	{
		friend class Drawable;
		friend class Updatable;
		friend class Alarmable;
		friend class Inputable;
		friend class Collidable;
		friend class GameObject;

	private:
		static void Submit(Scene* s, CommandBase* cmd) { s->SubmitCommand(cmd); }
	};
};

#endif _SceneAttorney