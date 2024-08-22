#pragma once
#include "BasicObjects/GameObject.h"
#include "Geomatries/TextureRect.h"
#include "BasicObjects/Collider.h"

class Platform : GameObject
{
public:
	Platform();
	~Platform();

	// GameObject을(를) 통해 상속됨
	void Update() override;
	void Render() override;


private:

	Collider* collider = nullptr;
	TextureRect* textureRect = nullptr;


};

