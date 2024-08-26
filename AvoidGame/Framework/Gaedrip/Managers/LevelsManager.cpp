#include "../../Framework.h"
#include "Framework.h"
#include "LevelsManager.h"

LevelsManager::LevelsManager(Ground* ground, Player* player, HealPack* healPack) : ground(ground), player(player), healPack(healPack)
{
	hammerLeft = new HammerLeft();
	hammerRight = new HammerRight();
	reinhardt = new Reinhardt();

	for (UINT i = 0; i < EQSize; i++)
		dangerBoxs.push_back(new DangerBox());

	// 18도 돌리기
	reinhardt->transform.SetPosition(Vector3(2000, 2000, 0));

	hammerLeft->transform.SetPosition({2000, 2000, 0});

	hammerRight->transform.SetPosition({ 2000, 2000, 0 });
	hammerLeft->transform.SetSize(Vector3(397 * 2, 133 * 2, 1));

	wreckingball = new Wreckingball();

	wreckingball->transform.SetPosition(WinCenterPos);

	skull = new TextureRect(Transform({2000, 2000, 0}, {40, 40, 0}, 0), PathGaedrip + L"mccreeUltimateBlueMagenta.png");
	circle = new TextureRect(Vector3(2000, 2000, 0), Vector3(500, 500, 0), 0, PathGaedrip + L"mccreeUltimateCircleMagenta2.png");
	
	wall = new Rect(Vector3(2000, 2000, 0), Vector3(200, 400, 0), 0);
	wall->SetColor(Color(0, 100, 0, 0));

	
	progressTime = 0;

	postmpX = 0 - wreckingball->transform.GetSizeOfWidth() / 2;
	postmpY = 720 + wreckingball->transform.GetSizeOfHeight() / 2;

}

LevelsManager::~LevelsManager()
{
}

void LevelsManager::Update()
{
	switch (currentLevel)
	{
	case Nothing:
		ChangeLevel();
		break;

	case LevelReinhardt:
		reinhardt->Update();
		hammerLeft->Update();
		hammerRight->Update();
		for (int i = 0; i < 10; i++)
		{
			dangerBoxs[i]->Update();
		}
		break;

	case LevelWreckingBall:
		wreckingball->Update();
		for (int i = 0; i < 10; i++)
		{
			dangerBoxs[i]->Update();
		}
		break;

	case LevelSigma:
		break;

	case LevelCassidy:
		skull->Update();
		circle->Update();
		wall->Update();

		break;
	default:
		break;
	}
}

void LevelsManager::Render()
{
	for (int i = 0; i < dangerBoxs.size(); i++)
	{
		dangerBoxs[i]->Render();
	}
	switch (currentLevel)
	{
	case LevelReinhardt:
		reinhardt->Render();
		hammerLeft->Render();
		hammerRight->Render();
		break;

	case LevelWreckingBall:
		wreckingball->Render();
		break;

	case LevelSigma:
		break;

	case LevelCassidy:
		skull->Render();
		circle->Render();
		wall->Render();

		break;
	default:
		break;
	}
}

void LevelsManager::Reset()
{
	currentLevel = Nothing;

	for (int i = 0; i < dangerBoxs.size(); i++)
	{
		dangerBoxs[i]->transform.SetSize({ 70, 150, 0 });
		dangerBoxs[i]->transform.SetPosition({ 2000, 2000, 0 });
	}

	reinhardt->transform.SetPosition(Vector3(2000, 2000, 0));

	hammerLeft->transform.SetPosition({ 2000, 2000, 0 });

	hammerRight->transform.SetPosition({ 2000, 2000, 0 });
	hammerLeft->transform.SetSize(Vector3(397 * 2, 133 * 2, 1));

	wreckingball->transform.SetPosition(WinCenterPos);

	postmpX = 0 - wreckingball->transform.GetSizeOfWidth() / 2;
	postmpY = 720 + wreckingball->transform.GetSizeOfHeight() / 2;

	skull->transform.SetPosition({ 2000, 2000, 0 });
	circle->transform.SetPosition({ 2000, 2000, 0 });
	wall->transform.SetPosition({ 2000, 2000, 0 });
	hasStartedCassidy = false;
	zoomedOut = false;
	Attacked = false;

	float raiseSpdSigma = 1;
	float dropSpd = 1;
	bool hasCreatedHealPack = false;
	bool hasStartedSigma = false;
	bool movesRightSigma = false;
	bool movesLeftSigma = false;

	healPack->transform.SetPosition(Vector3(2000, 2000, 0));

	progressTime = 0;



}

