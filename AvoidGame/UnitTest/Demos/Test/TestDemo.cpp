#include "stdafx.h"
#include "TestDemo.h"

void TestDemo::Init()
{
	collider = new Collider(Transform({500, 500, 0}, {500, 500, 0}, 0));
	rect = new Rect(Transform({ 500, 500, 0 }, { 500, 500, 0 }, 0));
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
