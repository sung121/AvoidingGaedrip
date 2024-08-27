#include "stdafx.h"
#include "Program.h"

#include "Systems/Window.h"

#include "Demos/Test/TestDemo.h"
#include "Demos/Gaedrip/GaedripDemo.h"
<<<<<<< Updated upstream:Gaedrip-ì¤‘ê°„ì™„ì„±ë³¸/UnitTest/Program.cpp
#include "AnimDemo.h"



=======
#include "SceneBase.h"
#include "Components/Rigidbody.h"
>>>>>>> Stashed changes:AvoidGame/UnitTest/Program.cpp

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
				&Vector3(0, 0, 0),	// Ä«¸Þ¶ó À§Ä¡
				&Vector3(0, 0, 1),	// Ä«¸Þ¶ó°¡ º¸°íÀÖ´Â ¹æÇâ (Àü¹æ)
				&Vector3(0, 1, 0)	// Ä«¸Þ¶ó À§ÂÊ ¹æÇâ
			);

			vpb->SetView(view);
		}

		// Projection
		{
			D3DXMatrixOrthoOffCenterLH
			(
				&proj,
				0.0f,					// ¿ÞÂÊ
				(float)WinMaxWidth,		// ¿À¸¥ÂÊ
				0.0f,					// ¾Æ·¡
				(float)WinMaxHeight,	// À§
				0,						// ´Ï¾î	(±íÀÌ ÃÖ¼Ò)
				1						// ÆÄ	(±íÀÌ ÃÖ´ë)
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

<<<<<<< Updated upstream:Gaedrip-ì¤‘ê°„ì™„ì„±ë³¸/UnitTest/Program.cpp
=======
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

>>>>>>> Stashed changes:AvoidGame/UnitTest/Program.cpp
void Program::Update()
{
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