void LevelsManager::Excute()
{
	switch (currentLevel)
	{
	case LevelReinhardt:
		if (restTime < standardRestTime)
		{
			restTime += Time::Delta();
			return;
		}
		ExcuteReinhardt();
		for (int i = 0; i < 3; i++)
		{
			if (GameManager::CheckCollide(player->getCollider(), dangerBoxs[i]->getCollider()) && player->getIsImmortal() == false)
				GameManager::AttackPlayer(player);
		}
		if ((GameManager::CheckCollide(player->getCollider(), hammerLeft->getCollider()) && (player->getIsImmortal() == false)))
			GameManager::AttackPlayer(player);

		if ((GameManager::CheckCollide(player->getCollider(), hammerRight->getCollider()) && (player->getIsImmortal() == false)))
			GameManager::AttackPlayer(player);

		if ((GameManager::CheckCollide(player->getCollider(), reinhardt->getCollider()) && (player->getIsImmortal() == false)))
			GameManager::AttackPlayer(player);

			break;

	case LevelWreckingBall:
		ExcuteWreckingBall();

		if ((GameManager::CheckCollide(player->getCollider(), dangerBoxs[0]->getCollider())) && (player->getIsImmortal() == false))
		{
			GameManager::AttackPlayer(player);
		}
		if ((GameManager::CheckCollide(player->getCollider(), wreckingball->getCollider())) && (player->getIsImmortal() == false))
		{
			GameManager::AttackPlayer(player);
		}
		break;

	case LevelSigma:
		if (restTime < standardRestTime)
		{
			restTime += Time::Delta();
			return;
		}
		ExcuteSigma();

		if (GameManager::CheckCollide(player->getCollider(), healPack->getCollider()))
		{
			GameManager::AttackPlayer(player, -1, false);
			healPack->transform.SetPosition({ 2000, 2000, 0 });
		}
		break;

	case LevelCassidy:
		if (restTime < standardRestTime)
		{
			restTime += Time::Delta();
			return;
		}
		ExcuteCassidy();
		break;
	default:
		break;
	}
}

