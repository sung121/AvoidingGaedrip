#include "stdafx.h"
#include "AnimDemo.h"

void AnimDemo::Init()
{
	//ar = new AnimationRect(Transform());

	Sounds::Get()->AddSound("BGM",
		SoundPath + L"bgm.wav");
	Sounds::Get()->Play("BGM");

	Sounds::Get()->AddSound("Move",
		SoundPath + L"Shot.wav");
}

void AnimDemo::Destroy()
{
	//SAFE_DELETE(ar);
}

void AnimDemo::Update()
{
	//ar->Update();

	if (Mouse::Get()->Down(0x000000))
	{
		Sounds::Get()->Play("Move", 1000);
	}
}

void AnimDemo::Render()
{
	//ar ->Render();
}

void AnimDemo::PostRender()
{
}

void AnimDemo::GUI()
{
	//ar->GUI();
}
