#pragma once

#include "../Framework/Framework.h"
#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"

class HealPack
{
public:
	HealPack();
	~HealPack();

	TextureRect* GetHealPack() { return healPack; }

	void Destroy();

	


	
private:
	TextureRect* healPack;
	
};

