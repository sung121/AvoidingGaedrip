#include "Framework.h"
#include "Background.h"

Background::Background(GameObject& gameObject) : Component(gameObject)
{
	//transform.AddTransform(rect->getTransformPointer());
	gameObject.AddComponent<Rect>();
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
