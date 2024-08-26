#pragma once

#include "stdafx.h"
#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"
#include "Demos/00_gaedrip/GeometricObject.h"
#include "Demos/00_gaedrip/Player.h"
#include "Demos/00_gaedrip/GameSystems.h"
#include "LevelObject.h"

class LevelSigma
{
public:
	LevelSigma();
	~LevelSigma();

	void ExcutePatternS(Player* player, GeometricObject* geometricObject, HealPack* healPack);

	bool GetIsFinished();
	bool GetIsAttacked() { return isAttacked; }
	bool GetisUsedItem() { return isUsedItem; }

	void Destroy();

private:

	bool isFinished = false;

	float timeSigma = 0;
	
	bool checkSigma = false;
	bool checkReachGround = true;

	float raiseSpd = 1;
	float dropSpd = 1;

	bool isAttacked = false;

	bool isUsedItem = false;
	bool isSpawnedHealPack = false;
	bool isMoveRight = true;

	Rect* invisibleBox;
};

