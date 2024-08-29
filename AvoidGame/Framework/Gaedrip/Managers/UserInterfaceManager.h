#pragma once
#include "BasicObjects/GameObject.h"

class GameObject;
class TextureRect;
class Player;
class Rect;


struct UserInterfaces
{
	UserInterfaces();
	~UserInterfaces();

	void Reset();

	GameObject* gear = nullptr;
	GameObject* buttonStart = nullptr;
	GameObject* buttonStart2 = nullptr;
	GameObject* buttonSetting = nullptr;
	GameObject* title = nullptr;

	GameObject* keyRightOff = nullptr;
	GameObject* keyRightOn = nullptr;
	GameObject* keyLeftOff = nullptr;
	GameObject* keyLeftOn = nullptr;
	GameObject* keyJump = nullptr;

	vector<GameObject*> lifeImages;
	int lifeCount = 5;

	vector<GameObject*> scoreImages;
	Vector3 scoreStandardPos = { 500, 500, 0 };

	GameObject* lifeTransform = nullptr;
	
	Vector3 lifePosition = lifeTransform->transform.GetPosition();
	Vector3 lifeSize = lifeTransform->transform.GetSize();
	
	GameObject* blinder = nullptr;
	GameObject* energyBar = nullptr;
};

class UserInterfaceManager : public Singleton<UserInterfaceManager>
{
public:
	UserInterfaceManager(GameObject& gameObject);
	~UserInterfaceManager();

	// GameObject을(를) 통해 상속됨
	void Update() override;
	void Render();

	void Reset();
	void ManageMainScreen();
	void SelectButtonMainScreen();
	
	void Execute();


	void ChangeMoveButtonColor(Player* player);
	void ChangeJumpButtonColor(Player* player);
	void AdjustEnergyBar(Player* player);
	void AdjustScoreImage();
	void AdjustHpBar(Player* player);

	bool getisMain() { return isMain; }
	void setIsMain(bool isMain) { isMain = isMain; }

	bool getReseted() { return reseted; }
	void setReseted(bool reseted) { reseted = reseted; }

private:
	void setNumberPieceImage(TextureRect& scorePieceImage, int score);

private:

	UserInterfaces UIImages;
	
	bool isKeyRightTurnedOn = false;
	bool isKeyLeftTurnedOn = false;

	bool isMain;
	bool reseted;

	float score = 0;

	char selectionNumber = 0;



	// Singleton을(를) 통해 상속됨
	void Start() override;

	void Destroy() override;

	void PhysicsUpdate() override;

	void OnCollisionEnter() override;

};

