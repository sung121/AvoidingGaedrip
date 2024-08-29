#pragma once

#include "../UnitTest/SceneBase.h"
#include "Components/Rigidbody.h"

class StandardTransform;

class GameObject
{
public:
	GameObject(SceneBase* currentScene);
	GameObject();
	~GameObject();

	virtual void Update();
	virtual void Render();
	
	template <typename T>
	T& AddComponent()
	{
		//static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
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

	template <typename T>
	T& GetComponent()
	{
		
		for (int i = 0; i < components.size(); i++)
		{
			if (typeid(T) == typeid(components[i]))
			{
				T& component = *((T*)components[i]);
				return component;
			}
		}
	}

public:
	vector<Component*> components;
	StandardTransform transform;
	//vector<std::reference_wrapper<TextureRect>> scoreImages;

private:
	SceneBase* currentScene;
};

