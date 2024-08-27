#include "Framework.h"
#include "GameObject.h"

#include "Components/Component.h"
#include "Components/Rigidbody.h"

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
