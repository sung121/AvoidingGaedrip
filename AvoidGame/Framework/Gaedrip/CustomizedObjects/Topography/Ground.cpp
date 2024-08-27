#include "Framework.h"
#include "Ground.h"

Ground::Ground()
{
	transform.SetSize(Vector3( 1094, 217 * 0.75f, 0 ) * 2);
	AddComponent<TextureRect>();
	//textureRect = new TextureRect(transform, PathGaedrip + L"PlatformBig.png");
	collider = new Collider(transform);
	
	transform.AddTransform(textureRect->getTransformPointer());
	transform.AddTransform(collider->getTransformPointer());

	collider->transform = this->transform;
	textureRect->transform = this->transform;

}

Ground::~Ground()
{
}

void Ground::Update()
{
	//cout << textureRect->transform.GetPosition().y << endl;


	collider->Update();
	textureRect->Update();
}

void Ground::Render()
{
	//collider->Render();
	textureRect->Render();
}

void Ground::ChangerRenderState()
{

}
