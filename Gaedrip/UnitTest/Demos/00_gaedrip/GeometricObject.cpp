#include "stdafx.h"
#include "GeometricObject.h"

GeometricObject::GeometricObject()
{

	platformBig = new TextureRect(Vector3(637, 5, 0),
		Vector3(1400, 217, 1), 0.00f, TexturePath + L"PlatformBig.png");

	platformSmall = new TextureRect(Vector3(-200, 300, 0),
		Vector3(360 * 0.8, 55 * 0.8, 1), 0.00f, TexturePath + L"PlatformSmall.png");

	geometricBoxs.push_back(platformBig);
	geometricBoxs.push_back(platformSmall);

	geometricBoxs.push_back(new TextureRect(Vector3(600, 700, 0),
		Vector3(360 * 0.8, 55 * 0.8, 1), 0.00f, TexturePath + L"PlatformSmall.png"));
	geometricBoxs.push_back(new TextureRect(Vector3(1400, 300, 0),
		Vector3(360 * 0.8, 55 * 0.8, 1), 0.00f, TexturePath + L"PlatformSmall.png"));
	for (int i = 0; i < dangerBoxsCount; i++)
	{
		dangerBoxs.push_back(new Rect(Vector3(2000, 500, 0), Vector3(50, 200, 1), 0.0f));
	}
}

GeometricObject::~GeometricObject()
{
}

void GeometricObject::Update()
{
	for (TextureRect* tr : geometricBoxs)
	{
		tr->Update();
	}
	for (int i = 0; i < dangerBoxs.size(); i++)
	{
		dangerBoxs[i]->Update();
	}

}

void GeometricObject::Destroy()
{
	for (int i = 0; i < dangerBoxs.size(); i++)
		SAFE_DELETE(dangerBoxs[i]);
	for (int i = 0; i < geometricBoxs.size(); i++)
		SAFE_DELETE(geometricBoxs[i]);

	for (int i = 0; i < invisibleCollisionBox.size(); i++)
		SAFE_DELETE(invisibleCollisionBox[i]);

}
