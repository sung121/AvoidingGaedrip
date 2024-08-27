#include "Framework.h"
#include "StandardTransform.h"

StandardTransform::StandardTransform(GameObject& gameObject) : Transform(gameObject)
{
	transforms.push_back(this);
}

StandardTransform::~StandardTransform()
{
}
