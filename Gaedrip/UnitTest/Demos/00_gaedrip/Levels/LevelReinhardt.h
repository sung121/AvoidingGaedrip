#pragma once

#include "stdafx.h"
#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"
#include "Demos/00_gaedrip/GeometricObject.h"
#include "LevelObject.h"

class LevelReinhardt : public LevelObject
{
public:
	LevelReinhardt();
	~LevelReinhardt();

	// LevelObject을(를) 통해 상속됨
	void ExcutePattern() override;
	void Collide() override;
	bool GetIsFinished() override;
	

	/// <summary>
	/// //////////////////////////////////////////////////
	/// </summary>

	void Update();

	void ExcutePatternR(GeometricObject* geometricObject);

	void Init();


	TextureRect* GetReinhardtObject() { return reinhardt; }
	TextureRect* GetHammerRightObject() { return hammerRight; }
	TextureRect* GetHammerLeftObject() { return hammerLeft; }

	void Destroy();




private:


	TextureRect* reinhardt = nullptr;

	TextureRect* hammerRight = nullptr;
	TextureRect* hammerLeft = nullptr;

	float timeReinhardt;

	int EQSize = 28;
	bool isFinished = false;

	random_device* randDevice;

	
};

