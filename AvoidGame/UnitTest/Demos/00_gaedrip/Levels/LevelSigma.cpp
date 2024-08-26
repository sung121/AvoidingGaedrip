#include "stdafx.h"
#include "LevelSigma.h"

LevelSigma::LevelSigma()
{
	invisibleBox = new Rect(Vector3(2000, 500, 0), Vector3(50, 200, 1), 0.0f);
}

LevelSigma::~LevelSigma()
{
}

void LevelSigma::ExcutePatternS(Player* player, GeometricObject* geometricObject, HealPack* healPack)
{

	float spd = 1000 * Time::Delta();
	float rotSpd = 1000 * Time::Delta();

	Rect* playerObject = player->GetPlayerObject();
	timeSigma += Time::Delta();
	TextureRect* healPackObject = healPack->GetHealPack();


	if (timeSigma > 0 && checkSigma == false && checkReachGround == true)
	{
		
		player->SetIsJump(true);
		player->SetIsJumpTwice(true);
		player->SetIsApplyGravity(false);
		checkReachGround = false;
		checkSigma = true;
		isFinished = false;
			
	}
	// 나중에 가능하면 지수함수 이용하기
	if (playerObject->GetPosition().y < 600 && checkSigma == true && checkReachGround == false)
	{
		playerObject->SetPosition(Vector3(playerObject->GetPosition().x, playerObject->GetPosition().y + spd * raiseSpd, 0));
		raiseSpd *= 0.9f;
		if (raiseSpd < 0.2f)
		{
			raiseSpd = 0.2f;
		}
		player->SetIsApplyGravity(false);
		if (isSpawnedHealPack == false)
		{

			random_device randDevice;
			int temp1 = healPackObject->GetSizeOfWidth() / 2;
			int temp2 = WinMaxWidth - healPackObject->GetSizeOfWidth() / 2;
			uniform_int_distribution<int> intRand(temp1, temp2);
			int pos = intRand(randDevice);
			healPackObject->SetPosition(Vector3(pos, 300, 0));
			isSpawnedHealPack = true;
		}

	}
	else if(timeSigma < 5)
	{
		if (healPackObject->GetPosition().x > (WinMaxWidth - healPackObject->GetSizeOfWidth() / 2))
			isMoveRight = false;
		else if (healPackObject->GetPosition().x < healPackObject->GetSizeOfWidth() / 2)
			isMoveRight = true;
		if (isMoveRight == true)
			healPackObject->SetPosition(Vector3(healPackObject->GetPosition().x + spd * 0.3f, healPackObject->GetPosition().y, 0));
		else
			healPackObject->SetPosition(Vector3(healPackObject->GetPosition().x - spd * 0.3f, healPackObject->GetPosition().y, 0));
	}
	else if (true)
	{
		checkSigma = false;
		playerObject->SetPosition(Vector3(playerObject->GetPosition().x, playerObject->GetPosition().y - spd * dropSpd * 1.5f, 0));
		
		

		if (GameSystems::CheckCollideGeometricObject(geometricObject, player)  == true)
		{
			checkReachGround = true;
			timeSigma = 0;
			isFinished = true;
			player->SetIsApplyGravity(true);
			player->HasDamage();
			raiseSpd = 1;
			isAttacked = true;
			isSpawnedHealPack = false;
			healPackObject->SetPosition(Vector3(2000, 2000, 0));
		}
	}





}

bool LevelSigma::GetIsFinished()
{
    return isFinished;
}

void LevelSigma::Destroy()
{
	SAFE_DELETE(invisibleBox);
}
