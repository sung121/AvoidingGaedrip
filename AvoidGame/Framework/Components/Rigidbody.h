#pragma once
#include "Component.h"

class Rigidbody : public Component
{
	// Component을(를) 통해 상속됨
	void Start() override;
	void Destroy() override;
	void PhysicsUpdate() override;
	void OnCollisionEnter() override;
	void Update() override;
};

