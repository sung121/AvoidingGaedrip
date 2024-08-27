#include "Framework.h"
#include "Reinhardt.h"

Reinhardt::Reinhardt()
{
	collider = new Collider(transform);
	//textureRect = new TextureRect(transform, PathGaedrip + L"reinhardt.png");

	transform.AddTransform(collider->getTransformPointer());
	transform.AddTransform(textureRect->getTransformPointer());

}

Reinhardt::~Reinhardt()
{
	SAFE_DELETE(textureRect);
	SAFE_DELETE(collider);

}

void Reinhardt::Update()
{
	textureRect->Update();
	collider->Update();
}

void Reinhardt::Render()
{
	textureRect->Render();
	//collider->Render();
}
