#pragma once

class GameManager;
class DangerBox;
class Player;
class Reinhardt;
class HammerLeft;
class HammerRight;
class Wreckingball;
class Ground;
class HealPack;
class UserInterfaceManager;

class Rect;

class LevelManager : public Component
{
public:
	//LevelManager(Ground* ground, Player* player, HealPack* healPack);
	LevelManager(GameObject& gameObject);
	~LevelManager();

	void Update();

	void Reset();

	void Execute();

	void ChangeLevel();

	vector<DangerBox*>& getDangerBoxs() { return this->dangerBoxs; }


private:

	void ExcuteReinhardt();
	void ExcuteWreckingBall();
	void ExcuteSigma();
	void ExcuteCassidy();

private:

	Ground* ground = nullptr;
	Player* player = nullptr;

	float progressTime = 0;
	
	float standardRestTime = 2;
	float restTime = 0;
	float hasRested = false;

	enum ProgressLevel
	{
		Nothing = 0,
		LevelReinhardt,
		LevelWreckingBall,
		LevelSigma,
		LevelCassidy
	};

	ProgressLevel currentLevel = Nothing;

	vector<DangerBox*> dangerBoxs;

	HammerLeft* hammerLeft = nullptr;
	HammerRight* hammerRight = nullptr;
	Reinhardt* reinhardt = nullptr;
	Wreckingball* wreckingball = nullptr;

	TextureRect* skull = nullptr;
	TextureRect* circle = nullptr;
	Rect* wall = nullptr;


	HealPack* healPack = nullptr;;

	float raiseSpdSigma = 1;
	float dropSpd = 0.5;
	bool hasCreatedHealPack = false;
	bool hasStartedSigma = false;
	bool movesRightSigma = false;
	bool movesLeftSigma = false;

	bool hasStartedCassidy = false;
	
	bool zoomedOut = false;
	bool Attacked = false;

	int EQSize = 28;
	bool isFinished = false;
	random_device randDevice;

	float postmpX;
	float postmpY;

};

