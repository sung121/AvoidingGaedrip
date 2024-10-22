#include "Framework.h"
#include "WreckingBall.h"

Wreckingball::Wreckingball()
{
	//transform = Transform(WinCenterPos, { 300, 300, 0 }, 0);
	//textureRect = new TextureRect(transform, PathGaedrip + L"wreckingBall.png");
	collider = &AddComponent<Collider>();
	//collider = new Collider(transform);
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