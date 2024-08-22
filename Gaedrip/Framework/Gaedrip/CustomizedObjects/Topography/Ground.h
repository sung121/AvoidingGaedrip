#pragma once
#include "BasicObjects/GameObject.h"
#include "Geomatries/TextureRect.h"
#include "BasicObjects/Collider.h"

class Ground : GameObject
{
public:
	Ground();
	~Ground();

	// GameObject을(를) 통해 상속됨
	void Update() override;
	void Render() override;

	void ChangerRenderState();

	Collider* getCollider() { return collider; }

	StandardTransform& getTransform() const { return transform; }

public:
	StandardTransform& transform = GameObject::transform;

private:

	TextureRect* textureRect = nullptr;
	Collider* collider = nullptr;

};

