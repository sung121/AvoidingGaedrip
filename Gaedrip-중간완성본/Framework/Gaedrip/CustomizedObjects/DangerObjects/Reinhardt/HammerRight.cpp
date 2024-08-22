#include "Framework.h"
#include "HammerRight.h"

HammerRight::HammerRight()
{
	transform.SetSize(Vector3(397 * 2, 133 * 2, 1));

	textureRect = new TextureRect(transform, PathGaedrip + L"HamaRight.png");
	collider = new Collider(transform);

	transform.AddTransform(textureRect->getTransformPointer());
	transform.AddTransform(collider->getTransformPointer());

}

HammerRight::~HammerRight()
{
	SAFE_DELETE(textureRect);
	SAFE_DELETE(collider);

}

void HammerRight::Update()
{
	textureRect->Update();
	collider->Update();
}

void HammerRight::Render()
{
	textureRect->Render();
	//collider->Render();
}
