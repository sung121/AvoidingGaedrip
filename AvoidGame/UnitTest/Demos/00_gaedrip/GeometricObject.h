#pragma once
#include "../Framework/Framework.h"
#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"

class GeometricObject
{
public:
	GeometricObject();
	~GeometricObject();

	void Update();

	vector<TextureRect*> GetGeometricBoxs() { return geometricBoxs; }
	TextureRect* GetPlatformBig() { return platformBig; }
	TextureRect* GetPlatformSmall() { return platformSmall; }
	vector<Rect*> GetDangerBoxs() { return dangerBoxs; }

	void Destroy();


private:
	vector<Rect*> dangerBoxs;
	int dangerBoxsCount = 28;

	vector<TextureRect*> geometricBoxs;
	TextureRect* platformBig = nullptr;
	TextureRect* platformSmall = nullptr;

	vector<Rect*> invisibleCollisionBox;
	int collisionBoxCount = 10;


};

