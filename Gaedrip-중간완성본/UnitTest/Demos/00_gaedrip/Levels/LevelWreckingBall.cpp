#include "stdafx.h"
#include "LevelWreckingBall.h"

LevelWreckingBall::LevelWreckingBall()
{
	wreckingBall = new TextureRect(Vector3(2000, 2000, 0),
		Vector3(300, 300, 1), 0, TexturePath + L"wreckingBall.png");

	wreckingBallRope = new Rect(Vector3(2000, 2000, 0), Vector3(30, 50, 1), 0.0f);



}

LevelWreckingBall::~LevelWreckingBall()
{
}


void LevelWreckingBall::ExcutePattern()
{
}

void LevelWreckingBall::Collide()
{
}

void LevelWreckingBall::ExcutePatternW(GeometricObject* geometricObject)
{

	timeWreckingBall += Time::Delta();
	float spd = 1200 * Time::Delta();

	float posCoordinateSystemCenterX;
	float posCoordinateSystemCenterY;

	posCoordinateSystemCenterX = GameSystems::GetposCoordinateSystemCenterX(); // 360
	posCoordinateSystemCenterY = GameSystems::GetposCoordinateSystemCenterY();	// 640
	float posYplatFormCenter = 215;

	float posX = wreckingBall->GetPosition().x;
	float posY = wreckingBall->GetPosition().y;
	static float postmpX = 0 - wreckingBall->GetSizeOfWidth() / 2;
	static float postmpY = 720 + wreckingBall->GetSizeOfHeight() / 2;



	if (timeWreckingBall < 0.1f && timeWreckingBall >= 0)
	{
		isFinished = false;
		wreckingBall->SetPosition(Vector3(0 - wreckingBall->GetSizeOfWidth() / 2, 720 + wreckingBall->GetSizeOfHeight() / 2, 0));
		wreckingBallRope->SetPosition(Vector3(-500, 500, 0));
	}
	// y = ax^2 + b;
	if (timeWreckingBall < 1)
	{

	}
	else if (timeWreckingBall < 3)
	{
		float a, b, c;
		a = 0.001f;
		b = posCoordinateSystemCenterX + wreckingBall->GetSizeOfWidth();
		c = posYplatFormCenter;
		postmpX += spd * 1;
		postmpY = a * ((postmpX - b) * (postmpX - b)) + c;
		wreckingBall->SetPosition(Vector3(postmpX - 100, postmpY, 0));
		wreckingBall->SetRotation(wreckingBall->GetRotation() - spd * 0.01f);
	}
	else if (timeWreckingBall < 3.5f)
	{
		wreckingBall->SetPosition(Vector3(1280 + wreckingBall->GetSizeOfWidth() / 2, 720 + wreckingBall->GetSizeOfHeight() / 2, 0));
		wreckingBallRope->SetPosition(Vector3(-500, 500, 0));
		postmpX = 1280 + wreckingBall->GetSizeOfWidth() / 2;
		postmpY = 720 + wreckingBall->GetSizeOfHeight() / 2;
	}
	// y = ax^2 + b;
	else if (timeWreckingBall < 6)
	{
		float a, b, c;
		a = 0.001f;
		b = posCoordinateSystemCenterX + wreckingBall->GetSizeOfWidth();
		c = posYplatFormCenter;
		postmpX -= spd * 1;
		postmpY = a * ((postmpX - b) * (postmpX - b)) + c;
		wreckingBall->SetPosition(Vector3(postmpX + 100, postmpY, 0));
		wreckingBall->SetRotation(wreckingBall->GetRotation() - spd * 0.01f);
	}
	else if (timeWreckingBall < 6.5f)
	{
		wreckingBall->SetSize(Vector3(350, 350, 1));
		wreckingBall->SetPosition(Vector3(640, 720 + wreckingBall->GetSizeOfHeight() / 2, 0));
		wreckingBall->SetRotation(0);
	}
	// ≥ª∑¡¬Ô∞Ì ∂•ø° ¥Í¿∏∏È √Êµπ ∆«¡§
	else if (timeWreckingBall < 9)
	{
		wreckingBall->SetPosition(Vector3(posX, posY - spd, 0));

		if (GameSystems::CheckCollideLevelWreckingBallWithPlatform(this, geometricObject) == true)
		{
			timeWreckingBall = 11;
		}

	}
	if (timeWreckingBall == 11)
	{
		for (int i = 0; i < geometricObject->GetDangerBoxs().size(); i++)
		{
			Rect* dangerBox = geometricObject->GetDangerBoxs()[i];
			if (i < 2)
			{
				if (0 == i % 2)
				{
					dangerBox->SetPosition(Vector3(640 + i * dangerBox->GetSizeOfWidth(), 0, 0));
				}
				else
				{
					dangerBox->SetPosition(Vector3(640 - i * dangerBox->GetSizeOfWidth(), 0, 0));
				}
			}
			else
			{
				if (0 == i % 2)
				{
					dangerBox->SetPosition(Vector3(640 + i * dangerBox->GetSizeOfWidth() / 2, 0, 0));
				}
				else
				{
					dangerBox->SetPosition(Vector3(640 - i * dangerBox->GetSizeOfWidth() / 2, 0, 0));
				}
			}
		}

	}
	if (timeWreckingBall < 11)
	{

	}
	else if (timeWreckingBall < 15)
	{
		for (int i = 0; i < geometricObject->GetDangerBoxs().size(); i++)
		{
			Rect* dangerBox = geometricObject->GetDangerBoxs()[i];
			dangerBox->SetPosition(Vector3(dangerBox->GetPosition().x, dangerBox->GetPosition().y + spd * 1.5f, 0));

		}
		if (geometricObject->GetDangerBoxs()[0]->GetPosition().y > 100)
		{
			timeWreckingBall = 17;
		}
	}
	if (timeWreckingBall < 17.5f)
	{
	}
	else if (timeWreckingBall < 19)
	{
		for (int i = 0; i < geometricObject->GetDangerBoxs().size(); i++)
		{
			Rect* dangerBox = geometricObject->GetDangerBoxs()[i];
			dangerBox->SetPosition(Vector3(dangerBox->GetPosition().x, dangerBox->GetPosition().y - spd * 1.5f, 0));
		}
	}
	else if (timeWreckingBall < 21)
	{
		wreckingBall->SetPosition(Vector3(posX, posY + spd * 0.8, 0));

	}
	else
	{
		uniform_int_distribution<int> intRand(0, 2);
		isFinished = true;
	}



}

void LevelWreckingBall::Destroy()
{
	SAFE_DELETE(wreckingBall);
	SAFE_DELETE(wreckingBallRope);

}

bool LevelWreckingBall::GetIsFinished()
{
	return isFinished;
}
