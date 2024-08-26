#include "Framework.h"
#include "HealPack.h"

HealPack::HealPack()
{
	Vector3 pos = { 2000, 2000, 0 };

	transform = Transform(pos, { 100, 100, 0 }, 0);

	textureRect = new TextureRect(pos, Vector3(100, 100, 1), 0.0f, PathGaedrip + L"healPack.png");
	collider = new Collider(pos, Vector3(100, 100, 1), 0.0f);
	

	transform.AddTransform(textureRect->getTransformPointer());
	transform.AddTransform(collider->getTransformPointer());


}

HealPack::~HealPack()
{
}

void HealPack::Update()
{
	textureRect->Update();
	collider->Update();
}

void HealPack::Render()
{
	textureRect->Render();
	//collider->Render();
}

void HealPack::Reset()
{
	Vector3 pos = { 2000, 2000, 0 };

	transform = Transform(pos, { 100, 100, 0 }, 0);
}
