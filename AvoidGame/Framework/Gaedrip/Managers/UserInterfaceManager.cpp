#include "Framework.h"
#include "UserInterfaceManager.h"

#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"
#include "Gaedrip/CustomizedObjects/Entities/Player.h"

bool UserInterfaceManager::isMain = false;
bool UserInterfaceManager::reseted = false;
UserInterfaceManager::UserInterfaceManager()
{
}

UserInterfaceManager::~UserInterfaceManager()
{
}

void UserInterfaceManager::Update()
{

	if (!isMain)
	{
		score += Time::Delta();

		UIImages.energyBar->Update();
		UIImages.blinder->Update();

		if (isKeyLeftTurnedOn)
			UIImages.keyLeftOn->Update();
		else
			UIImages.keyLeftOff->Update();

		if (isKeyRightTurnedOn)
			UIImages.keyRightOn->Update();
		else
			UIImages.keyRightOff->Update();

		for (UINT i = 0; i < UIImages.lifeImages.size(); i++)
			UIImages.lifeImages[i]->Update();

		UIImages.keyJump->Update();

		for (UINT i = 0; i < UIImages.scoreImages.size(); i++)
			UIImages.scoreImages[i]->Update();
		return;
	}
	UIImages.buttonStart2->Update();
	UIImages.buttonSetting->Update();
	UIImages.gear->Update();
	UIImages.title->Update();

}

void UserInterfaceManager::Render()
{

	if (!isMain)
	{
		UIImages.energyBar->Render();
		UIImages.blinder->Render();

		if (isKeyLeftTurnedOn)
			UIImages.keyLeftOn->Render();
		else
			UIImages.keyLeftOff->Render();

		if (isKeyRightTurnedOn)
			UIImages.keyRightOn->Render();
		else
			UIImages.keyRightOff->Render();

		for (UINT i = 0; i < UIImages.lifeImages.size(); i++)
			UIImages.lifeImages[i]->Render();

		UIImages.keyJump->Render();

		for (UINT i = 0; i < UIImages.scoreImages.size(); i++)
			UIImages.scoreImages[i]->Render();
		return;
	}

	UIImages.buttonStart2->Render();
	UIImages.buttonSetting->Render();
	UIImages.gear->Render();
	UIImages.title->Render();

}

void UserInterfaceManager::Reset()
{
	UIImages.Reset();
	score = 0;
	isKeyLeftTurnedOn = false;
	isKeyRightTurnedOn = false;

}

void UserInterfaceManager::ManageMainScreen()
{
	if (Keyboard::Get()->Down(VK_DOWN))
	{
		selectionNumber--;
		if (selectionNumber == -1)
			selectionNumber = 1;

		SelectButtonMainScreen();
	}
	if (Keyboard::Get()->Down(VK_UP))
	{
		selectionNumber++;
		if (selectionNumber == 2)
			selectionNumber = 0;
		SelectButtonMainScreen();
	}
	if (Keyboard::Get()->Down(VK_RETURN) && selectionNumber == 0)
	{
		isMain = false;
		reseted = true;
	}
	if (Mouse::Get()->Down(0x000000))
	{
		Vector3 mousePos = Mouse::Get()->GetPosition();

		Transform& settingTransform = UIImages.buttonSetting->transform;
		Transform& gearTransform = UIImages.gear->transform;
		Transform& startTransform = UIImages.buttonStart2->transform;

		cout << mousePos.x << endl;
		cout << startTransform.GetPosition().x - startTransform.GetSizeOfWidth() / 2 << endl;
		if (mousePos.x > startTransform.GetPosition().x - startTransform.GetSizeOfWidth() / 2 && 
			mousePos.x < startTransform.GetPosition().x + startTransform.GetSizeOfWidth() / 2 && 
			mousePos.y < startTransform.GetPosition().y + startTransform.GetSizeOfHeight() / 2 &&
			mousePos.y > startTransform.GetPosition().y - startTransform.GetSizeOfHeight() / 2 )
		{
			isMain = false;
			reseted = true;
		}	
	}
}

