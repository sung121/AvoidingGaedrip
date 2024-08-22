#pragma once

#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"
#include "Demos/00_gaedrip/Levels/LevelReinhardt.h"
#include "Demos/00_gaedrip/Levels/LevelWreckingBall.h"
#include "Demos/00_gaedrip/Levels/LevelPhara.h"
#include "Demos/00_gaedrip/Levels/LevelSigma.h"
#include "Demos/00_gaedrip/Levels/LevelStart.h"
#include "Demos/00_gaedrip/HealPack.h"
#include "Demos/00_gaedrip/Levels/LevelCassidy.h"
#include "Demos/00_gaedrip/GameSystems.h"
#include "Demos/00_gaedrip/MainScreen.h"
#include "Player.h"
#include "UI.h"






class gaedrip : public IObject
{
public:

	// IObject을(를) 통해 상속됨
	void Init() override;
	void Destroy() override;
	void Update() override;
	void Render() override;
	void PostRender() override;
	void GUI() override;

	void UpdateAll();

	void ProgressRound();
	void BringUpDeathScreen();
	void BringUpMainScreen();

	void AdjustButtonsColor();
	void InitRound();
	void DestroyRound();

private:

	LevelReinhardt* reinhardt = nullptr;
	LevelWreckingBall* wreckingBall = nullptr;
	LevelPhara* phara = nullptr;
	LevelSigma* sigma = nullptr;
	LevelStart* start = nullptr;
	UserInterface* userInterface = nullptr;
	GeometricObject* geometricObject = nullptr;
	HealPack* healPack = nullptr;
	LevelStart* levelStart = nullptr;
	LevelCassidy* cassidy = nullptr;

	MainScreen* mainScreen = nullptr;
	
	Player* player = nullptr;

	TextureRect* screenDefeat = nullptr;
	Rect* backgroundSolid = nullptr;

	bool isMovingLeft = false;
	bool isMovingRight = false;
	bool isDestroyed = false;
	bool isInited = true;

	float standardGravitySpd;
	float gravitySpd;

	float timeAbsoulte = 0;

	short level;

	random_device randDevice;




};