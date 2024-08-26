#pragma once

class Transform
{
public:
	
	Transform();
	Transform(const Vector3& position, const Vector3& size, float rotation);
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

