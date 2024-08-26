#pragma once
#include "stdafx.h"
#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"
#include "Demos/00_gaedrip/UI.h"

class UserInterface
{
public:
	UserInterface();
	~UserInterface();

	void Update();

	TextureRect* GetKeyRightOff() { return keyRightOff; }
	TextureRect* GetKeyRightOn() { return keyRightOn; }
	TextureRect* GetKeyLeftOff() { return keyLeftOff; }
	TextureRect* GetKeyLeftOn() { return keyRightOn; }
	TextureRect* GetKeyJump() { return keyJump; }

	vector<TextureRect*> GetButtons() { return buttons; }
	
	Rect* GetBlinder() { return blinder; }
	Rect* GetEnergyBar() { return energyBar; }


	vector<Rect*> GetLifeImages() { return lifeImages; }
	
	void SetLifeImages(float lifes);

	void SetScoreImage(TextureRect* scoreImage, int number);
	vector<TextureRect*> GetScoreImages() { return scoreImages; }

	int GetScore() { return score; }
	void SetScore(int score) { this->score = score; }

	void Destroy();

private:


	TextureRect* keyRightOff = nullptr;
	TextureRect* keyRightOn = nullptr;
	TextureRect* keyLeftOff = nullptr;
	TextureRect* keyLeftOn = nullptr;
	TextureRect* keyJump = nullptr;


	vector<Rect*> lifeImages;

	vector<TextureRect*> scoreImages;
	Vector3 scoreStandardPos = { 500, 500, 0 };

	int score = 0;

	vector<TextureRect*> buttons;
	Rect* blinder = nullptr;
	Rect* energyBar = nullptr;



};

