#include "stdafx.h"
#include "LevelStart.h"

void LevelStart::ExcutePattern()
{
}

void LevelStart::Collide()
{
}

bool LevelStart::GetIsFinished()
{
	return isFinished;
}

void LevelStart::ExcutePattern(GeometricObject* geometricObject)
{
	vector<TextureRect*> geometricBoxs = geometricObject->GetGeometricBoxs();

	float spd = 800 * Time::Delta();
	float posX1 = geometricBoxs[1]->GetPosition().x;
	float posY1 = geometricBoxs[1]->GetPosition().y;

	float posX2 = geometricBoxs[2]->GetPosition().x;
	float posY2 = geometricBoxs[2]->GetPosition().y;

	float posX3 = geometricBoxs[3]->GetPosition().x;
	float posY3 = geometricBoxs[3]->GetPosition().y;

	if (1 > timeStart && timeStart >= 0)
	{
		timeStart += Time::Delta();
	}
	else if (timeStart < 3)
	{

		if (posX1 < 200 - spd)
		{
			geometricBoxs[1]->SetPosition(Vector3(posX1 + spd, posY1, 0));
		}

		if (posY2 > 300 + spd)
		{
			geometricBoxs[2]->SetPosition(Vector3(posX2, posY2 - spd, 0));
		}

		if (posX3 > 1000 + spd)
		{
			geometricBoxs[3]->SetPosition(Vector3(posX3 - spd, posY3, 0));
		}
		timeStart += Time::Delta();
	}
	else if (timeStart >= 3)
	{
		geometricBoxs[1]->SetPosition(Vector3(posX1 - spd, posY1, 0));
		geometricBoxs[2]->SetPosition(Vector3(posX2, posY2 - spd, 0));
		geometricBoxs[3]->SetPosition(Vector3(posX3 + spd, posY3, 0));
		timeStart += Time::Delta();
	}


	if (timeStart >= 5)
	{
		timeStart = -1;
		isFinished = true;

	}
}
