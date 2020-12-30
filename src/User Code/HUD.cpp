// HUD

#include "HUD.h"

#include "Fergilnad.h"
#include "HealthDisplay.h"
#include "ReloadDisplay.h"
#include "RadarDisplay.h"
#include "ReticleDisplay.h"
#include "ObjectiveDisplay.h"
#include "ScoreDisplay.h"

HUD* HUD::ptrInstance = nullptr;

HUD::HUD()
	:healthDisplay(0), reloadDisplay(0), radarDisplay(0), reticleDisplay(0), objectiveDisplay(0), scoreDisplay(0)
{
	healthDisplay = new HealthDisplay();
	reloadDisplay = new ReloadDisplay();
	radarDisplay = new RadarDisplay();
	reticleDisplay = new ReticleDisplay();
	objectiveDisplay = new ObjectiveDisplay();
	scoreDisplay = new ScoreDisplay();
}

HUD::~HUD()
{

}

void HUD::privInitialize()
{
	healthDisplay->Initialize();
	healthDisplay->SetPosition(Fergilnad::GetWidth() - 100, Fergilnad::GetHeight() - healthDisplay->GetHeight());

	reloadDisplay->Initialize();
	reloadDisplay->SetPosition(5, 0);

	radarDisplay->Initialize();
	radarDisplay->SetPosition(Fergilnad::GetWidth() - 100, 0);

	reticleDisplay->Initialize();
	reticleDisplay->SetPosition(Fergilnad::GetWidth() / 2, Fergilnad::GetHeight() / 2);

	scoreDisplay->Initialize();
	scoreDisplay->SetPosition(130, 0);

	objectiveDisplay->Initialize();
	objectiveDisplay->SetPosition(0, Fergilnad::GetHeight() - objectiveDisplay->GetHeight());
}

void HUD::privRenderHUD()
{
	healthDisplay->Render();
	reloadDisplay->Render();
	radarDisplay->Render();
	reticleDisplay->Render();
	scoreDisplay->Render();
	objectiveDisplay->Render();
}

void HUD::privUpdateScore(int score)
{
	scoreDisplay->SetScore(score);
}

void HUD::privUpdateReload()
{
	reloadDisplay->UpdateDisplay();
}

void HUD::privDelete()
{
	delete healthDisplay;
	delete reloadDisplay;
	delete radarDisplay;
	delete reticleDisplay;
	delete objectiveDisplay;
	delete scoreDisplay;

	delete ptrInstance;

	ptrInstance = nullptr;
}