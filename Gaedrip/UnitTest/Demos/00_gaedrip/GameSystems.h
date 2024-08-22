#pragma once
#include "../Framework/Framework.h"
#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"
#include "Demos/00_gaedrip/Levels/LevelReinhardt.h"
#include "Demos/00_gaedrip/Levels/LevelWreckingBall.h"
#include "Demos/00_gaedrip/GeometricObject.h"
#include "Demos/00_gaedrip/HealPack.h"
#include "Demos/00_gaedrip/UI.h"
#include "Demos/00_gaedrip/MainScreen.h"
#include "Player.h"

class LevelWreckingBall;

class GameSystems
{
public:
	GameSystems();
	~GameSystems();

	static bool CheckCollideGeometricObject(GeometricObject* geometricObject, Player* player);
	static bool CheckCollideHealPack(HealPack* healPack, Player* player);

	static bool CheckCollideLevelReinhardt(LevelReinhardt* levelReinhardt, Player* player);
	static bool CheckCollideLevelWreckingBall(LevelWreckingBall* levelWreckingBall, Player* player);
	static bool CheckCollideLevelWreckingBallWithPlatform(LevelWreckingBall* levelWreckingBall, GeometricObject* geometricObject);
	static bool CheckCollideDangerBox(GeometricObject* geometricObject, Player* player);

	static void CheckPlayerImmortal(Player* player);
	static void CheckPlayerDead(Player* player, TextureRect* defeatScreen, MainScreen* mainScreen);

	static void ApplyGravity(Player* player, float &gravitySpd, float gravitySpdOriginal);

	static void LimitEnergy(Player* player);

	static void AdjustEnergyBar(Player* player, UserInterface* userInterface);
	
	static void SetScoreBoard(UserInterface* userInterface, float score);

	static float GetposCoordinateSystemCenterX() { return WinMaxHeight / 2;}
	static float GetposCoordinateSystemCenterY() { return WinMaxWidth / 2; }


private:

	float posCoordinateSystemCenterX;
	float posCoordinateSystemCenterY;



};

