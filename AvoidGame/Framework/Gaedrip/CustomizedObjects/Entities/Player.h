#pragma once
#include "BasicObjects/GameObject.h"

class Collider;
class Rect;

class Player : public GameObject
{
public:
	Player();
	~Player();

	// GameObject을(를) 통해 상속됨
	void Update() override;
	void Render() override;
	
	void GUI();

	void Reset();

	void MoveWidth();
	void CheckAndSetRuns();
	void Jump();

	void ChangeRenderStates();

	bool getApplysGravity() { return applysGravity; }
	void setApplysGravity(bool applysGravity) { this->applysGravity = applysGravity; }

	Collider* getCollider() { return collider; }

	bool getJumps() { return jumps; }
	void setJumps(bool jumps) { this->jumps = jumps; this->jumpTime = 0; }

	void setReachsAtGround(bool reachsAtGround) { this->reachsAtGround = reachsAtGround; }
	bool getReachsAtGround() { return reachsAtGround; }

	bool getReachsAtJumpLimit() { return reachsAtJumpLimit; }
	void setReachsAtJumpLimit(bool reachsAtLimit) { this->reachsAtGround = reachsAtLimit; }

	bool getJumpsTwice() { return jumpsTwice; }
	void setJumpsTwice(bool jumpsTwice) { this->jumpsTwice = jumpsTwice; }

	bool getJumpsFisrt() { return jumpsFirst; }
	void setJumpsFirst(bool jumpsFirst) { this->jumpsFirst = jumpsFirst; }

	float getJumpSpd() { return jumpSpd; }
	void setJumpSpd(float jumpsSpd) { this->jumpSpd = jumpsSpd; }

	float getStandardJumpSpd() { return standardJumpSpd; }

	float GetEnergy() { return energy; }
	void SetEnergy(float energy) { this->energy = energy; }

	float getHp() { return this->hp; }
	void setHp(int hp) { this->hp = hp; }

	float getMaxHp() { return this->maxHp; }
	void setMaxHp( int maxHp ) { this->hp = maxHp; }

	bool getIsImmortal() { return this->isImmortal; }
	void setIsImmortal(bool isImmortal) { this->isImmortal = isImmortal; }

	bool getImmortalTime() { return this->immortalTime; }
	void setImmortalTime(float immortalTime) { this->immortalTime = immortalTime; }

	void setColor(const Color& color) { rect->SetColor(color); }

	void AdjustImmortal();


private:

	Collider* collider = nullptr;
	Rect* rect = nullptr;
	

	bool rendersColliderWireFrame = false;

	int hp = 2;
	int maxHp = 2;

	bool isImmortal = false;
	float immortalTime = 0;

	bool jumps = false;
	bool jumpsTwice = false;
	bool jumpsFirst = false;
	bool moves = false;

	float energy = 1.5f;
	float standardEnergy = 1.5f;

	bool isExhausted = false;

	bool dashs = false;
	bool dashsFirst = false;

	bool reachsAtJumpLimit = true;
	bool reachsAtGround = true;

	bool applysGravity = true;

	float jumpSpd;
	float standardJumpSpd = 1400;
	
	float moveSpd = 450;
	float standardMoveSpd = 450;

	float jumpTime = 0;
	float standardJumpTime = 0.25;

	bool moveL = false;
	bool moveR = false;

	bool moveU = false;

};

