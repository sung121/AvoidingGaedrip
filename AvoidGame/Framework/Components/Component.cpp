#include "Framework.h"
#include "Component.h"
#include "BasicObjects/GameObject.h"

Component::Component(GameObject& gameObject) : gameObject(&gameObject), transform(gameObject.transform)
{
}

Component::~Component()
{
}

GameObject& Component::CreateGameObject()
{
	GameObject* gameObject = new GameObject();
	//GameObject& gameObjectRef = *gameObject;
	childs.push_back(gameObject);
	return *gameObject;
	// TODO: 여기에 return 문을 삽입합니다.
}