void UserInterfaceManager::SelectButtonMainScreen()
{

	Transform& settingTransform = UIImages.buttonSetting->transform;
	Transform& gearTransform = UIImages.gear->transform;
	Transform& startTransform = UIImages.buttonStart2->transform;

	switch (selectionNumber)
	{
	case 0:
		// 스타트 버튼 활성화
		startTransform.SetSize(UIImages.buttonStart->transform.GetSize() * 1.5f );

		settingTransform.SetSize({ 100, 30, 0 });
		
		settingTransform.SetPosition({ gearTransform.GetPosition().x, gearTransform.GetPosition().y - (gearTransform.GetSizeOfHeight() / 2) -
			(settingTransform.GetSizeOfHeight() / 2), 0 });

		break;
	case 1:
		// 세팅 버튼 활성화
		settingTransform.SetSize(settingTransform.GetSize() * 1.5f );
		settingTransform.SetPosition(
			{ gearTransform.GetPosition().x, (gearTransform.GetPosition().y - (gearTransform.GetSizeOfHeight() / 2)) - (settingTransform.GetSizeOfHeight() / 2), 0 });
			
		
		startTransform.SetSize({ 235, 90, 0 } );
		break;
	default:
		break;

	}
}

void UserInterfaceManager::Execute()
{
}

void UserInterfaceManager::ChangeMoveButtonColor(Player* player)
{
	if (Keyboard::Get()->Press(VK_LEFT))
		isKeyLeftTurnedOn = true;
	else
		isKeyLeftTurnedOn = false;
	
	if (Keyboard::Get()->Press(VK_RIGHT))
		isKeyRightTurnedOn = true;
	else
		isKeyRightTurnedOn = false;
}

void UserInterfaceManager::ChangeJumpButtonColor(Player* player)
{
}

void UserInterfaceManager::AdjustEnergyBar(Player* player)
{	
	UIImages.energyBar->transform.SetPositionX(140 + player->GetEnergy() * 165);
}

void UserInterfaceManager::AdjustScoreImage()
{
	vector<TextureRect*> scoreImages = UIImages.scoreImages;
	//vector<TextureRect*> scoreImages = userInterface->GetScoreImages();
	Vector3 standardPosition = { 900, 640, 0 };
	float widthHarf = scoreImages[0]->transform.GetSizeOfWidth() / 2;
	float width = scoreImages[0]->transform.GetSizeOfWidth();


	int number1;
	int number2;
	int number3;
	int number4;
	int scoreInt = score * 10;
	//cout << scoreInt << endl;

	string str = to_string(scoreInt);
	int strLength = str.length();
	//std::cout << "입력된 문자열: "<< scoreInt << "\n" << "변환된 문자열: " << str << "\n" << "문자열 길이: " << strLength << "\n";

	switch (strLength)
	{
	case 1:
		number1 = std::stoi(str.substr(0, 1));
		setNumberPieceImage(scoreImages[0], number1);
		scoreImages[0]->transform.SetPosition(standardPosition);

		break;
	case 2:
		number1 = std::stoi(str.substr(1, 1));
		setNumberPieceImage(scoreImages[0], number1);

		number2 = std::stoi(str.substr(0, 1));
		setNumberPieceImage(scoreImages[1], number2);

		UIImages.scoreImages[0]->transform.SetPosition(Vector3(standardPosition.x + widthHarf, standardPosition.y, 0));
		UIImages.scoreImages[1]->transform.SetPosition(Vector3(standardPosition.x - widthHarf, standardPosition.y, 0));


		break;
	case 3:
		number1 = std::stoi(str.substr(2, 1));
		setNumberPieceImage(scoreImages[0], number1);

		number2 = std::stoi(str.substr(1, 1));
		setNumberPieceImage(scoreImages[1], number2);

		number3 = std::stoi(str.substr(0, 1));
		setNumberPieceImage(scoreImages[2], number3);


		UIImages.scoreImages[0]->transform.SetPosition(Vector3(standardPosition.x + width, standardPosition.y, 0));
		UIImages.scoreImages[1]->transform.SetPosition(standardPosition);
		UIImages.scoreImages[2]->transform.SetPosition(Vector3(standardPosition.x - width, standardPosition.y, 0));

		break;
	case 4:
		number1 = std::stoi(str.substr(3, 1));
		setNumberPieceImage(scoreImages[0], number1);

		number2 = std::stoi(str.substr(2, 1));
		setNumberPieceImage(scoreImages[1], number2);

		number3 = std::stoi(str.substr(1, 1));
		setNumberPieceImage(scoreImages[2], number3);

		number4 = std::stoi(str.substr(0, 1));
		setNumberPieceImage(scoreImages[3], number4);

		UIImages.scoreImages[0]->transform.SetPosition(Vector3(standardPosition.x + widthHarf + width, standardPosition.y, 0));
		UIImages.scoreImages[1]->transform.SetPosition(Vector3(standardPosition.x + widthHarf, standardPosition.y, 0));
		UIImages.scoreImages[2]->transform.SetPosition(Vector3(standardPosition.x - widthHarf, standardPosition.y, 0));
		UIImages.scoreImages[3]->transform.SetPosition(Vector3(standardPosition.x - widthHarf - width, standardPosition.y, 0));

		break;
	default:
		break;
	}
}

