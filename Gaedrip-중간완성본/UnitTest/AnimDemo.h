#pragma once
#include "Geomatries/AnimationRect.h"

class AnimDemo : public IObject
{
public:

	// IObject을(를) 통해 상속됨
	void Init() override;

	void Destroy() override;

	void Update() override;

	void Render() override;

	void PostRender() override;

	void GUI() override;

private:
	AnimationRect* ar = nullptr;



};

