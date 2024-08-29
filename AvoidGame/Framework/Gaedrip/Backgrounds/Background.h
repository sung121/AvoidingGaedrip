#pragma once
#include "BasicObjects/GameObject.h"
#include "Geomatries/Rect.h"

class Background : public Component
{
public:
	Background(GameObject& gameObject);
	~Background();

	// GameObject을(를) 통해 상속됨
	void Update() override;

private:

	Rect* rect = nullptr;

};

