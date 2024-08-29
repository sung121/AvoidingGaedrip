#include "stdafx.h"
#include "GaedripScene.h"

#include "BasicObjects/Collider.h"
#include "Gaedrip/CustomizedObjects/Entities/Player.h"
#include "Gaedrip/Managers/GameManager.h"
#include "Gaedrip/CustomizedObjects/Topography/Ground.h"
#include "Gaedrip/CustomizedObjects/Topography/Platform.h"
#include "Gaedrip/CustomizedObjects/DangerObjects/DangerBox.h"
#include "Gaedrip/Backgrounds/Background.h"
#include "Gaedrip/Managers/LevelManager.h"
#include "Gaedrip/Managers/UserInterfaceManager.h"
#include "Gaedrip/Items/HealPack.h"

void GaedripScene::Init()
{

	player = new Player();
	
	GameObject* healPackObj = new GameObject();
	healPack = &healPackObj->AddComponent<HealPack>();
	
	
	GameObject* groundObj = new GameObject();
	ground = &groundObj->AddComponent<Ground>();
	
	GameObject* backgroundObj = new GameObject();
	background = &backgroundObj->AddComponent<Background>();
	
	GameObject* levelManagerObj = new GameObject();
	levelManager = &levelManagerObj->AddComponent<LevelManager>();
	
	dangerBoxs = levelManager->getDangerBoxs();
	
	ground->transform.SetPositionY(-40);

	background->Update();
	player->Update();
	healPack->Update();
	levelManager->Update();
	ground->Update();
	//UserInterfaceManager::Get()->Update();
}

void GaedripScene::Destroy()
{
	SAFE_DELETE(background);
	SAFE_DELETE(levelManager);
	SAFE_DELETE(player);
	SAFE_DELETE(ground);
	SAFE_DELETE(platform);
}

void GaedripScene::PhysicsUpdate()
{
}

void GaedripScene::Update()
{

	if (UserInterfaceManager::Get()->getisMain() == false)
	{
		
		Execute();
		
		background->Update();
		player->Update();
		healPack->Update();
		levelManager->Update();
		ground->Update();
		UserInterfaceManager::Get()->Update();
		return;
	}
	
	//UserInterfaceManager::Get()->ManageMainScreen();
	//UserInterfaceManager::Get()->Update();
	
	// 리셋을 하겠다면
	if (UserInterfaceManager::Get()->getReseted() == true)
	{
		Reset();
		for (int i = 0; i < dangerBoxs.size(); i++)
			dangerBoxs[i]->Update();
		
		background->Update();
		player->Update();
		healPack->Update();
		levelManager->Update();
		ground->Update();
		UserInterfaceManager::Get()->Update();

		UserInterfaceManager::Get()->setReseted(false);
	}

}

void GaedripScene::Render()
{
	background->Render();
	// 메인이 아니라면
	if (UserInterfaceManager::Get()->getisMain() == false)
	{
		background->Render();
		player->Render();
		healPack->Render();
		levelManager->Render();
		ground->Render();
		UserInterfaceManager::Get()->Render();
		return;
	}
	UserInterfaceManager::Get()->Render();
	
}

void GaedripScene::Execute()
{
	player->CheckAndSetRuns();
	player->MoveWidth();
	//UserInterfaceManager::Get()->ChangeMoveButtonColor(player);
	//UserInterfaceManager::Get()->AdjustEnergyBar(player);
	//UserInterfaceManager::Get()->AdjustScoreImage();
	//UserInterfaceManager::Get()->AdjustHpBar(player);
	CheckJump();
	CheckCollideGround();

	player->Jump();

	levelManager->Execute();
}

void GaedripScene::CheckJump()
{
	if ((player->getReachsAtJumpLimit() == false) && (player->getJumps() == true))
	{
		return;
		printf("점프중\n");
	}
	GameManager::ApplyGravityPlayer(player, 165);
}

void GaedripScene::CheckCollideGround()
{
	if (GameManager::CheckCollide(player->getCollider(), ground->getCollider()))
	{

		player->transform.SetPositionY(ground->transform.GetPosition().y + player->transform.GetSize().y / 2 + ground->transform.GetSize().y / 2 - 0.01f);

		player->setReachsAtGround(true);
		player->setJumps(false);
		player->setReachsAtJumpLimit(true);
		player->setApplysGravity(false);
		player->setJumpsTwice(false);
		player->setJumpsFirst(false);
		player->setJumpSpd(player->getStandardJumpSpd());
	}
	else
	{
		player->setApplysGravity(true);
	}
}

void GaedripScene::ChangeRenderState()
{
	if (Keyboard::Get()->Down('O'))
	{
		player->ChangeRenderStates();
	}
}

void GaedripScene::Reset()
{
	player->Reset();
	levelManager->Reset();
	//UserInterfaceManager::Get()->Reset();
	healPack->Reset();
}

void GaedripScene::PostRender()
{
}

void GaedripScene::GUI()
{
	player->GUI();
}


