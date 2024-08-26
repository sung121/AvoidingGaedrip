#include "Framework.h"
#include "StandardTransform.h"

StandardTransform::StandardTransform()
{
	transforms.push_back(this);
}

StandardTransform::~StandardTransform()
{
}
