#pragma once

#include "stdafx.h"
#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"
#include "LevelObject.h"
#include "../GameSystems.h"

class GeometricObject;

class LevelWreckingBall : public LevelObject
{
public:

	LevelWreckingBall();
	~LevelWreckingBall();


	// LevelObject을(를) 통해 상속됨
	virtual void ExcutePattern() override;
	virtual void Collide() override;
	virtual bool GetIsFinished() override;

	void ExcutePatternW(GeometricObject* a);
	TextureRect* GetWreckingBallObject() { return wreckingBall; };
	Rect* GetWreckingBallRopeObject() { return wreckingBallRope; };

	void Destroy();

private:


	TextureRect* wreckingBall = nullptr;
	Rect* wreckingBallRope = nullptr;
	
	bool isFinished = false;

	float timeWreckingBall = 0;

	random_device randDevice;

};

