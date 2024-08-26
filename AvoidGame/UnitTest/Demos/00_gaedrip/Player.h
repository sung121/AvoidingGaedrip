#pragma once

#include "../Framework/Framework.h"
#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"

class Player
{
public:

	Player(float jumpSpd, float jumpLimit);
	~Player();

	void Update();

	void SafeDelete();


	bool HasDamage();
	void CheckDead();

	Rect* GetPlayerObject() { return player; }

	void SetIsApplyGravity(bool params) { isApplyGravity = params; }
	bool GetIsApplyGravity() { return isApplyGravity; }

	void SetIsDead(bool params) { isPlayerDead = params; }
	bool GetIsDead() { return isPlayerDead; }

	void SetIsJump(bool params) { isJump = params; }
	bool GetIsJump() { return isJump; }

	void SetIsJumpTwice(bool params) { isJumpTwice = params; }
	bool GetIsJumpTwice() { return isJumpTwice; }

	void SetIsImmortal(bool params) {  isPlayerImmortal = params; }
	bool GetIsImmortal() { return isPlayerImmortal; }

	void SetIsReachAtLimit(bool params) { isReachAtLimit = params; }
	bool GetIsReachAtLimit() { return isReachAtLimit; }

	void SetJumpLimit(float params) { jumpLimit = params; }
	float GetJumpLimit() { return jumpLimit; }

	void SetJumpSpd(float params) { jumpSpd = params; }
	float GetJumpSpd() { return jumpSpd; }

	void SetTimeJump(float params) { timeJump = params; }
	float GetTimeJump() { return timeJump; }

	void SetTimeImmortal(float params) { timeImmortal = params; }
	float GetTimeImmortal() { return timeImmortal; }


	void SetLifes(int params) { lifes = params; }
	int GetLifes() { return lifes; }
	int GetstandardLifes() { return standardLifes; }

	void SetEnergy(float params) { energy = params; }
	float GetEnergy() { return energy; }
	float* GetEnergyPointer() { return &energy; }

	void Destroy();



	void Jump(float& gravitySpd, float gravitySpdOriginal);

private:
	Rect* player = nullptr;

	bool isMovingLeft = false;
	bool isMovingRight = false;


	bool isPlayerDead = false;
	bool isPlayerImmortal = false;

	bool isJump = false;
	bool isJumpTwice = false;

	bool isReachAtLimit = false;
	bool isReachAtLimitTwice = false;

	bool isApplyGravity = true;


	float jumpLimit;
	float jumpSpd;

	float timeJump = 0;
	float timeImmortal = 0;

	float energy = 1.5f;

	int lifes = 2;
	int standardLifes = 2;
};

