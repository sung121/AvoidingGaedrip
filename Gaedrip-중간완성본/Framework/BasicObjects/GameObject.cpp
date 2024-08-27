#include "Framework.h"
#include "GameObject.h"
<<<<<<< Updated upstream:Gaedrip-중간완성본/Framework/BasicObjects/GameObject.cpp
=======

#include "Components/Component.h"
#include "Components/Rigidbody.h"
>>>>>>> Stashed changes:AvoidGame/Framework/BasicObjects/GameObject.cpp

GameObject::GameObject() : transform(*this)
{
	components.push_back(&transform);
}

GameObject::~GameObject()
{
	for (int i = 0; i < components.size(); i++)
	{
		delete components[i];
	}
}
