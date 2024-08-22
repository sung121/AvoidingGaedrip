#include "stdafx.h"
#include "HealPack.h"

HealPack::HealPack()
{
	healPack = new TextureRect(Vector3(500, 500, 0),
		Vector3(100, 100, 1), 0.0f, TexturePath + L"healPack.png");

}

HealPack::~HealPack()
{
}

void HealPack::Destroy()
{
	SAFE_DELETE(healPack);
}
