#include "Framework.h"
#include "DangerBox.h"

#include "BasicObjects/Collider.h"

DangerBox::DangerBox()
{
	transform.SetSize({ 70, 150, 0 });
	transform.SetPosition({2000, 2000, 0});
	rect = &AddComponent<Rect>();
	//rect = new Rect(transform);
	//collider = new Collider(transform);
	collider = &AddComponent<Collider>();

	transform.AddTransform(rect->getTransformPointer());
	transform.AddTransform(collider->getTransformPointer());

	rect->SetColor(Color(100, 0, 0, 0));
}

DangerBox::~DangerBox()
{
}

void DangerBox::Update()
{
	rect->Update();
	collider->Update();
}

void DangerBox::Render()
{
	rect->Render();
}
