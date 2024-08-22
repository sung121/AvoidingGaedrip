#include "stdafx.h"
#include "LevelCassidy.h"

LevelCassidy::LevelCassidy()
{
	skull = new TextureRect(Vector3(2000, 2000, 0), Vector3(40, 40, 0), 0, TexturePath + L"mccreeUltimateBlueMagenta.png");
	circle = new TextureRect(Vector3(2000, 2000, 0), Vector3(500, 500, 0), 0, TexturePath + L"mccreeUltimateCircleMagenta2.png");
	wall = new Rect(Vector3(2000, 2000, 0), Vector3(200, 400, 0), 0);
	wall->SetColor(Color(0, 100, 0, 0));

}

LevelCassidy::~LevelCassidy()
{
}

void LevelCassidy::ExcutePattern(Player* player)
{
	timeCassidy += Time::Delta();
	float spd = 300 * Time::Delta();

	Rect* playerObject = player->GetPlayerObject();
	
	if (timeCassidy >= 0 && ischeckCassidy == false)
	{
		ischeckCassidy = true;
		isFinished = false;
		isAttacked = false;
		isEnd = false;
		int temp1 = wall->GetSizeOfWidth() / 2;
		int temp2 = WinMaxWidth - wall->GetSizeOfWidth() / 2;

		random_device randDevice;
		uniform_int_distribution<int> intRand1(temp1, temp2);
		int posX = intRand1(randDevice);

		temp1 = 128 + wall->GetSizeOfHeight() / 2;
		temp2 = WinMaxHeight - wall->GetSizeOfHeight() / 2;

		uniform_int_distribution<int> intRand2(temp1, temp2);
		int posY = intRand2(randDevice);

		wall->SetPosition(Vector3(posX, posY, 0));
	}
	if (isEnd == false)
	{
		skull->SetPosition(playerObject->GetPosition());
		circle->SetPosition(playerObject->GetPosition());
		circle->SetSize(Vector3(circle->GetSize().x - spd, circle->GetSize().y - spd, 0));

		if (circle->GetSize().x < 0)
		{
			isEnd = true;
			isFinished = true;
			ischeckCassidy = false;
			circle->SetPosition(Vector3(2000, 2000, 0));
			circle->SetSize(Vector3(500, 500, 0));
			skull->SetPosition(Vector3(2000, 2000, 0));

			if (playerObject->GetPosition().x + playerObject->GetSizeOfWidth() / 2 < wall->GetPosition().x + wall->GetSizeOfWidth() / 2 &&
				playerObject->GetPosition().x - playerObject->GetSizeOfWidth()/2 > wall->GetPosition().x - wall->GetSizeOfWidth() / 2 &&
				playerObject->GetPosition().y < wall->GetPosition().y + wall->GetSizeOfHeight() / 2
				)
			{

			}
			else
			{
				player->HasDamage();
				isAttacked = true;
			}
			wall->SetPosition(Vector3(2000, 2000, 0));
		}
	}

}

void LevelCassidy::Update()
{
	skull->Update();
	circle->Update();
	wall->Update();
}

void LevelCassidy::Destroy()
{
	SAFE_DELETE(skull);
	SAFE_DELETE(circle);
	SAFE_DELETE(wall);

}
