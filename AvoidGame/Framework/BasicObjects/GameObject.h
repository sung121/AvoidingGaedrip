#pragma once
<<<<<<< Updated upstream:Gaedrip-중간완성본/Framework/BasicObjects/GameObject.h
#include "Utilities/StandardTransform.h"
=======

#include "../UnitTest/SceneBase.h"

class StandardTransform;
class Rigidbody;
class SceneBase;
>>>>>>> Stashed changes:AvoidGame/Framework/BasicObjects/GameObject.h

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
			currentScene->getRigidbodies().push_back(this);
			currentScene->getRigidbodies() = new vector<Rigidbody>();
		}
		return *component;
	};

public:
	vector<Component*> components;
	StandardTransform transform;

private:
	SceneBase* currentScene;
};

