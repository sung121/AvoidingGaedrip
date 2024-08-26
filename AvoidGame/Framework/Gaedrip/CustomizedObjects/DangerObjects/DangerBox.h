#pragma once
#include "BasicObjects/GameObject.h"

class Collider;
class Rect;
class StandardTransform;

class DangerBox : GameObject
{
public:
	DangerBox();
	~DangerBox();

	// GameObject을(를) 통해 상속됨
	void Update() override;
	void Render() override;

	Collider* getCollider() { return collider; }

	bool getMovesUp() { return movesUp; }
	void setMovesUp(bool movesUp) { this->movesUp = movesUp; }

	bool getMovesDown() { return movesDown; }
	void setMovesDown(bool movesDown) { this->movesDown = movesDown; }

	bool getMovesFirst() { return movesFirst; }
	void setMovesFirst(bool movesFirst) { this->movesFirst = movesFirst; }

public:
	StandardTransform& transform = GameObject::transform;
	
private:

	Rect* rect = nullptr;
	Collider* collider = nullptr;
	
	bool movesUp = false;
	bool movesDown = false;
	bool movesFirst = false;


};

