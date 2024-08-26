#include "stdafx.h"
#include "GameSystems.h"

GameSystems::GameSystems()
{

}

GameSystems::~GameSystems()
{
}

bool GameSystems::CheckCollideGeometricObject(GeometricObject* geometricObject, Player* player)
{
	// 충돌 판정
	vector<TextureRect*> geometricBoxs = geometricObject->GetGeometricBoxs();

	Rect* systemPlayer = player->GetPlayerObject();


	for (TextureRect* tr : geometricBoxs)
	{

		BoundingBox* playerCollision = systemPlayer->GetCollision();
		BoundingBox* trCollision = tr->GetCollision();

		float playerLTY = playerCollision->GetEdge().LT.y;
		float playerLTX = playerCollision->GetEdge().LT.x;
		float playerRBY = playerCollision->GetEdge().RB.y;
		float playerRBX = playerCollision->GetEdge().RB.x;


		float trLTY = trCollision->GetEdge().LT.y;
		float trLTX = trCollision->GetEdge().LT.x;
		float trRBY = trCollision->GetEdge().RB.y;
		float trRBX = trCollision->GetEdge().RB.x;



		// 충돌 여부
		if (BoundingBox::AABB(playerCollision, trCollision) ||
			BoundingBox::OBB(playerCollision, trCollision))
		{

			// 아래에서 위
			if (playerLTY >= trRBY && playerLTY <= trLTY && playerRBY <= trRBY)
			{
				// float tmp = r->GetSizeOfHeight() / 2 + tr1->GetSizeOfHeight()/2;
				float tmp = trRBY;
				// 너비의 반 구하기
				tmp -= systemPlayer->GetSize().y * 0.5f;


			}
			//위에서 아래
			if (playerLTY >= trLTY && playerRBY >= trRBY && playerRBY <= trLTY)
			{

				float tmp = trLTY;
				tmp += systemPlayer->GetSizeOfHeight() * 0.5f;

				player->SetIsJump(false);
				player->SetIsJumpTwice(false);
				player->SetIsReachAtLimit(false);
				player->SetJumpSpd(2000);
				player->SetIsApplyGravity(false);


				systemPlayer->SetPosition(Vector3(systemPlayer->GetPosition().x, tmp + 0.01f, systemPlayer->GetPosition().z));
			}
			//오른쪽에서 왼쪽
			if (playerLTX >= trLTX && playerLTX <= trRBX && playerRBX >= trRBX)
			{
				// float tmp = r->GetSizeOfHeight() / 2 + tr1->GetSizeOfHeight()/2;

				float tmp = trRBX;
				tmp += systemPlayer->GetSize().x * 0.5f;

				systemPlayer->SetPosition(Vector3(tmp + 0.01f, systemPlayer->GetPosition().y, systemPlayer->GetPosition().z));
			}
			//왼쪽에서 오른쪽
			if (playerLTX <= trLTX && playerRBX >= trLTX && playerRBX >= trRBX)
			{
				// float tmp = r->GetSizeOfHeight() / 2 + tr1->GetSizeOfHeight()/2;

				float tmp = trLTX;
				tmp -= systemPlayer->GetSize().x * 0.5f;

				systemPlayer->SetPosition(Vector3(tmp - 0.01f, systemPlayer->GetPosition().y, systemPlayer->GetPosition().z));
			}
			return true;
		}
		{
		}

		//블럭 위 0.01f 올라갔을때
		if (((systemPlayer->GetPosition().y) == (trLTY + (systemPlayer->GetSizeOfHeight() * 0.5f) + 0.01f)))
			player->SetIsApplyGravity(false);

		if (((systemPlayer->GetPosition().y) == (trLTY + (systemPlayer->GetSizeOfHeight() * 0.5f) + 0.01f))
			&& ((systemPlayer->GetPosition().x) < ((trLTX - systemPlayer->GetSize().x * 0.5f))))
			player->SetIsApplyGravity(true);
		if (((systemPlayer->GetPosition().y) == (trLTY + (systemPlayer->GetSizeOfHeight() * 0.5f) + 0.01f))
			&& ((systemPlayer->GetPosition().x) > ((trRBX - systemPlayer->GetSize().x * 0.5f))))
			player->SetIsApplyGravity(true);

		/*else
	isApplyGravity = true;*/
	}


	return false;
}