void UserInterfaceManager::AdjustHpBar(Player* player)
{
	int currentHp = player->getHp();
	
	if (currentHp < 0)
		return;
	
	for (int i = 0; i < currentHp; i++)
	{
		UIImages.lifeImages[i]->transform.SetPosition({UIImages.lifePosition.x + i * 25, UIImages.lifePosition.y, 0});
	}
	for (int i = currentHp; i < UIImages.lifeCount; i++)
	{
		
		UIImages.lifeImages[i]->transform.SetPosition({2000, 2000, 0});
	}

}

void UserInterfaceManager::setNumberPieceImage(TextureRect* NumberPieceImage, int number)
{
	switch (number)
	{
	case 1:
		NumberPieceImage->SetPath(PathGaedrip + L"Number1.png");
		break;
	case 2:
		NumberPieceImage->SetPath(PathGaedrip + L"Number2.png");
		break;
	case 3:
		NumberPieceImage->SetPath(PathGaedrip + L"Number3.png");
		break;
	case 4:
		NumberPieceImage->SetPath(PathGaedrip + L"Number4.png");
		break;
	case 5:
		NumberPieceImage->SetPath(PathGaedrip + L"Number5.png");
		break;
	case 6:
		NumberPieceImage->SetPath(PathGaedrip + L"Number6.png");
		break;
	case 7:
		NumberPieceImage->SetPath(PathGaedrip + L"Number7.png");
		break;
	case 8:
		NumberPieceImage->SetPath(PathGaedrip + L"Number8.png");
		break;
	case 9:
		NumberPieceImage->SetPath(PathGaedrip + L"Number9.png");
		break;
	case 0:
		NumberPieceImage->SetPath(PathGaedrip + L"Number0.png");
	default:
		break;
	}
}

/// ////////////////////////////////////////////////////////////////////////////////////

