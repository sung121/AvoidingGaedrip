#pragma once

#include "../Framework/Framework.h"
#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"

class LevelObject
{
public:



	virtual void ExcutePattern() = 0;
	virtual void Collide() = 0;
	virtual bool GetIsFinished() = 0;




private:




};

