#pragma once
#include "BasicObjects/GameObject.h"
#include "Geomatries/TextureRect.h"
#include "Gaedrip/CustomizedObjects/Entities/Player.h"

struct UserInterfaces
{
	UserInterfaces();
	~UserInterfaces();

	//void Reset();

	//TextureRect* gear = nullptr;
	//TextureRect* buttonStart = nullptr;
	//TextureRect* buttonStart2 = nullptr;
	//TextureRect* buttonSetting = nullptr;
	//TextureRect* title = nullptr;

	//TextureRect* keyRightOff = nullptr;
	//TextureRect* keyRightOn = nullptr;
	//TextureRect* keyLeftOff = nullptr;
	//TextureRect* keyLeftOn = nullptr;
	//TextureRect* keyJump = nullptr;

	//vector<Rect*> lifeImages;
	//int lifeCount = 5;

	//vector<TextureRect*> scoreImages;
	//Vector3 scoreStandardPos = { 500, 500, 0 };

	//Transform lifeTransform = Transform(Vector3(1100, 650, 0), Vector3(20, 40, 1), 0.00f);
	//Vector3 lifePosition = lifeTransform.GetPosition();
	//Vector3 lifeSize = lifeTransform.GetSize();


	//
	//Rect* blinder = nullptr;
	//Rect* energyBar = nullptr;
};

class UserInterfaceManager : public GameObject
{
public:
	UserInterfaceManager();
	~UserInterfaceManager();

	// GameObject을(를) 통해 상속됨
	void Update() override;
	void Render() override;

	void Reset();
	void ManageMainScreen();
	void SelectButtonMainScreen();
	
	void Excute();


	void ChangeMoveButtonColor(Player* player);
	void ChangeJumpButtonColor(Player* player);
	void AdjustEnergyBar(Player* player);
	void AdjustScoreImage();
	void AdjustHpBar(Player* player);

	static bool getisMain() { return UserInterfaceManager::isMain; }
	static void setIsMain(bool isMain) { UserInterfaceManager::isMain = isMain; }

	static bool getReseted() { return UserInterfaceManager::reseted; }
	static void setReseted(bool reseted) { UserInterfaceManager::reseted = reseted; }

private:
	void setNumberPieceImage(TextureRect* scorePieceImage, int score);

private:

	UserInterfaces UIImages;
	
	bool isKeyRightTurnedOn = false;
	bool isKeyLeftTurnedOn = false;

	static bool isMain;
	static bool reseted;

	float score = 0;

	char selectionNumber = 0;


};