UserInterfaces::UserInterfaces()
{
	gear = new TextureRect(Vector3(100, 600, 0), Vector3(150, 150, 0), 0, PathGaedrip + L"gear.png");
	buttonStart = new TextureRect(Vector3(500, 500, 0), Vector3(235, 90, 0), 0, PathGaedrip + L"Text-Start.png");
	buttonStart2 = new TextureRect(Vector3(640, 200, 0), Vector3(235, 90, 0), 0, PathGaedrip + L"Text-Start2.png");
	buttonSetting = new TextureRect(Vector3(100, 100, 0), Vector3(100, 30, 0), 0, PathGaedrip + L"Text-Setting.png");
	title = new TextureRect(Vector3(640, 460, 0), Vector3(683, 280, 0), 0, PathGaedrip + L"Text-AvoidFromOverwatch.png");

	buttonSetting->transform.SetPosition(
		{gear->transform.GetPosition().x,
		gear->transform.GetPosition().y - (gear->transform.GetSizeOfHeight() / 2) - (buttonSetting->transform.GetSizeOfHeight() / 2), 0});

	keyRightOff = new TextureRect(Vector3(280, 50, 0),
		Vector3(161, 102, 1), 0.00f, PathGaedrip + L"KeyRightOff.png");

	keyRightOn = new TextureRect(Vector3(280, 50, 0),
		Vector3(161, 102, 1), 0.00f, PathGaedrip + L"KeyRightOn.png");

	keyLeftOff = new TextureRect(Vector3(105, 50, 0),
		Vector3(161, 102, 1), 0.00f, PathGaedrip + L"KeyLeftOff.png");

	keyLeftOn = new TextureRect(Vector3(105, 50, 0),
		Vector3(161, 102, 1), 0.00f, PathGaedrip + L"KeyLeftOn.png");

	keyJump = new TextureRect(Vector3(600, 55, 0),
		Vector3(900 / 3, 320 / 3, 1), 0.00f, PathGaedrip + L"keyJump.png");
	blinder = new Rect(Vector3(140, 30, 0),
		Vector3(1400, 150, 1), 0.00f);

	blinder->SetColor(Color(0, 0, 0, 1));

	energyBar = new Rect(Vector3(570, 50, 0),
		Vector3(1400, 90, 1), 0.00f);

	energyBar->SetColor(Color(0, 100, 0, 1));

	for (UINT i = 0; i < lifeCount; i++)
		lifeImages.push_back(new Rect({ lifePosition.x + i * 25, lifePosition.y, 0}, lifeSize, 0));

	scoreImages.push_back(new TextureRect(Vector3(2000, 2000, 0),
		Vector3(40, 40, 1), 0.00f, PathGaedrip + L"Number0.png"));
	scoreImages.push_back(new TextureRect(Vector3(2000, 2000, 0),
		Vector3(40, 40, 1), 0.00f, PathGaedrip + L"Number0.png"));
	scoreImages.push_back(new TextureRect(Vector3(2000, 2000, 0),
		Vector3(40, 40, 1), 0.00f, PathGaedrip + L"Number0.png"));
	scoreImages.push_back(new TextureRect(Vector3(2000, 2000, 0),
		Vector3(40, 40, 1), 0.00f, PathGaedrip + L"Number0.png"));
}

UserInterfaces::~UserInterfaces()
{
}

void UserInterfaces::Reset()
{
	gear->transform = Transform(Vector3(100, 600, 0), Vector3(150, 150, 0), 0);
	buttonStart->transform = Transform(Vector3(500, 500, 0), Vector3(235, 90, 0), 0);
	buttonStart2->transform = Transform(Vector3(640, 200, 0), Vector3(235, 90, 0), 0);
	buttonSetting->transform = Transform(Vector3(100, 100, 0), Vector3(100, 30, 0), 0);
	title->transform = Transform(Vector3(640, 460, 0), Vector3(683, 280, 0), 0);

	buttonSetting->transform.SetPosition(
		{ gear->transform.GetPosition().x,
		gear->transform.GetPosition().y - (gear->transform.GetSizeOfHeight() / 2) - (buttonSetting->transform.GetSizeOfHeight() / 2), 0 });


	keyRightOff->transform = Transform(Vector3(280, 50, 0), Vector3(161, 102, 1), 0.00f);

	keyRightOn->transform = Transform(Vector3(280, 50, 0), Vector3(161, 102, 1), 0.00f);

	keyLeftOff->transform = Transform(Vector3(105, 50, 0),Vector3(161, 102, 1), 0.00f);

	keyLeftOn->transform = Transform(Vector3(105, 50, 0), Vector3(161, 102, 1), 0.00f);

	keyJump->transform = Transform(Vector3(600, 55, 0), Vector3(900 / 3, 320 / 3, 1), 0.00f);

	blinder->transform = Transform(Vector3(140, 30, 0), Vector3(1400, 150, 1), 0.00f);

	energyBar->transform = Transform(Vector3(570, 50, 0), Vector3(1400, 90, 1), 0.00f);

	energyBar->SetColor(Color(0, 100, 0, 1));

	for (UINT i = 0; i < lifeCount; i++)
		lifeImages[i]->transform = Transform({lifePosition.x + i * 25, lifePosition.y, 0}, lifeSize, 0);

	for (UINT i = 0; i < scoreImages.size(); i++)
		scoreImages[i]->transform = Transform(Vector3(2000, 2000, 0), Vector3(40, 40, 1), 0.00f);

}