void LevelsManager::ExcuteReinhardt()
{
	progressTime += Time::Delta();


	float spd = 1000 * Time::Delta();
	float rotSpd = 1000 * Time::Delta();
	float spdEarthQuake = 1.2f;

	float rotationLeft = hammerLeft->transform.GetRotation();
	float rotationRight = hammerRight->transform.GetRotation();

	float posXLeft = hammerLeft->transform.GetPosition().x;
	float posXRight = hammerRight->transform.GetPosition().x;

	float posYLeft = hammerLeft->transform.GetPosition().y;
	float posYRight = hammerRight->transform.GetPosition().y;

	static float standardPosYEarthQuake = -20;

	static bool sorts = false;

	if (progressTime < 0.1f && progressTime >= 0)
	{
		isFinished = false;
		hammerLeft->transform.SetPosition(Vector3(1700, 500, 0));
		hammerRight->transform.SetPosition(Vector3(-500, 500, 0));
		return;

	}
	else if (1 > progressTime)
	{
		if (posXLeft > 1200)
		{
			hammerLeft->transform.SetPosition(Vector3(posXLeft - spd, 500, 0));
		}
		if (posXRight < 0)
		{
			hammerRight->transform.SetPosition(Vector3(posXRight + spd, 500, 0));

		}
		return;
	}
	else if (progressTime < 1.5f)
	{
		if (rotationLeft > -0.4f)
		{
			hammerLeft->transform.SetRotation(rotationLeft - spd * 0.001f);
			return;
		}
	}	//회전하며 내려찍기
	else if (progressTime < 4)
	{
		if (posYLeft > 255)
		{
			hammerLeft->transform.SetPosition(Vector3(posXLeft, posYLeft - spd * 1.3f, 0));
		}
		else
			progressTime = 5;
		if (rotationLeft < 0)
		{
			hammerLeft->transform.SetRotation(rotationLeft + spd * 0.002f);
		}
	}	//땅 밑에 정렬
	if (progressTime == 5)
	{
		for (int i = 0; i < 3; i++)
		{
			dangerBoxs[i]->transform.SetPosition(Vector3(posXLeft - 300 - (i * 50), posYLeft - 300, 0));
			//cout << dangerBoxs[i]->getCollider()->transform.GetPosition().y << endl;
		}
	}

	// 지진파 올라가는 코드
	if (5 <= progressTime && progressTime <= 7.5f)
	{
		
		if (progressTime < 5.1f + 0.1f * 3)
		{
			for (UINT i = 0; 5.1f + (0.1f * i) <= progressTime; i++)
			{
				if (dangerBoxs[i]->getMovesFirst() == false)
				{
					dangerBoxs[i]->setMovesUp(true);
					dangerBoxs[i]->setMovesFirst(true);
				}
			}
		}

		for (UINT i = 0; i < 3; i++)
		{
			
			if (dangerBoxs[i]->getMovesUp() == true)
			{
				dangerBoxs[i]->transform.SetPositionY(dangerBoxs[i]->transform.GetPosition().y + spd * spdEarthQuake);
				//방향 전환
				if (dangerBoxs[i]->transform.GetPosition().y > standardPosYEarthQuake + 170 )
				{
					dangerBoxs[i]->transform.SetPositionY(standardPosYEarthQuake + 170);
					dangerBoxs[i]->setMovesUp(false);
					dangerBoxs[i]->setMovesDown(true);
				}
			}
			else if(dangerBoxs[i]->getMovesDown() == true)
			{
				dangerBoxs[i]->transform.SetPositionY(dangerBoxs[i]->transform.GetPosition().y - spd * spdEarthQuake);
				//방향 전환
				if ( dangerBoxs[i]->transform.GetPosition().y < standardPosYEarthQuake )
				{
					dangerBoxs[i]->transform.SetPositionY(standardPosYEarthQuake);
					dangerBoxs[i]->setMovesDown(false);
					dangerBoxs[i]->setMovesUp(true);
					dangerBoxs[i]->transform.SetPositionX(dangerBoxs[i]->transform.GetPosition().x - (( dangerBoxs[i]->transform.GetSize().x ) + ( dangerBoxs[i]->transform.GetSize().x / 2 )));
				}
			}
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////// 왼쪽 망치 내리찍기
	if (progressTime < 7.5f)
	{
	}
	else if (progressTime < 8)
	{
		progressTime = 8;
		for (int i = 0; i < 10; i++)
		{
			dangerBoxs[i]->transform.SetPosition({ 2000, 2000, 0 });
			dangerBoxs[i]->setMovesFirst(false);
			dangerBoxs[i]->setMovesUp(false);
			dangerBoxs[i]->setMovesDown(false);

		}
	}
	else if (8.5f > progressTime)
	{
		if (rotationRight < 0.4f)
		{
			hammerRight->transform.SetRotation(rotationRight + spd * 0.001f);
		}
	}
	else if (12 > progressTime)
	{
		if (posYRight > 255)
		{
			hammerRight->transform.SetPosition(Vector3(posXRight, posYRight - spd * 1.3f, 0));
		}
		else
			progressTime = 13;
		if (rotationRight > 0)
		{
			hammerRight->transform.SetRotation(rotationRight - spd * 0.002f);
		}
	}
	// 정렬
	if (progressTime == 13)
	{
		for (int i = 0; i < 3; i++)
			dangerBoxs[i]->transform.SetPosition(Vector3(posXRight + 360 + (i * 50), posYLeft - 300, 0));
	}
	// 지진파 올라가는 코드
	if (13 <= progressTime && progressTime <= 15.5f)
	{

		if (progressTime < 13.0f + 0.1f * 3)
		{
			for (UINT i = 0; 13.0f + (0.1f * i) <= progressTime; i++)
			{
				if (dangerBoxs[i]->getMovesFirst() == false)
				{
					dangerBoxs[i]->setMovesUp(true);
					dangerBoxs[i]->setMovesFirst(true);
				}
			}
		}

		for (UINT i = 0; i < 3; i++)
		{

			if (dangerBoxs[i]->getMovesUp() == true)
			{
				dangerBoxs[i]->transform.SetPositionY(dangerBoxs[i]->transform.GetPosition().y + spd * spdEarthQuake);
				//방향 전환
				if (dangerBoxs[i]->transform.GetPosition().y > standardPosYEarthQuake + 170)
				{
					dangerBoxs[i]->transform.SetPositionY(standardPosYEarthQuake + 170);
					dangerBoxs[i]->setMovesUp(false);
					dangerBoxs[i]->setMovesDown(true);
				}
			}
			else if (dangerBoxs[i]->getMovesDown() == true)
			{
				dangerBoxs[i]->transform.SetPositionY(dangerBoxs[i]->transform.GetPosition().y - spd * spdEarthQuake);
				//방향 전환
				if (dangerBoxs[i]->transform.GetPosition().y < standardPosYEarthQuake)
				{
					dangerBoxs[i]->transform.SetPositionY(standardPosYEarthQuake);
					dangerBoxs[i]->setMovesDown(false);
					dangerBoxs[i]->setMovesUp(true);
					dangerBoxs[i]->transform.SetPositionX(dangerBoxs[i]->transform.GetPosition().x + ((dangerBoxs[i]->transform.GetSize().x) + (dangerBoxs[i]->transform.GetSize().x / 2)));
				}
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	if (progressTime < 15.5f)
	{

	}
	else if (progressTime < 16.0f)
	{
		progressTime = 16.0f;
		if (progressTime == 16.0f)
		{
			for (int i = 0; i < 10; i++)
			{
				dangerBoxs[i]->transform.SetPosition({ 2000, 2000, 0 });
				dangerBoxs[i]->setMovesFirst(false);
				dangerBoxs[i]->setMovesUp(false);
				dangerBoxs[i]->setMovesDown(false);
			}
		}
		reinhardt->transform.SetPosition(Vector3(-1000, 385, 0));
		hammerLeft->transform.SetPosition(Vector3(2000, 2000, 0));
		hammerRight->transform.SetPosition(Vector3(2000, 2000, 0));
	}
	else if (progressTime < 18.0f)
	{
		if (reinhardt->transform.GetPosition().x < 500)
		{
			reinhardt->transform.SetPosition(Vector3(reinhardt->transform.GetPosition().x + spd, 385, 0));
		}

	}
	else if (progressTime > 20)
	{
		reinhardt->transform.SetPosition(Vector3(2000, 2000, 0));
		isFinished = true;

		ChangeLevel();
	}
}

void LevelsManager::ExcuteWreckingBall()
{
	progressTime += Time::Delta();
	
	//cout << progressTime << endl;

	float spd = 1200 * Time::Delta();

	float centerPosX = WinCenterPos.x;
	float centerPosY = WinCenterPos.y;

	float posYplatFormCenter = 215;

	float posX = wreckingball->transform.GetPosition().x;
	float posY = wreckingball->transform.GetPosition().y;
	cout << posX << endl;

	if (progressTime < 0.1f && progressTime >= 0)
	{
		isFinished = false;
		wreckingball->transform.SetPosition(Vector3(0 - wreckingball->transform.GetSizeOfWidth() / 2, 720 + wreckingball->transform.GetSizeOfHeight() / 2, 0));
	}
	// y = ax^2 + b;
	if (progressTime < 1)
	{

	}
	else if (progressTime < 3)
	{
		cout << "움직이는중" << endl;
		cout << "레킹볼width: " << wreckingball->transform.GetSizeOfWidth() << endl;
		cout << "postmpX" << postmpX<< endl;

		float a, x, b;
		a = 0.001f;
		x = centerPosX + wreckingball->transform.GetSizeOfWidth();
		b = posYplatFormCenter;
		postmpX += spd * 1;
		postmpY = a * ((postmpX - x) * (postmpX - x)) + b;
		wreckingball->transform.SetPosition(Vector3(postmpX - 100, postmpY, 0));
		wreckingball->transform.SetRotation(wreckingball->transform.GetRotation() - spd * 0.01f);
	}
	else if (progressTime < 3.5f)
	{
		wreckingball->transform.SetPosition(Vector3(1280 + wreckingball->transform.GetSizeOfWidth() / 2, 720 + wreckingball->transform.GetSizeOfHeight() / 2, 0));
		postmpX = 1280 + wreckingball->transform.GetSizeOfWidth() / 2;
		postmpY = 720 + wreckingball->transform.GetSizeOfHeight() / 2;
	}
	// y = ax^2 + b;
	else if (progressTime < 6)
	{
		float a, b, c;
		a = 0.001f;
		b = centerPosX + wreckingball->transform.GetSizeOfWidth();
		c = posYplatFormCenter;
		postmpX -= spd * 1;
		postmpY = a * ((postmpX - b) * (postmpX - b)) + c;
		wreckingball->transform.SetPosition(Vector3(postmpX + 100, postmpY, 0));
		wreckingball->transform.SetRotation(wreckingball->transform.GetRotation() - spd * 0.01f);
	}
	else if (progressTime < 6.5f)
	{
		wreckingball->transform.SetSize(Vector3(350, 350, 1));
		wreckingball->transform.SetPosition(Vector3(640, 720 + wreckingball->transform.GetSizeOfHeight() / 2, 0));
		wreckingball->transform.SetRotation(0);
	}
	// 내려찍고 땅에 닿으면 충돌 판정
	else if (progressTime < 9)
	{
		wreckingball->transform.SetPosition(Vector3(posX, posY - spd, 0));

		if (GameManager::CheckCollide(wreckingball->getCollider(), ground->getCollider()) == true)
		{
			progressTime = 11;
		}

	}
	if (progressTime == 11)
	{
		dangerBoxs[0]->transform = Transform({WinCenterPos.x, -100, 0}, {{WinMaxWidth, 300, 0}}, 0);

	}
	
	if (progressTime < 11)
	{

	}
	else if (progressTime < 15)
	{
		dangerBoxs[0]->transform.SetPositionY( dangerBoxs[0]->transform.GetPosition().y + spd * 1.5f);
		
		if (dangerBoxs[0]->transform.GetPosition().y > 100)
		{
			progressTime = 17;
		}
	}
	if (progressTime < 17.5f)
	{
	}
	else if (progressTime < 19)
	{
		for (int i = 0; i < dangerBoxs.size(); i++)
		{
			StandardTransform& dangerBoxsTransform = dangerBoxs[i]->transform;
			dangerBoxsTransform.SetPosition(Vector3(dangerBoxsTransform.GetPosition().x, dangerBoxsTransform.GetPosition().y - spd * 1.5f, 0));
		}
	}
	else if (progressTime < 21)
	{
		wreckingball->transform.SetPosition(Vector3(posX, posY + spd * 0.8, 0));

	}
	else
	{
		uniform_int_distribution<int> intRand(0, 2);
		isFinished = true;
		postmpX = 0 - wreckingball->transform.GetSizeOfWidth() / 2;
		postmpY = 720 + wreckingball->transform.GetSizeOfHeight() / 2;

		ChangeLevel();
	}
	
}

void LevelsManager::ExcuteSigma()
{
	float spd = 1000 * Time::Delta();
	float rotSpd = 1000 * Time::Delta();

	progressTime += Time::Delta();


	if (progressTime > 0 && hasStartedSigma == false )
	{

		player->setJumps(true);
		player->setJumpsTwice(true);
		player->setApplysGravity(false);
		hasStartedSigma = true;
		isFinished = false;

	}
	// 나중에 가능하면 지수함수 이용하기
	if (hasStartedSigma == true)
	{
		// 플레이어 y값 600이상일시
		if ((player->transform.GetPosition().y > 600) && (hasCreatedHealPack == false))
		{	
			random_device randDevice;
			int temp1 = healPack->transform.GetSizeOfWidth() / 2;
			int temp2 = WinMaxWidth - healPack->transform.GetSizeOfWidth() / 2;
			uniform_int_distribution<int> intRand(temp1, temp2);
			int pos = intRand(randDevice);
			
			healPack->transform.SetPosition(Vector3(pos, 300, 0));
			hasCreatedHealPack = true;

		}
		else if(player->transform.GetPosition().y < 600) // y값이 600보다 작을시 y 축 수직 이동
		{
			player->setApplysGravity(false);

			player->transform.SetPositionY(player->transform.GetPosition().y + spd * raiseSpdSigma);
			raiseSpdSigma *= 0.94f;
			if (raiseSpdSigma < 0.15f)
			{
				raiseSpdSigma = 0.15f;
			}

		}

	}

	if (hasCreatedHealPack == true && progressTime < 5)
	{
		player->setApplysGravity(false);


		cout  << "콜리더: " << healPack->getCollider()->transform.GetPosition().x << endl;
		cout << "일반: " << healPack->transform.GetPosition().x << endl;

		if (healPack->transform.GetPosition().x > (WinMaxWidth - healPack->transform.GetSizeOfWidth() / 2))
			movesRightSigma = false;
		else if (healPack->transform.GetPosition().x < healPack->transform.GetSizeOfWidth() / 2)
		{
			movesRightSigma = true;
			cout << healPack->transform.GetPosition().x << endl;
		}

		if (movesRightSigma == true)
			healPack->transform.SetPosition(Vector3(healPack->transform.GetPosition().x + spd * 0.6f, healPack->transform.GetPosition().y, 0));
		else
			healPack->transform.SetPosition(Vector3(healPack->transform.GetPosition().x - spd * 0.6f, healPack->transform.GetPosition().y, 0));
	}	// 떨구기
	else if (hasCreatedHealPack == true)
	{
		player->setApplysGravity(true);
		player->transform.SetPosition(Vector3(player->transform.GetPosition().x, player->transform.GetPosition().y - spd * dropSpd, 0));

		if (GameManager::CheckCollide(ground->getCollider(), player->getCollider()) == true)
		{
			hasStartedSigma = false;
			GameManager::AttackPlayer(player, 1);
			raiseSpdSigma = 1;
			hasStartedSigma = false;
			hasCreatedHealPack = false;
			healPack->transform.SetPosition(Vector3(2000, 2000, 0));
			ChangeLevel();
		}
	}

}

void LevelsManager::ExcuteCassidy()
{
	progressTime += Time::Delta();
	float spd = 300 * Time::Delta();
	// 시작 하지 않았다면
	if (hasStartedCassidy == false)
	{
		hasStartedCassidy = true;
		Attacked = false;
		int temp1 = wall->transform.GetSizeOfWidth() / 2;
		int temp2 = WinMaxWidth - wall->transform.GetSizeOfWidth() / 2;

		random_device randDevice;
		uniform_int_distribution<int> intRand1(temp1, temp2);
		int posX = intRand1(randDevice);

		temp1 = 128 + wall->transform.GetSizeOfHeight() / 2;
		temp2 = WinMaxHeight - wall->transform.GetSizeOfHeight() / 2;

		uniform_int_distribution<int> intRand2(temp1, temp2);
		int posY = intRand2(randDevice);
		wall->transform.SetPosition(Vector3(posX, posY, 0));
		return;
	}

	//////////////////////////////////////////////////////////////////////
	// 시작했다면
	// 플레이어 위치에 맞워서 원을 축소하고 따라감.
	skull->transform.SetPosition(player->transform.GetPosition());
	circle->transform.SetPosition(player->transform.GetPosition());
	circle->transform.SetSize(Vector3(circle->transform.GetSize().x - spd, circle->transform.GetSize().y - spd, 0));

	// 원이 0 이상이면
	if (circle->transform.GetSize().x > 0)
		return;

	ChangeLevel();

	hasStartedCassidy = false;


	if (player->transform.GetPosition().x + player->transform.GetSizeOfWidth() / 2 < wall->transform.GetPosition().x + wall->transform.GetSizeOfWidth() / 2 &&
		player->transform.GetPosition().x - player->transform.GetSizeOfWidth() / 2 > wall->transform.GetPosition().x - wall->transform.GetSizeOfWidth() / 2 &&
		player->transform.GetPosition().y < player->transform.GetPosition().y + wall->transform.GetSizeOfHeight() / 2
		)
	{
	}
	else
	{
		GameManager::AttackPlayer(player);
	}


	circle->transform.SetPosition(Vector3(2000, 2000, 0));
	circle->transform.SetSize(Vector3(500, 500, 0));
	skull->transform.SetPosition(Vector3(2000, 2000, 0));
	wall->transform.SetPosition(Vector3(2000, 2000, 0));

	return;
	


	

}

void LevelsManager::ChangeLevel()
{
	{
		progressTime = 0;
		restTime = 0;
		uniform_int_distribution<int> intRand(1, 4);
		int level = intRand(randDevice);

		switch (level)
		{
		case 1:
			currentLevel = LevelReinhardt;
			break;

		case 2:
			currentLevel = LevelWreckingBall;
			break;

		case 3:
			currentLevel = LevelSigma;
			break;

		case 4:
			currentLevel = LevelCassidy;
			break;

		default:
			break;
		}

	}
}
