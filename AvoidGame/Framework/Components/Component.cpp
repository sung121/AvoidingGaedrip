#include "Framework.h"
#include "Component.h"
#include "BasicObjects/GameObject.h"

Component::Component(GameObject& gameObject) : gameObject(gameObject), transform(gameObject.transform)
{
}

Component::~Component()
{
}
