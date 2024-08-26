#pragma once

class Collider;
class Player;
class GameManager;
class Ground;
class Platform;
class DangerBox;
class Background;
class LevelManager;
class UserInterfaceManager;
class HealPack;


class GaedripDemo : public IObject
{
public:
	void Init() override;
	void Destroy() override;

	void PhysicsUpdate() override;
	void Update() override;
	void Render() override;
	
	void Execute();
	void CheckJump();
	void CheckCollideGround();
	void ChangeRenderState();

	void Reset();
	
	void PostRender() override;
	void GUI() override;


private:
	
	Player* player = nullptr;
	HealPack* healPack = nullptr;
	Ground* ground = nullptr;
	Platform* platform = nullptr;
	Background* background = nullptr;
	LevelManager* levelsManager = nullptr;
	vector<DangerBox*> dangerBoxs;
	UserInterfaceManager* userInterfaceManager = nullptr;

	bool isMainFirst = false;



};

