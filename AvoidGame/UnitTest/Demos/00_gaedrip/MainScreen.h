#pragma once
#include "Geomatries/TextureRect.h"
#include "Geomatries/Rect.h"
#include "Geomatries/AnimationRect.h"



class MainScreen
{
public:
	MainScreen();
	~MainScreen();

	void Update();

	void Render();

	void Excute();

	bool GetIsMain() { return isMain; }
	void SetIsMain(bool param) { isMain = param; }

	TextureRect* GetButtonStart() { return buttonStart; }
	void SetButtonStart(TextureRect* param) { buttonStart = param; }
	
	TextureRect* GetButtonSetting() { return buttonSetting; }

	TextureRect* GetTitle() { return title; }

	void SelectToKeyboard();
	void SelectToMouse();

	void Destroy();

private:

	TextureRect* gear = nullptr;
	TextureRect* buttonStart = nullptr;
	TextureRect* buttonStart2 = nullptr;
	TextureRect* buttonSetting = nullptr;
	TextureRect* title = nullptr;
	char selectionNumber = 0;

	TextureRect* text_Start = nullptr;

	//AnimationRect* gear = nullptr;
	//TextureRect* buttonStart = nullptr;
	//TextureRect* buttonSetting = nullptr;
	//TextureRect* title = nullptr;

	bool isMain = true;


};

