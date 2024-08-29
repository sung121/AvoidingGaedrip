#include "Framework.h"
#include "TextureRect.h"

#include "BasicObjects/GameObject.h"

TextureRect::TextureRect(GameObject& gameObject, Vector3 position, Vector3 size, float rotation, wstring path) : Component(gameObject)
{
	this->path = path;
	
	transform.SetPosition(position);
	transform.SetSize(size);
	transform.SetRotation(rotation);
	MakeTextureRect();

}

TextureRect::TextureRect(GameObject& gameObject, const Transform& transform, wstring path) : Component(gameObject)
{
	this->path = path;

	this->transform = transform;
	
	MakeTextureRect();
}

TextureRect::TextureRect(GameObject& gameObject) : Component(gameObject)
{
	MakeTextureRect();
}


TextureRect::~TextureRect()
{
	SAFE_RELEASE(srv);
	SAFE_RELEASE(rs);

	SAFE_DELETE(wb);

	SAFE_DELETE(ps);
	SAFE_DELETE(il);
	SAFE_DELETE(vs);

	SAFE_DELETE(ib);
	SAFE_DELETE(vb);



}

void TextureRect::MakeTextureRect()
{
	{
		vertices.assign(4, VertexTexture());

		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[0].uv = Vector2(0, 1);
		verticesPosition[0] = vertices[0].position;

		vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].uv = Vector2(1, 0);
		verticesPosition[1] = vertices[1].position;

		vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].uv = Vector2(1, 1);
		verticesPosition[2] = vertices[2].position;

		vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);
		vertices[3].uv = Vector2(0, 0);
		verticesPosition[3] = vertices[3].position;

	}


	{
		vb = new VertexBuffer();
		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
	}

	// IndexBuffer
	{
		indices = { 0, 1, 2, 0, 3, 1 };

		ib = new IndexBuffer();
		ib->Create(indices, D3D11_USAGE_IMMUTABLE);
	}

	//VertexShader
	{
		vs = new VertexShader();
		vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");

	}

	// InputLayout
	{
		il = new InputLayout();
		il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());

	}

	// PixelShader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");
	}

	//World
	{
		wb = new WorldBuffer;
	}

	//Rasterizer State
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));

		// CullMode : 그리지 않을 면 선택 (CULL_BACK = 뒷면을 그리지 않음)
		desc.CullMode = D3D11_CULL_BACK;
		// FillMode : 채우기 방식 선택 (SOLID는 가득 채우기)
		desc.FillMode = D3D11_FILL_SOLID;
		// 반시계 그리기 설정(false는 시계방향으로 고정한다)
		desc.FrontCounterClockwise = false;

		HRESULT hr = DEVICE->CreateRasterizerState(&desc, &rs);
		CHECK(hr);
	}



	//SRV
	{
		HRESULT hr = D3DX11CreateShaderResourceViewFromFile

		(DEVICE,
			path.c_str(),
			nullptr,
			nullptr,
			&srv,
			nullptr
		);
		CHECK(hr);
	}
}

void TextureRect::SetShader(wstring shaderPath)
{
	vs->Clear();
	ps->Clear();

	vs->Create(shaderPath, "VS");
	ps->Create(shaderPath, "PS");

}

void TextureRect::SetPath(wstring path)
{
	SAFE_RELEASE(srv);
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile
	(DEVICE,
		path.c_str(),
		nullptr,
		nullptr,
		&srv,
		nullptr
	);
	CHECK(hr);
}

void TextureRect::Update()
{
	UpdateWorld();
}

void TextureRect::Render()
{
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();
	wb->SetVSBuffer(0);

	ps->SetShader();

	DC->PSSetShaderResources(0, 1, &srv);
	DC->RSSetState(rs);

	DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void TextureRect::GUI()
{
	ImGui::Begin("TextureRect");
	{
		ImGui::DragFloat2("Position", position);
		ImGui::DragFloat2("Size", size);
		ImGui::DragFloat("Rotation", &rotation);
	}
	ImGui::End();

}

void TextureRect::GUI(const char* name)
{
	ImGui::Begin(name);
	{
		ImGui::DragFloat2("Position", position);
		ImGui::DragFloat2("Size", size);
		ImGui::DragFloat("Rotation", &rotation);
	}
	ImGui::End();
}

void TextureRect::PostRender()
{
}

void TextureRect::Start()
{
}

void TextureRect::Destroy()
{
}

void TextureRect::PhysicsUpdate()
{
}

void TextureRect::OnCollisionEnter()
{
}

void TextureRect::UpdateWorld()
{
	position = transform.GetPosition();
	size = transform.GetSize();
	rotation = transform.GetRotation();

	D3DXMatrixScaling(&S, this->transform.GetSize().x, this->transform.GetSize().y, this->transform.GetSize().z);
	//Rotation
	D3DXMatrixRotationZ(&R, this->transform.GetRotation());
	// Translation
	//D3DXMatrixTranslation(&T, this->transform.GetPosition().x, this->transform.GetPosition().y, this->transform.GetPosition().z);
	D3DXMatrixTranslation(&T, transform.GetPosition().x, transform.GetPosition().y, transform.GetPosition().z);

	world = S * R * T;
	wb->SetWorld(world);
}

void TextureRect::MapVertexBuffer()
{
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);

}

void TextureRect::UnmapVertexBuffer()
{
	memcpy(subResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());

	DC->Unmap(vb->GetResource(), 0);
}

