#include "stdafx.h"
#include "UI.h"

UserInterface::UserInterface()
{
	keyRightOff = new TextureRect(Vector3(280, 50, 0),
		Vector3(161, 102, 1), 0.00f, TexturePath + L"KeyRightOff.png");

	keyRightOn = new TextureRect(Vector3(280, 50, 0),
		Vector3(161, 102, 1), 0.00f, TexturePath + L"KeyRightOn.png");

	keyLeftOff = new TextureRect(Vector3(105, 50, 0),
		Vector3(161, 102, 1), 0.00f, TexturePath + L"KeyLeftOff.png");

	keyLeftOn = new TextureRect(Vector3(105, 50, 0),
		Vector3(161, 102, 1), 0.00f, TexturePath + L"KeyLeftOn.png");

	keyJump = new TextureRect(Vector3(600, 50, 0),
		Vector3(900 / 3, 320 / 3, 1), 0.00f, TexturePath + L"keyJump.png");

	buttons.push_back(keyRightOff);

	buttons.push_back(keyRightOn);

	buttons.push_back(keyLeftOff);

	buttons.push_back(keyLeftOn);

	blinder = new Rect(Vector3(140, 30, 0),
		Vector3(1400, 150, 1), 0.00f);

	blinder->SetColor(Color(0, 0, 0, 1));

	energyBar = new Rect(Vector3(570, 50, 0),
		Vector3(1400, 90, 1), 0.00f);

	energyBar->SetColor(Color(0, 100, 0, 1));

	lifeImages.push_back(new Rect(Vector3(1100, 650, 0),
		Vector3(20, 40, 1), 0.00f));

	lifeImages.push_back(new Rect(Vector3(1125, 650, 0),
		Vector3(20, 40, 1), 0.00f));

	lifeImages.push_back(new Rect(Vector3(1150, 650, 0),
		Vector3(20, 40, 1), 0.00f));

	lifeImages.push_back(new Rect(Vector3(1175, 650, 0),
		Vector3(20, 40, 1), 0.00f));

	lifeImages.push_back(new Rect(Vector3(1200, 650, 0),
		Vector3(20, 40, 1), 0.00f));

	lifeImages.push_back(new Rect(Vector3(1225, 650, 0),
		Vector3(20, 40, 1), 0.00f));

	scoreImages.push_back(new TextureRect(Vector3(2000, 2000, 0),
		Vector3(40, 40, 1), 0.00f, TexturePath + L"Number0.png"));
	scoreImages.push_back(new TextureRect(Vector3(2000, 2000, 0),
		Vector3(40, 40, 1), 0.00f, TexturePath + L"Number0.png"));
	scoreImages.push_back(new TextureRect(Vector3(2000, 2000, 0),
		Vector3(40, 40, 1), 0.00f, TexturePath + L"Number0.png"));
	scoreImages.push_back(new TextureRect(Vector3(2000, 2000, 0),
		Vector3(40, 40, 1), 0.00f, TexturePath + L"Number0.png"));

}

UserInterface::~UserInterface()
{

}

void UserInterface::Update()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->Update();
	}
	keyJump->Update();

	blinder->Update();
	energyBar->Update();
	for (int i = 0; i < scoreImages.size(); i++)
	{
		scoreImages[i]->Update();
	}
	for (int i = 0; i < lifeImages.size(); i++)
	{
		lifeImages[i]->Update();
	}


}

void UserInterface::SetLifeImages(float lifes)
{
}

void UserInterface::SetScoreImage(TextureRect* scoreImage, int number)
{
	switch (number)
	{
	case 1:
		scoreImage->SetPath(TexturePath + L"Number1.png");
		break;
	case 2:
		scoreImage->SetPath(TexturePath + L"Number2.png");
		break;
	case 3:
		scoreImage->SetPath(TexturePath + L"Number3.png");
		break;
	case 4:
		scoreImage->SetPath(TexturePath + L"Number4.png");
		break;
	case 5:
		scoreImage->SetPath(TexturePath + L"Number5.png");
		break;
	case 6:
		scoreImage->SetPath(TexturePath + L"Number6.png");
		break;
	case 7:
		scoreImage->SetPath(TexturePath + L"Number7.png");
		break;
	case 8:
		scoreImage->SetPath(TexturePath + L"Number8.png");
		break;
	case 9:
		scoreImage->SetPath(TexturePath + L"Number9.png");
		break;
	case 0:
		scoreImage->SetPath(TexturePath + L"Number0.png");
	default:
		break;
	}

}

void UserInterface::Destroy()
{
	SAFE_DELETE(keyRightOff);
	SAFE_DELETE(keyRightOn);
	SAFE_DELETE(keyLeftOff);
	SAFE_DELETE(keyLeftOn);
	SAFE_DELETE(keyJump);
	SAFE_DELETE(blinder);
	SAFE_DELETE(energyBar);

	for (int i = 0; i < lifeImages.size(); i++)
		SAFE_DELETE(lifeImages[i]);

	for (int i = 0; i < scoreImages.size(); i++)
	{
		SAFE_DELETE(scoreImages[i]);
	}

	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i];
	}







}
