#include "stdafx.h"
#include "Program.h"
#include "Systems/Window.h"
#include "Demos/Test/TestDemo.h"
#include "Demos/Gaedrip/GaedripDemo.h"
#include "SceneBase.h"
#include "Components/Rigidbody.h"

void Program::Init()
{
	States::Create();

	// Create VPBuffer
	{
		vpb = new VPBuffer();

		// View
		{
			D3DXMatrixLookAtLH
			(
				&view,
				&Vector3(0, 0, 0),	// ī�޶� ��ġ
				&Vector3(0, 0, 1),	// ī�޶� �����ִ� ���� (����)
				&Vector3(0, 1, 0)	// ī�޶� ���� ����
			);

			vpb->SetView(view);
		}

		// Projection
		{
			D3DXMatrixOrthoOffCenterLH
			(
				&proj,
				0.0f,					// ����
				(float)WinMaxWidth,		// ������
				0.0f,					// �Ʒ�
				(float)WinMaxHeight,	// ��
				0,						// �Ͼ�	(���� �ּ�)
				1						// ��	(���� �ִ�)
			);

			vpb->SetProjection(proj);
		}
	}

	//Push(new CupheadDemo);

	Push(new SceneBase);
	
	//Push(new TestDemo);
	
	//Push(new AnimDemo);
}

void Program::Destroy()
{
	SAFE_DELETE(vpb);

	for (SceneBase* obj : objs)
	{
		obj->Destroy();
		SAFE_DELETE(obj);
	}
}

void Program::PhysicsUpdate()
{
	for (IObject* obj : objs)
	{
		obj->PhysicsUpdate();
	}
}

void Program::PhysicsUpdate()
{
	for (SceneBase* obj : objs)
	{
		for (size_t i = 0; i < obj->getRigidbodies().size(); i++)
		{
			obj->getRigidbodies()[i].gameObject;
		}
	}
}

void Program::Update()
{
	physicsCycle = 0;
	FXUPdatePerSec = 0;
	frameRate = 0;
	time = 0;

	frameRate += 1;

	physicsCycle += Time::Delta();
	time += Time::Delta();

	while (physicsCycle >= 0.02)
	{
		physicsCycle -= 0.02;
		FXUPdatePerSec++;
		PhysicsUpdate();
	}
	for (IObject* obj : objs)
		obj->Update();
}

void Program::Render()
{
	vpb->SetVSBuffer(1);

	for (IObject* obj : objs)
		obj->Render();
}

void Program::PostRender()
{
	for (SceneBase* obj : objs)
		obj->PostRender();
}

void Program::GUI()
{
	for (SceneBase* obj : objs)
	{
		obj->GUI();
	}
}

void Program::Push(SceneBase* obj)
{
	objs.push_back(obj);
	obj->Init();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	srand((UINT)time(NULL));

	DXDesc desc;
	desc.AppName = L"D2DGame";
	desc.instance = instance;
	desc.handle = NULL;
	desc.width = WinMaxWidth;
	desc.height = WinMaxHeight;

	Program* program = new Program();
	Window* window = new Window(desc);
	WPARAM wParam = window->Run(program);

	SAFE_DELETE(window);
	SAFE_DELETE(program);

	return wParam;

}
