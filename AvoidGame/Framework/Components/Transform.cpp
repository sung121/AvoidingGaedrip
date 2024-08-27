#include "Framework.h"
#include "Transform.h"

Transform::Transform(GameObject& gameObject) : Component(gameObject)
{
	position = Vector3( WinMaxWidth/ 2 , WinMaxHeight / 2, 0);
	size = Vector3(WinMaxWidth, WinMaxHeight, 0);
	rotation = 0;

}

Transform::Transform(GameObject& gameObject, const Vector3& position, const Vector3& size, float rotation) : Component(gameObject)
{
	this->position = position;
	this->size = size;
	this->rotation = rotation;

}

Transform::~Transform()
{
}

void Transform::Start()
{
}

void Transform::Destroy()
{
}

void Transform::PhysicsUpdate()
{
}

void Transform::OnCollisionEnter()
{
}

void Transform::Update()
{
}
