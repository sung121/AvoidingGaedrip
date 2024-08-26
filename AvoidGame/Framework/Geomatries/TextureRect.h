#pragma once
#include "Utilities/Transform.h"

class TextureRect
{
public:
	TextureRect(Vector3 position, Vector3 size, float rotation, wstring path);
	TextureRect(const Transform& transform, wstring path);

	~TextureRect();
	void MakeTextureRect();

	void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }
	void SetShader(wstring shaderPath);

	void SetPath(wstring path);

	void Update();
	void UpdateWorld();

	void MapVertexBuffer();
	void UnmapVertexBuffer();


	void Render();
	void GUI();
	void GUI(const char* name);

	Transform* getTransformPointer() { return &transform; }
	Transform& getTransform() { return transform; }

public:
	Transform transform;

protected:

	vector<VertexTexture> vertices;
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

	wstring path;

	ID3D11ShaderResourceView* srv = nullptr;
	ID3D11RasterizerState* rs = nullptr;


	Vector3 verticesPosition[4];

	D3D11_MAPPED_SUBRESOURCE subResource;


};