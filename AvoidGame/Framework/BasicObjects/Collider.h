#pragma once
#include "Geomatries/Rect.h"
#include "Utilities/Transform.h"

class Collider : public Rect
{
public:
	Collider(Vector3 position, Vector3 size, float rotation);
	Collider(const Transform& transform);
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

