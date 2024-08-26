#include "stdafx.h"
#include "LevelPhara.h"

LevelPhara::LevelPhara()
{
	for (int i = 0; i < 40; i++)
	{
		pharaMissiles.push_back(new Rect(Vector3(2000, 2000, 0), Vector3(30, 50, 1), 0.0f));
		pharaMissiles[i]->SetColor(Color(100, 0, 0, 1));
		missilesTargetPoint.push_back(new Vector3(2000, 2000, 0));
	}

}

LevelPhara::~LevelPhara()
{
}

void LevelPhara::ExcutePattern()
{
}

void LevelPhara::Collide()
{
}

bool LevelPhara::GetIsFinished()
{
    return false;
}

void LevelPhara::ExcutePattern(Player* player)
{

	float spd = 800 * Time::Delta();
	timePhara += Time::Delta();


	float posX = pharaMissiles[0]->GetPosition().x;
	float posY = pharaMissiles[0]->GetPosition().y;
	float distanceX = posX - missilesTargetPoint[0]->x;
	float distanceY = posY - missilesTargetPoint[0]->y;

	if (1 < timeCheckPhara && isCheckPhara == false)
	{
		uniform_int_distribution<int> intRand(0, WinMaxWidth);
		for (int i = 0; i < pharaMissiles.size(); i++)
		{

			float posX = intRand(randDevice);

			pharaMissiles[i]->SetPosition(Vector3(posX, 1400, 0));

		}
		isCheckPhara = true;
		timePhara = 2;
	}
	else
	{
		timeCheckPhara += Time::Delta();
	}
	if (timePhara == 2)
	{
		missilesTargetPoint[0]->x = player->GetPlayerObject()->GetPosition().x;
		missilesTargetPoint[0]->y = 135;
		printf("타켓 위치x : %f", missilesTargetPoint[0]->x);

	}
	if (timePhara < 2)
	{

	}
	else if (timePhara < 5)
	{

		printf("미사일과 플레이어 사이 거리: %f\n 미사일 위치: %f\n", distanceX, posX);


		pharaMissiles[0]->SetPosition(
			Vector3(posX - (distanceX * spd * 0.01f),
				posY - (distanceY * spd * 0.01f),
				0));
	}
}

void LevelPhara::Destroy()
{
	for (int i = 0; i < missilesTargetPoint.size(); i++)
		SAFE_DELETE(missilesTargetPoint[i]);

	for (int i = 0; i < pharaMissiles.size(); i++)
		SAFE_DELETE(pharaMissiles[i]);

}
