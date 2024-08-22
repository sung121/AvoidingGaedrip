#include "Framework.h"
#include "HammerLeft.h"

HammerLeft::HammerLeft()
{
	transform.SetSize(Vector3(397 * 2, 133 * 2, 1));
	
	textureRect = new TextureRect(transform, PathGaedrip + L"HamaLeft.png");
	collider = new Collider(transform);
	
	
	transform.AddTransform(textureRect->getTransformPointer());
	transform.AddTransform(collider->getTransformPointer());

}

HammerLeft::~HammerLeft()
{
	SAFE_DELETE(textureRect);
	SAFE_DELETE(collider);

}

void HammerLeft::Update()
{
	textureRect->Update();
	collider->Update();
}

void HammerLeft::Render()
{
	textureRect->Render();
	//collider->Render();
}
