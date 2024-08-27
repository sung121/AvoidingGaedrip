#include "Framework.h"
#include "WreckingBall.h"

<<<<<<< Updated upstream:Gaedrip-중간완성본/Framework/Gaedrip/CustomizedObjects/DangerObjects/WreckingBall/WreckingBall.cpp
=======
#include "BasicObjects/Collider.h"
#include "Geomatries/TextureRect.h"

>>>>>>> Stashed changes:AvoidGame/Framework/Gaedrip/CustomizedObjects/DangerObjects/WreckingBall/WreckingBall.cpp
Wreckingball::Wreckingball()
{
	//transform = Transform(WinCenterPos, { 300, 300, 0 }, 0);
	//textureRect = new TextureRect(transform, PathGaedrip + L"wreckingBall.png");
	collider = new Collider(transform);
	transform.AddTransform(textureRect->getTransformPointer());
	transform.AddTransform(collider->getTransformPointer());
}

Wreckingball::~Wreckingball()
{
	SAFE_DELETE(textureRect);
	SAFE_DELETE(collider);
}

void Wreckingball::Update()
{
	textureRect->Update();
	collider->Update();
}

void Wreckingball::Render()
{
	//collider->Render();
	textureRect->Render();
}