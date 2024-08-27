#include "stdafx.h"
#include "TestDemo.h"

#include "Geomatries/Rect.h"
#include "Gaedrip/CustomizedObjects/Entities/Player.h"
#include "Gaedrip/CustomizedObjects/Topography/Ground.h"
#include "Gaedrip/Managers/LevelManager.h"
#include "Gaedrip/CustomizedObjects/DangerObjects/WreckingBall/WreckingBall.h"

void TestDemo::Init()
{
	//collider = new Collider(Transform({500, 500, 0}, {500, 500, 0}, 0));
	//rect = new Rect(Transform({ 500, 500, 0 }, { 500, 500, 0 }, 0));
	player = new Player();
	
	ground = new Ground();
	wreckingball = new Wreckingball();
}

void TestDemo::Destroy()
{
}

void TestDemo::Update()
{
	ground->Update();
	wreckingball->Update();
}

void TestDemo::Render()
{
	ground->Render();
	wreckingball->Render();
}

void TestDemo::PostRender()
{
}

void TestDemo::GUI()
{
}
