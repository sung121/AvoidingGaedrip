#pragma once

#include "stdafx.h"
#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"
#include "LevelObject.h"
#include "../GameSystems.h"

class LevelPhara : public LevelObject
{
public:
	LevelPhara();
	~LevelPhara();


	// LevelObject을(를) 통해 상속됨
	void ExcutePattern() override;
	void Collide() override;
	bool GetIsFinished() override;

	void ExcutePattern(Player*);

	vector<Rect*> GetPharaMissiles() { return pharaMissiles; }

	void Destroy();

private:

	vector<Vector3*> missilesTargetPoint;
	vector<Rect*> pharaMissiles;

	float timePhara = 0;
	float timeCheckPhara = 0;

	bool isFinished = false;

	bool isCheckPhara = false;

	random_device randDevice;

};

