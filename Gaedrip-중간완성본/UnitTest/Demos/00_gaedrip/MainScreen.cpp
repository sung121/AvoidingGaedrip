#include "stdafx.h"
#include "MainScreen.h"

MainScreen::MainScreen()
{
	gear = new TextureRect(Vector3(100, 600, 0), Vector3(150, 150, 0), 0, TexturePath + L"gear.png");
	buttonStart = new TextureRect(Vector3(500, 500, 0), Vector3(235, 90, 0), 0, TexturePath + L"Text-Start.png");
	buttonStart2 = new TextureRect(Vector3(640, 200, 0), Vector3(235, 90, 0), 0, TexturePath + L"Text-Start2.png");
	buttonSetting = new TextureRect(Vector3(100, 100, 0), Vector3(100, 30, 0), 0, TexturePath + L"Text-Setting.png");
	title = new TextureRect(Vector3(640, 460, 0), Vector3(683 , 280 , 0), 0, TexturePath + L"Text-AvoidFromOverwatch.png");
	buttonSetting->SetPosition(Vector3(gear->GetPosition().x, gear->GetPosition().y - (gear->GetSizeOfHeight() / 2) - (buttonSetting->GetSizeOfHeight() / 2), 0));

}

MainScreen::~MainScreen()
{
}

void MainScreen::Update()
{
	gear->Update();
	buttonStart2->Update();
	buttonSetting->Update();
	title->Update();
	gear->Update();
}

void MainScreen::Render()
{
	gear->Render();
	buttonStart2->Render();
	buttonSetting->Render();
	title->Render();
	gear->Render();
}

void MainScreen::Excute()
{
	//좌클릭 == 0x000000 우클릭 == 0x000001 휠클릭 == 0x000002

	if (Keyboard::Get()->Down(VK_DOWN) || Keyboard::Get()->Down('s') || Keyboard::Get()->Down('S'))
	{
		selectionNumber--;
		if (selectionNumber == -1)
			selectionNumber = 1;

		SelectToKeyboard();
	}
	if (Keyboard::Get()->Down(VK_UP) || Keyboard::Get()->Down('w') || Keyboard::Get()->Down('W'))
	{
		selectionNumber++;
		if (selectionNumber == 2)
			selectionNumber = 0;
		SelectToKeyboard();
	}
	if (Keyboard::Get()->Down(VK_RETURN)|| Keyboard::Get()->Down(VK_SPACE))
	{
		if (selectionNumber == 0)
			isMain = false;
	}
	if (Mouse::Get()->Down(0x000000))
	{
		SelectToMouse();
	}
	
}

void MainScreen::SelectToKeyboard()
{
	switch (selectionNumber)
	{
	case 0:
		// 스타트 버튼 활성화
		buttonStart2->SetSize(buttonStart->GetSize() * 1.5f);

		buttonSetting->SetSize(Vector3(100, 30, 0));
		buttonSetting->SetPosition(Vector3(gear->GetPosition().x, gear->GetPosition().y - (gear->GetSizeOfHeight() / 2) - (buttonSetting->GetSizeOfHeight() / 2), 0));
		break;
	case 1:
		// 세팅 버튼 활성화
		buttonSetting->SetSize(buttonSetting->GetSize() * 1.5f);
		buttonSetting->SetPosition(Vector3(gear->GetPosition().x, (gear->GetPosition().y - (gear->GetSizeOfHeight() / 2)) - (buttonSetting->GetSizeOfHeight() / 2), 0));

		buttonStart2->SetSize(Vector3(235, 90, 0));
		buttonStart2->SetPosition(Vector3(640, 200, 0));
		break;
	default:
		break;
		
	}
}

void MainScreen::SelectToMouse()
{
	float posXMouse = Mouse::Get()->GetPosition().x;
	float posYMouse = Mouse::Get()->GetPosition().y;
	if (posXMouse < buttonStart2->GetPosition().x + buttonStart2->GetSizeOfWidth() /2	&&
		posXMouse > buttonStart2->GetPosition().x - buttonStart2->GetSizeOfWidth() /2	&&
		posYMouse < buttonStart2->GetPosition().y + buttonStart2->GetSizeOfHeight() /2	&&
		posYMouse > buttonStart2->GetPosition().y - buttonStart2->GetSizeOfHeight() / 2 )
	{
		isMain = false;
	}
	Mouse::Get()->GetPosition();
	
}

void MainScreen::Destroy()
{
	SAFE_DELETE(gear);
	SAFE_DELETE(buttonStart);
	SAFE_DELETE(buttonStart2);
	SAFE_DELETE(buttonSetting);
	SAFE_DELETE(title);
	SAFE_DELETE(text_Start);


}

