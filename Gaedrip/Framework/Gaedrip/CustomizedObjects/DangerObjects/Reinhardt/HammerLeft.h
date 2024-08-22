#pragma once
#include "BasicObjects/GameObject.h"
#include "BasicObjects/Collider.h"
#include "Geomatries/TextureRect.h"

class HammerLeft : public GameObject
{
public:
	HammerLeft();
	~HammerLeft();

	// GameObject을(를) 통해 상속됨
	void Update() override;
	void Render() override;

	Collider* getCollider() { return this->collider; }

private:
	TextureRect* textureRect = nullptr;
	Collider* collider = nullptr;

};

