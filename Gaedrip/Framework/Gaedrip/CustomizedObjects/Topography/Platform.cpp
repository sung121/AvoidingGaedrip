#include "Framework.h"
#include "Platform.h"

Platform::Platform()
{
	Vector3 basicSize(222, 35, 0);
	transform.SetPosition({ WinCenterPos.x, WinCenterPos.y + 100, 0 });
	transform.SetSize({basicSize});

	collider = new Collider(transform);
	textureRect = new TextureRect(transform, PathGaedrip + L"PlatformSmall.png");

}

Platform::~Platform()
{
}

void Platform::Update()
{
	textureRect->transform = this->transform;
	collider->transform = this->transform;

	textureRect->Update();
	collider->Update();
}

void Platform::Render()
{
	collider->Render();
	textureRect->Render();
}
