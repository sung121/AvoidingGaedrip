#pragma once
#include "Geomatries/Rect.h"

class Transform;
class GameObject;

class Collider : public Rect
{
public:
	//Collider(GameObject& gameObject, Vector3 position, Vector3 size, float rotation);
	//Collider(GameObject& gameObject, const Transform& transform);
	Collider(GameObject& gameObject);

	~Collider();

	void MakeCollider();

	void Update();
	void Render();

	void ChangeRenders(bool renders) { this->renders = renders; }

	BoundingBox* GetCollider() { return collider; }

private:

	RectEdge* edge = nullptr;
	BoundingBox* collider;

	bool renders = true;

	Vector3 verticesPosition[4];

};

