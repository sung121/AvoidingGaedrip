#pragma once
<<<<<<<< Updated upstream:Gaedrip-ì¤‘ê°„ì™„ì„±ë³¸/Framework/Utilities/Transform.h
#include "Framework.h"
// Å¬·¡½º ¼±¾ð
class Transform
========

#include "Component.h"

class Transform : public Component
>>>>>>>> Stashed changes:AvoidGame/Framework/Components/Transform.h
{
public:
	// ComponentÀ»(¸¦) ÅëÇØ »ó¼ÓµÊ
	void Start() override;

	void Destroy() override;

	void PhysicsUpdate() override;

	void OnCollisionEnter() override;

	void Update() override;

public:
	
	Transform(GameObject& gameObject);
	Transform(GameObject& gameObject, const Vector3& position, const Vector3& size, float rotation);
	~Transform();

	Vector3 GetPosition() const 
	{
		return this->position; 
	}
	Vector3* GetPositionPointer()
	{
		return &(this->position);
	}
	void SetPosition(Vector3 position) { this->position = position; }

	void operator =(const Transform& transform)
	{
		this->position	= transform.GetPosition();
		this->rotation	= transform.GetRotation();
		this->size		= transform.GetSize();
	}


	void SetPositionX(float x) { this->position.x = x; }
	void SetPositionY(float y) { this->position.y = y; }

	Vector3 GetSize() const { return size; }
	void SetSize(Vector3 size) { this->size = size; }

	float GetSizeOfWidth() { return size.x; }
	float GetSizeOfHeight() { return size.y; }


	void ReverseSizeToX() { this->size.x = -this->size.x; }

	float GetRotation() const { return this->rotation; }
	float* GetRotationPointer(){ return &this->rotation; }
	void SetRotation(float rotation) { this->rotation = rotation; }

protected:
	
	Vector3 position;
	Vector3 size;
	float rotation;

};

