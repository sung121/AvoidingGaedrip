#include "stdafx.h"
#include "LevelReinhardt.h"

LevelReinhardt::LevelReinhardt()
{
	timeReinhardt = 0;

	isFinished = false;

	// 18도 돌리기
	reinhardt = new TextureRect(Vector3(2000, 2000, 0),
		Vector3(795 * 1.5, 440 * 1.5, 1), 0.2f, TexturePath + L"reinhardt.png");

	hammerRight = new TextureRect(Vector3(2000, 2000, 0),
		Vector3(397 * 2, 133 * 2, 1), 0.00f, TexturePath + L"HamaRight.png");

	hammerLeft = new TextureRect(Vector3(2000, 500, 0),
		Vector3(397 * 2, 133 * 2, 1), 0, TexturePath + L"HamaLeft.png");

	// 18도 돌리기
	reinhardt = new TextureRect(Vector3(2000, 2000, 0),
		Vector3(795 * 1.5, 440 * 1.5, 1), 0.2f, TexturePath + L"reinhardt.png");
}

LevelReinhardt::~LevelReinhardt()
{
}

void LevelReinhardt::ExcutePattern()
{
	
}

void LevelReinhardt::Collide()
{
}

bool LevelReinhardt::GetIsFinished()
{
	return isFinished;
}

void LevelReinhardt::Update()
{	
		hammerRight->Update();
		hammerLeft->Update();
		reinhardt->Update();
}

void LevelReinhardt::ExcutePatternR(GeometricObject* geometricObject)
{
	timeReinhardt += Time::Delta();

	vector<Rect*> dangerBox = geometricObject->GetDangerBoxs();

	float spd = 1000 * Time::Delta();
	float rotSpd = 1000 * Time::Delta();
	float spdEarthQuake = 1;

	float rotationLeft = hammerLeft->GetRotation();
	float rotationRight = hammerRight->GetRotation();

	float posXLeft = hammerLeft->GetPosition().x;
	float posXRight = hammerRight->GetPosition().x;

	float posYLeft = hammerLeft->GetPosition().y;
	float posYRight = hammerRight->GetPosition().y;


	if (timeReinhardt < 0.1f && timeReinhardt >= 0)
	{
		isFinished = false;
		hammerLeft->SetPosition(Vector3(1700, 500, 0));
		hammerRight->SetPosition(Vector3(-500, 500, 0));

	}
	else if (1 > timeReinhardt)
	{
		if (posXLeft > 1200)
		{
			hammerLeft->SetPosition(Vector3(posXLeft - spd, 500, 0));
		}
		if (posXRight < 0)
		{
			hammerRight->SetPosition(Vector3(posXRight + spd, 500, 0));

		}
	}
	else if (timeReinhardt < 1.5f)
	{
		if (rotationLeft > -0.4f)
		{
			hammerLeft->SetRotation(rotationLeft - spd * 0.001f);
		}
	}
	else if (timeReinhardt < 4)
	{
		if (posYLeft > 255)
		{
			hammerLeft->SetPosition(Vector3(posXLeft, posYLeft - spd * 1.3f, 0));
		}
		else
			timeReinhardt = 5;
		if (rotationLeft < 0)
		{
			hammerLeft->SetRotation(rotationLeft + spd * 0.002f);
		}
	}


	// 올라가는 코드
	

	for (int i = 0; i < dangerBox.size(); i++)
	{
		if (timeReinhardt < 5.15f + (i * 0.1f) && timeReinhardt > 5 + (i * 0.1f))
			dangerBox[i]->SetPosition(Vector3(posXLeft - 300 - (i * 50), dangerBox[i]->GetPosition().y + spd * spdEarthQuake, 0));
	}

	// 내려가는 코드
	for (int i = 0; i < dangerBox.size(); i++)
	{
		if (timeReinhardt < 6 + (i * 0.1f) && timeReinhardt > 5.2f + (i * 0.1f))
			dangerBox[i]->SetPosition(Vector3(posXLeft - 300 - (i * 50), dangerBox[i]->GetPosition().y - spd * spdEarthQuake, 0));

	}
	if (timeReinhardt == 5)
	{
		for (int i = 0; i < dangerBox.size(); i++)
			dangerBox[i]->SetPosition(Vector3(posXLeft - 300 - (i * 50), posYLeft - 300, 0));

	}
	//////////////////////////////////////////////////////////////////////////////////////////////////
	if (timeReinhardt < 7.5f)
	{

	}
	else if (8.5f > timeReinhardt)
	{
		if (rotationRight < 0.4f)
		{
			hammerRight->SetRotation(rotationRight + spd * 0.001f);
		}
	}
	else if (12 > timeReinhardt)
	{
		if (posYRight > 255)
		{
			hammerRight->SetPosition(Vector3(posXRight, posYRight - spd * 1.3f, 0));
		}
		else
			timeReinhardt = 13;
		if (rotationRight > 0)
		{
			hammerRight->SetRotation(rotationRight - spd * 0.002f);
		}
	}

	//올라가는 코드
	for (int i = 0; i < dangerBox.size(); i++)
	{
		if (timeReinhardt < 13.15f + (i * 0.1f) && timeReinhardt > 13 + (i * 0.1f))
			dangerBox[i]->SetPosition(Vector3(posXRight + 300 + (i * 50), dangerBox[i]->GetPosition().y + spd * spdEarthQuake, 0));
	}

	// 내려가는 코드
	for (int i = 0; i < dangerBox.size(); i++)
	{
		if (timeReinhardt < 14 + (i * 0.1f) && timeReinhardt > 13.2f + (i * 0.1f))
			dangerBox[i]->SetPosition(Vector3(posXRight + 300 + (i * 50), dangerBox[i]->GetPosition().y - spd * spdEarthQuake, 0));

	}
	if (timeReinhardt == 13)
	{
		for (int i = 0; i < dangerBox.size(); i++)
			dangerBox[i]->SetPosition(Vector3(posXRight + 300 + (i * 50), posYLeft - 300, 0));
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	if (timeReinhardt < 15.4f)
	{

	}
	else if (timeReinhardt < 15.5f)
	{
		reinhardt->SetPosition(Vector3(-1000, 385, 0));
		hammerLeft->SetPosition(Vector3(2000, 2000, 0));
		hammerRight->SetPosition(Vector3(2000, 2000, 0));
	}
	else if (timeReinhardt < 17.5f)
	{
		if (reinhardt->GetPosition().x < 500)
		{
			reinhardt->SetPosition(Vector3(reinhardt->GetPosition().x + spd, 385, 0));
		}

	}
	else if (timeReinhardt > 20)
	{
		reinhardt->SetPosition(Vector3(2000, 2000, 0));

		isFinished = true;
		timeReinhardt = 0;

	}
}

void LevelReinhardt::Init()
{
	timeReinhardt = 0;
}

void LevelReinhardt::Destroy()
{
	SAFE_DELETE(reinhardt);
	SAFE_DELETE(hammerLeft);
	SAFE_DELETE(hammerRight);
}
