#pragma once
#include "BasicObjects/Collider.h"
#include "Gaedrip/CustomizedObjects/Entities/Player.h"
#include "Gaedrip/Managers/GameManager.h"
#include "Gaedrip/CustomizedObjects/Topography/Ground.h"
#include "Gaedrip/CustomizedObjects/Topography/Platform.h"
#include "Gaedrip/CustomizedObjects/DangerObjects/DangerBox.h"
#include "Gaedrip/Backgrounds/Background.h"
#include "Gaedrip/Managers/LevelsManager.h"
#include "Gaedrip/Managers/UserInterfaceManager.h"
#include "Gaedrip/Items/HealPack.h"

class GaedripDemo : public IObject
{
public:
	// IObject을(를) 통해 상속됨
	void Init() override;
	void Destroy() override;
	
	void Update() override;
	void Render() override;
	
	void Excute();
	void CheckJump();
	void CheckCollideGround();
	void ChangeRenderState();

	void Reset();
	
	void PostRender() override;
	void GUI() override;


private:
	
	Player* player = nullptr;
	HealPack* healPack = nullptr;
	Ground* ground = nullptr;
	Platform* platform = nullptr;
	Background* background = nullptr;
	LevelsManager* levelsManager = nullptr;
	vector<DangerBox*> dangerBoxs;
	UserInterfaceManager* userInterfaceManager = nullptr;

	bool isMainFirst = false;

};

