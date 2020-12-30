// Fergilnad Initialization

#include "Fergilnad.h"
#include "../User Code/HUD.h"

void Fergilnad::GameInitialize()
{
	// Game Window Setup
	Fergilnad::SetWindowName("Matrices and Movement");
	Fergilnad::SetWidthHeight(800, 600);
	Fergilnad::SetClearColor(0.4f, 0.4f, 0.8f, 1.0f);

	// Use this area, for one time non-graphic creation

	///HUD::Initialize();
}