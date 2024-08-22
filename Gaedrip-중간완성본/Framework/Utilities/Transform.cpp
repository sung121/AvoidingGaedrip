#include "Framework.h"
#include "Transform.h"

Transform::Transform()
{
	position = Vector3( WinMaxWidth/ 2 , WinMaxHeight / 2, 0);
	size = Vector3(WinMaxWidth, WinMaxHeight, 0);
	rotation = 0;

}

Transform::Transform(const Vector3& position, const Vector3& size, float rotation)
{
	this->position = position;
	this->size = size;
	this->rotation = rotation;

}

Transform::~Transform()
{
}
