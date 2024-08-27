#include "Framework.h"
#include "Background.h"

Background::Background()
{
	transform.AddTransform(rect->getTransformPointer());
	AddComponent<Rect>();
	//rect = new Rect(transform);
	rect->SetColor(Color(0, 0, 0, 0));

}

Background::~Background()
{
}

void Background::Update()
{
	rect->Update();
}

void Background::Render()
{
	rect->Render();
}
