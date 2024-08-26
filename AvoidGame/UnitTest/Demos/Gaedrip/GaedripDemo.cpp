#include "stdafx.h"
#include "GaedripDemo.h"

void GaedripDemo::Init()
{

	player = new Player();
	healPack = new HealPack();
	ground = new Ground();
	background = new Background();
	levelsManager = new LevelsManager(ground, player, healPack);
	dangerBoxs = levelsManager->getDangerBoxs();
	userInterfaceManager = new UserInterfaceManager();
	
	ground->transform.SetPositionY(-40);

	background->Update();
	player->Update();
	healPack->Update();
	levelsManager->Update();
	ground->Update();
	userInterfaceManager->Update();
}

void GaedripDemo::Destroy()
{
	SAFE_DELETE(background);
	SAFE_DELETE(levelsManager);
	SAFE_DELETE(player);
	SAFE_DELETE(ground);
	SAFE_DELETE(platform);
}

void GaedripDemo::Update()
{
	// 메인화면이 아니라면

	if (UserInterfaceManager::getisMain() == false)
	{
		
		Excute();
		
		background->Update();
		player->Update();
		healPack->Update();
		levelsManager->Update();
		ground->Update();
		userInterfaceManager->Update();
		return;
	}
	
	userInterfaceManager->ManageMainScreen();
	userInterfaceManager->Update();
	
	// 리셋을 하겠다면
	if (UserInterfaceManager::getReseted() == true)
	{
		Reset();
		for (int i = 0; i < dangerBoxs.size(); i++)
			dangerBoxs[i]->Update();
		
		background->Update();
		player->Update();
		healPack->Update();
		levelsManager->Update();
		ground->Update();
		userInterfaceManager->Update();

		UserInterfaceManager::setReseted(false);
	}

}

void GaedripDemo::Render()
{
	background->Render();
	// 메인이 아니라면
	if (UserInterfaceManager::getisMain() == false)
	{
		background->Render();
		player->Render();
		healPack->Render();
		levelsManager->Render();
		ground->Render();
		userInterfaceManager->Render();
		return;
	}
	userInterfaceManager->Render();
	
}

void GaedripDemo::Excute()
{
	player->CheckAndSetRuns();
	player->MoveWidth();
	userInterfaceManager->ChangeMoveButtonColor(player);
	userInterfaceManager->AdjustEnergyBar(player);
	userInterfaceManager->AdjustScoreImage();
	userInterfaceManager->AdjustHpBar(player);
	CheckJump();
	CheckCollideGround();

	player->Jump();

	levelsManager->Excute();
}

void GaedripDemo::CheckJump()
{
	if ((player->getReachsAtJumpLimit() == false) && (player->getJumps() == true))
	{
		return;
		printf("점프중\n");
	}
	GameManager::ApplyGravityPlayer(player, 165);
}

void GaedripDemo::CheckCollideGround()
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

void GaedripDemo::ChangeRenderState()
{
	if (Keyboard::Get()->Down('O'))
	{
		player->ChangeRenderStates();
	}
}

void GaedripDemo::Reset()
{
	player->Reset();
	levelsManager->Reset();
	userInterfaceManager->Reset();
	healPack->Reset();
}

void GaedripDemo::PostRender()
{
}

void GaedripDemo::GUI()
{
	player->GUI();
}

