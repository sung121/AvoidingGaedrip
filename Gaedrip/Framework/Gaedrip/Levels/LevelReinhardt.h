#pragma once
#include "Gaedrip/CustomizedObjects/DangerObjects/DangerBox.h"
#include "Gaedrip/Managers/GameManager.h"

class LevelReinhardt
{
public:
	LevelReinhardt();
	~LevelReinhardt();
	
	void ExcutePattern();

	void Update();

	void Init();


	
	void Destroy();

private:


	float timeReinhardt;

	int EQSize = 28;
	bool isFinished = false;

	random_device* randDevice;

};

