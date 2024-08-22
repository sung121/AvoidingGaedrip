#pragma once
#include "Utilities/StandardTransform.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void Update() = 0;
	virtual void Render() = 0;
	
	Transform* getTransformPointer() { return &transform; }

public:

	StandardTransform transform;

};

