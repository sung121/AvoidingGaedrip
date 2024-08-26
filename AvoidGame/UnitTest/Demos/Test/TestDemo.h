#pragma once
class Rect;
class Player;
class Ground;
class LevelManager;
class Wreckingball;

class TestDemo : public IObject
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

	Rect* rect = nullptr;
	Collider* collider = nullptr;

	Player* player = nullptr;
	
	Wreckingball* wreckingball = nullptr;

	Ground* ground = nullptr;

	bool rendersWireFrame = false;

};

