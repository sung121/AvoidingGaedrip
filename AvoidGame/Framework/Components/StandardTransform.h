#pragma once
#include "Transform.h"

class StandardTransform : public Transform
{
public:
	StandardTransform(GameObject& gameObject);
	~StandardTransform();

	void AddTransform(Transform* transform) { transforms.push_back(transform); }

	void operator =(const Transform& transform)
	{
		SetPosition(transform.GetPosition());
		SetRotation(transform.GetRotation());
		SetSize(transform.GetSize());
	}

	void SetPosition(const Vector3& position)
	{  
		vector<Vector3> distances;
		for (UINT i = 0; i < transforms.size(); i++)
		{
			Vector3 diff = transforms[i]->GetPosition() - this->position;
			distances.push_back(diff);
		}

		this->position = position;

		for (UINT i = 0; i < transforms.size(); i++)
		{
			Vector3 pos = position + distances[i];
			transforms[i]->SetPosition(pos);
		}
	}
	void SetPositionX(float posX)
	{
		vector<float> distances;
		for (UINT i = 0; i < transforms.size(); i++)
		{
			float diff = transforms[i]->GetPosition().x - this->position.x;
			distances.push_back(diff);
		}

		this->position.x = posX;

		for (UINT i = 0; i < transforms.size(); i++)
		{
			float X = this->position.x + distances[i];
			transforms[i]->SetPositionX(X);
		}
	}
	void SetPositionY(float posY)
	{
		vector<float> distances;
		for (UINT i = 0; i < transforms.size(); i++)
		{
			float diff = transforms[i]->GetPosition().y - this->position.y;
			distances.push_back(diff);
		}

		this->position.y = posY;

		for (UINT i = 0; i < transforms.size(); i++)
		{
			float Y = this->position.y + distances[i];
			transforms[i]->SetPositionY(Y);
		}
	}

	void SetRotation(float rotation)
	{
		for (UINT i = 0; i < transforms.size(); i++)
		{
			transforms[i]->SetRotation(rotation);
		}
	}

	void SetSize(const Vector3& size)
	{
		for (UINT i = 0; i < transforms.size(); i++)
		{
			transforms[i]->SetSize(size);
		}

	}

protected:
	Vector3& position = Transform::position;
	Vector3& size = Transform::size;
	float& rotation = Transform::rotation;


private:

	vector<Transform*> transforms;

	



};
