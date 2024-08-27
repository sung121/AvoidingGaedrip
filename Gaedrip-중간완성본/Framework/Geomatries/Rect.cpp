#include "Framework.h"
#include "Rect.h"

#include "BasicObjects/GameObject.h"

Rect::Rect(GameObject& gameObject, Vector3 position, Vector3 size, float rotation) : Component(gameObject), transform(gameObject.transform)
{
	transform = this->gameObject.transform;
	transform.SetPosition(position);
	transform.SetSize(size);
	transform.SetRotation(rotation);

	MakeRect();
}

Rect::Rect(GameObject& gameObject, const Transform& transform) : Component(gameObject)
{
	this->transform = transform;
	MakeRect();
}

Rect::~Rect()
{

	SAFE_DELETE(wb);

	SAFE_DELETE(ps);
	SAFE_DELETE(il);
	SAFE_DELETE(vs);

	SAFE_DELETE(ib);
	SAFE_DELETE(vb);

}

void Rect::MakeRect()
{
	{
		vertices.assign(4, VertexColor());

		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[0].color = color;

		vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].color = color;

		vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].color = color;

		vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);
		vertices[3].color = color;

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
		vs->Create(ShaderPath + L"VertexColor.hlsl", "VS");

	}

	// InputLayout
	{
		il = new InputLayout();
		il->Create(VertexColor::descs, VertexColor::count, vs->GetBlob());
	}

	// PixelShader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"VertexColor.hlsl", "PS");
	}

	//World
	{
		wb = new WorldBuffer;
	}


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

	this->position = this->transform.GetPosition();
	this->size = this->transform.GetSize();
	this->rotation = this->transform.GetRotation();
}

void Rect::Start()
{
}

void Rect::Destroy()
{
}

void Rect::PhysicsUpdate()
{
}

void Rect::OnCollisionEnter()
{
}

void Rect::Update()
{
	if (printCycle < 0.5f)
	{
		printCycle += Time::Delta();
	}
	else
	{
		printCycle = 0;
	}
	UpdateWorld();
}

void Rect::Render()
{

	vb->SetIA();
	ib->SetIA();
	il->SetIA();

	vs->SetShader();
	wb->SetVSBuffer(0);

	ps->SetShader();

	DC->DrawIndexed(ib->GetCount(), 0, 0);
	///////////////////////////////////////////// DC가 뭔진 모르겠지만 아래에 있는 DC코드로 렌더 설정을 좀 조절할 수 있는 듯함.

	DC->RSSetState(rs);

	DC->DrawIndexed(ib->GetCount(), 0, 0);
	DC->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

void Rect::GUI()
{
	ImGui::Begin("Rect");
	{
		ImGui::DragFloat3("Position", position);
		ImGui::DragFloat3("Size", size);


		//ImGui::DragFloat3("Position", position);
		//ImGui::DragFloat3("Size", size);
	}
	ImGui::End();
}

void Rect::GUI(const char* name)
{
	ImGui::Begin(name);
	{
		ImGui::DragFloat3("Position", this->position);
		ImGui::DragFloat3("Size", this->size);
		
		this->transform.SetPosition(this->position);

		if (printCycle >= 0.5f)
		{
			//cout << "GUI() Transform: " << this->transform.GetPosition().x << endl;
		}

		//ImGui::DragFloat3("Position", position);
		//ImGui::DragFloat3("Size", size);
	}
	ImGui::End();
}

void Rect::UpdateColor()
{
	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		for (VertexColor& v : vertices)
		{
			v.color = color;
		}
	}
	memcpy(subResource.pData, vertices.data(), vb->GetCount() * vb->GetStride());
	DC->Unmap(vb->GetResource(), 0);
}

string Rect::MakeLable(string preFix)
{
	return string();
}


void Rect::UpdateWorld()
{
	position = transform.GetPosition();
	size = transform.GetSize();
	rotation = transform.GetRotation();
	// Scaling
	D3DXMatrixScaling(&S, this->transform.GetSize().x, this->transform.GetSize().y, this->transform.GetSize().z);
	//Rotation
	D3DXMatrixRotationZ(&R, this->transform.GetRotation());
	// Translation
	//D3DXMatrixTranslation(&T, this->transform.GetPosition().x, this->transform.GetPosition().y, this->transform.GetPosition().z);
	D3DXMatrixTranslation(&T, transform.GetPosition().x, transform.GetPosition().y, transform.GetPosition().z);

	if (printCycle >= 0.5f)
	{
		//cout << "UpdateWorld() positionX: " << this->transform.GetPosition().x << endl;
	}

	world = S * R * T;
	wb->SetWorld(world);
}

void Rect::SetColor(Color color)
{
	this->color = color;
	UpdateColor();
}

void Rect::SetTransform(Transform& transform)
{
	this->transform = transform;
}

