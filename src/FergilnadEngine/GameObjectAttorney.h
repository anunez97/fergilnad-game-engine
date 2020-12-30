// GameObject Attorney

#ifndef _GameObjectAttorney
#define _GameObjectAttorney

#include "GameObject.h"

class GameObjectAttorney
{
	friend class GameObjectExitCommand;
	friend class GameObjectEntryCommand;

	static void ConnectToScene(GameObject* go) { go->ConnectToScene(); }
	static void DisconnectToScene(GameObject* go) { go->DisconnectToScene(); }

public:
	class Octree
	{
		friend class OctreeNode;

		static void SubmitExit(GameObject* go) { go->SubmitExit(); }
	};

};

#endif _GameObjectAttorney