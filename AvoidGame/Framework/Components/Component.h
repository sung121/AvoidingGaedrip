#pragma once

class GameObject;
class Transform;

class Component
{
public:
	Component(GameObject& gameObject);
	~Component();

public:
	virtual void Start()			= 0;
	virtual void Destroy()			= 0;
	virtual void PhysicsUpdate()	= 0;
	virtual void OnCollisionEnter() = 0;
	virtual void Update()			= 0;

public:
	GameObject& GetGameObject() { return gameObject; }

public:
	GameObject& gameObject;
	Transform& transform;

};

