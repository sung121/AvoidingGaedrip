#pragma once

#include "stdafx.h"
#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"
#include "Demos/00_gaedrip/GeometricObject.h"
#include "Demos/00_gaedrip/Player.h"
#include "Demos/00_gaedrip/GameSystems.h"
#include "LevelObject.h"

class LevelCassidy
{
public:
	LevelCassidy();
	~LevelCassidy();

	void ExcutePattern(Player* player);
	void Update();
	
	bool GetIsFinished() { return isFinished; }
	bool GetIsAttacked() { return isAttacked; }
	TextureRect* GetSkull() { return skull; }
	TextureRect* GetCircle() { return circle; }
	Rect* GetWall() { return wall; }

	void Destroy();

private:

	TextureRect* skull = nullptr;
	TextureRect* circle = nullptr;
	Rect* wall = nullptr;

	float timeCassidy = 0;
	bool ischeckCassidy = false;
	bool isEnd = false;
	bool isAttacked = false;


	bool isFinished = false;


};

