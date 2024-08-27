#pragma once
<<<<<<< Updated upstream:Gaedrip-중간완성본/Framework/Geomatries/Rect.h

#include "Framework.h"
#include "Utilities/Transform.h"
=======
>>>>>>> Stashed changes:AvoidGame/Framework/Geomatries/Rect.h

class GameObject;

class Rect : public Component
{
public:
	virtual void Start();
	virtual void Destroy();
	virtual void PhysicsUpdate();
	virtual void OnCollisionEnter();
	virtual void Update();

public:
	Rect(GameObject& gameObject, Vector3 position, Vector3 size, float rotation);
	Rect(GameObject& gameObject,  const Transform& transform);
	~Rect();

	void MakeRect();

	void Render();

	void GUI();
	void GUI(const char* name);

	void UpdateColor(); 
	string MakeLable(string preFix);

	void UpdateWorld();
	void SetColor(Color color);

	void SetTag(char tag) { this->tag = tag; }

	Transform* getTransformPointer() { return &transform; }
	Transform& getTransform() { return transform; }
	
	void SetTransform(Transform& transform);



public:
	Transform& transform;

protected:
	vector<VertexColor> vertices;
	VertexBuffer* vb = nullptr;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	InputLayout* il = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	D3DXMATRIX world;
	D3DXMATRIX S, R, T;

	WorldBuffer* wb = nullptr;


	Vector3 position;
	Vector3 size;
	float rotation;

	Color color = Color(1, 0, 0, 1);

	ID3D11ShaderResourceView* srv = nullptr;
	ID3D11RasterizerState* rs = nullptr;

	D3D11_MAPPED_SUBRESOURCE subResource;

	float printCycle = 0;

	char tag = '\0';

};