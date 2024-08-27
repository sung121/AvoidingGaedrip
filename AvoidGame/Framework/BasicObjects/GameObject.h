#pragma once

#include "../UnitTest/SceneBase.h"
#include "Components/Rigidbody.h"

class StandardTransform;

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void Update() = 0;
	virtual void Render() = 0;
	
	Transform* getTransformPointer() { return &transform; }

	template <typename T>
	T& AddComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
		T* component = new T(*this);
		components.push_back(component);

		if (typeid(T) == typeid(Rigidbody))
		{
			cout << "Added Rigidbody Component\n";
			currentScene->getRigidbodies().push_back((Rigidbody*)component);
			//currentScene->getRigidbodies() = new vector<Rigidbody>();
		}
		return *component;
	};

public:
	vector<Component*> components;
	StandardTransform transform;

private:
	SceneBase* currentScene;
};