bool GameSystems::CheckCollideHealPack(HealPack* healPack, Player* player)
{

	BoundingBox* playerCollision = player->GetPlayerObject()->GetCollision();
	BoundingBox* healPackCollision = healPack->GetHealPack()->GetCollision();


	if (BoundingBox::AABB(playerCollision, healPackCollision) ||
		BoundingBox::OBB(playerCollision, healPackCollision)
		)
	{
		healPack->GetHealPack()->SetPosition(Vector3(2000, 2000, 0));
		return true;
	}
	else
	{
		return false;
	}

}

bool GameSystems::CheckCollideLevelReinhardt(LevelReinhardt* reinhardt, Player* player)
{

	// 망치 충돌 판정
	{
		BoundingBox* playerCollision = player->GetPlayerObject()->GetCollision();
		BoundingBox* hammerLeftCollision = reinhardt->GetHammerLeftObject()->GetCollision();
		BoundingBox* hammerRightCollision = reinhardt->GetHammerRightObject()->GetCollision();
		BoundingBox* reinhardtCollision = reinhardt->GetReinhardtObject()->GetCollision();



		if (BoundingBox::AABB(playerCollision, hammerLeftCollision) ||
			BoundingBox::OBB(playerCollision, hammerLeftCollision) ||
			BoundingBox::AABB(playerCollision, hammerRightCollision) ||
			BoundingBox::OBB(playerCollision, hammerRightCollision) ||
			BoundingBox::AABB(playerCollision, reinhardtCollision) ||
			BoundingBox::OBB(playerCollision, reinhardtCollision)
			)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
}

bool GameSystems::CheckCollideLevelWreckingBall(LevelWreckingBall* wreckingBall, Player* player)
{
	{
		BoundingBox* playerCollision = player->GetPlayerObject()->GetCollision();
		BoundingBox* wreckingBallCollision = wreckingBall->GetWreckingBallObject()->GetCollision();



		if (BoundingBox::AABB(playerCollision, wreckingBallCollision) ||
			BoundingBox::OBB(playerCollision, wreckingBallCollision)
			)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
}

bool GameSystems::CheckCollideLevelWreckingBallWithPlatform(LevelWreckingBall* wreckingBall, GeometricObject* geometricObject)
{
	{
		BoundingBox* platformBigCollision = geometricObject->GetPlatformBig()->GetCollision();
		BoundingBox* wreckingBallCollision = wreckingBall->GetWreckingBallObject()->GetCollision();



		if (BoundingBox::AABB(platformBigCollision, wreckingBallCollision) ||
			BoundingBox::OBB(platformBigCollision, wreckingBallCollision)
			)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
}

bool GameSystems::CheckCollideDangerBox(GeometricObject* geometricObject, Player* player)
{
	BoundingBox* playerCollision = player->GetPlayerObject()->GetCollision();

	for (int i = 0; i < geometricObject->GetDangerBoxs().size(); i++)
	{

		BoundingBox* dangerBoxCollision = geometricObject->GetDangerBoxs()[i]->GetCollision();

		if (BoundingBox::AABB(dangerBoxCollision, playerCollision) ||
			BoundingBox::OBB(dangerBoxCollision, playerCollision)
			)
		{
			return true;
		}
		else
		{
		}
	}

	return false;
}

void GameSystems::CheckPlayerImmortal(Player* player)
{
	// 플레이어가 비무적일시 파랑으로 색깔 변경
	bool isPlayerImmortal = player->GetIsImmortal();

	if (isPlayerImmortal == true)
	{
		player->SetTimeImmortal(player->GetTimeImmortal() - Time::Delta());
		if (player->GetTimeImmortal() < 0)
		{
			player->SetIsImmortal(false);
			player->GetPlayerObject()->SetColor(Color(0, 0, 100, 1));
		}
	}
}

void GameSystems::CheckPlayerDead(Player* player, TextureRect* defeatScreen, MainScreen* mainScreen)
{
	if (player->GetLifes() == 0)
	{
		player->SetLifes(player->GetstandardLifes());
		player->GetPlayerObject()->SetPosition(Vector3(3000, 3000, 0));

		mainScreen->SetIsMain(true);
	}


}

void GameSystems::ApplyGravity(Player* player, float& gravitySpd, float gravitySpdOriginal)
{
	Rect* playerObject = player->GetPlayerObject();
	gravitySpd *= 1.1f;
	if (gravitySpd > 1500)
	{
		gravitySpd = 1500;
	}
	Vector3 pos = playerObject->GetPosition();
	playerObject->SetPosition(Vector3(pos.x, pos.y - gravitySpd * Time::Delta(), pos.z));
}

void GameSystems::LimitEnergy(Player* player)
{

	if (player->GetEnergy() > 2)
	{
		player->SetEnergy(2);
	}
}

void GameSystems::AdjustEnergyBar(Player* player, UserInterface* userInterface)
{
	//570 - 140 = 330

	Rect* energyBar = userInterface->GetEnergyBar();
	userInterface->GetEnergyBar()->SetPosition(Vector3(140 + player->GetEnergy() * 165, energyBar->GetPosition().y, 0));
}

void GameSystems::SetScoreBoard(UserInterface* userInterface, float score)
{
	vector<TextureRect*> scoreImages = userInterface->GetScoreImages();
	Vector3 standardPosition = { 900, 640, 0 };
	float widthHarf = scoreImages[0]->GetSizeOfWidth() / 2;
	float width = scoreImages[0]->GetSizeOfWidth();


	int number1;
	int number2;
	int number3;
	int number4;
	int scoreInt = score * 100;

	string str = to_string(scoreInt);
	int strLength = str.length();
	//std::cout << "입력된 문자열: "<< scoreInt << "\n" << "변환된 문자열: " << str << "\n" << "문자열 길이: " << strLength << "\n";

	switch (strLength)
	{
	case 1:
		number1 = std::stoi(str.substr(0, 1));
		userInterface->SetScoreImage(scoreImages[0], number1);
		scoreImages[0]->SetPosition(standardPosition);

		break;
	case 2:
		number1 = std::stoi(str.substr(1, 1));
		userInterface->SetScoreImage(scoreImages[0], number1);
		
		number2 = std::stoi(str.substr(0, 1));
		userInterface->SetScoreImage(scoreImages[1], number2);

		scoreImages[0]->SetPosition(Vector3(standardPosition.x + widthHarf, standardPosition.y, 0));
		scoreImages[1]->SetPosition(Vector3(standardPosition.x - widthHarf, standardPosition.y, 0));


		break;
	case 3:
		number1 = std::stoi(str.substr(2, 1));
		userInterface->SetScoreImage(scoreImages[0], number1);

		number2 = std::stoi(str.substr(1, 1));
		userInterface->SetScoreImage(scoreImages[1], number2);

		number3 = std::stoi(str.substr(0, 1));
		userInterface->SetScoreImage(scoreImages[2], number3);


		scoreImages[0]->SetPosition(Vector3(standardPosition.x + width , standardPosition.y, 0));
		scoreImages[1]->SetPosition(standardPosition);
		scoreImages[2]->SetPosition(Vector3(standardPosition.x - width, standardPosition.y, 0));
		
		break;
	case 4:
		number1 = std::stoi(str.substr(3, 1));
		userInterface->SetScoreImage(scoreImages[0], number1);
		
		number2 = std::stoi(str.substr(2, 1));
		userInterface->SetScoreImage(scoreImages[1], number2);

		number3 = std::stoi(str.substr(1, 1));
		userInterface->SetScoreImage(scoreImages[2], number3);

		number4 = std::stoi(str.substr(0, 1));
		userInterface->SetScoreImage(scoreImages[3], number4);

		scoreImages[0]->SetPosition(Vector3(standardPosition.x + widthHarf + width, standardPosition.y, 0));
		scoreImages[1]->SetPosition(Vector3(standardPosition.x + widthHarf, standardPosition.y, 0));
		scoreImages[2]->SetPosition(Vector3(standardPosition.x - widthHarf, standardPosition.y, 0));
		scoreImages[3]->SetPosition(Vector3(standardPosition.x - widthHarf - width, standardPosition.y, 0));

		break;
	default:
		break;
	}

	

}

