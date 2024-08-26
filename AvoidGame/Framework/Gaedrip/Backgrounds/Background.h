#pragma once
#include "BasicObjects/GameObject.h"
#include "Geomatries/Rect.h"

class Background : public GameObject
{
public:
	Background();
	~Background();

	// GameObject을(를) 통해 상속됨
	void Update() override;

	void Render() override;

private:

	Rect* rect = nullptr;

};

