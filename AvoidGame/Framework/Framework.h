#pragma once

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

//�̸� �����ϵ� ���.
//pch pre compiled header

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <map>
#include <unordered_map>
#include <assert.h>
#include <random>
#include <functional>
#include "cmath"

using namespace std;

//DirectX
#include "../_Libraries/DirectXTex/DirectXTex.h"
#pragma comment(lib, "DirectXTex/DirectXTex.lib")

#include <d3dcompiler.h>
#include <d3d11.h>
#include "../_Libraries/DirectX/Include/D3DX10math.h"
#include "../_Libraries/DirectX/Include/D3DX11async.h"


#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dcompiler.lib")

//////////////////////////////////////////
//ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#pragma comment(lib, "ImGui/ImGui.lib")

//////////////////////////////////////////
// FMOD
#include "FMOD/inc/fmod.hpp"
#ifdef _WIN64

#pragma comment(lib, "FMOD/lib/x64/fmod_vc.lib")
#else
#pragma comment(lib, "FMOD/lib/x86/fmod_vc.lib")
#endif 

#include "Interfaces/IObject.h"

#include "Utilities/SingletonBase.h"

#include "Systems/Graphics.h"
#include "Systems/Keyboard.h"
#include "Systems/Mouse.h"
#include "Systems/Time.h"
#include "Systems/Sound.h"

#include "Utilities/Gui.h"

typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR2 Vector2;
typedef D3DXMATRIX  Matrix;
typedef D3DXCOLOR   Color;
typedef UINT		uint;

#define DEVICE Graphics::Get()->GetDevice()
#define DC     Graphics::Get()->GetDC()

#define CHECK(p) assert(SUCCEEDED(p))

#define SAFE_DELETE(p)		 { if(p) { delete(p);	   (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[](p);	   (p) = nullptr; } }
#define SAFE_RELEASE(p)		 { if(p) { (p)->Release(); (p) = nullptr; } }

#include "Renders/Resources/VertexType.h"
#include "Renders/Resources/ShaderBuffer.h"
#include "Renders/Resources/GlobalBuffer.h"
#include "Renders/Resources/Texture2D.h"

#include "Renders/IA/VertexBuffer.h"
#include "Renders/IA/IndexBuffer.h"
#include "Renders/IA/InputLayout.h"
#include "Renders/States.h"

#include "Renders/Shaders/VertexShader.h"
#include "Renders/Shaders/PixelShader.h"

#include "Utilities/DirectHelper.h"
#include "Utilities/BoundingBox.h"
#include "Utilities/String.h"
#include "Utilities/Path.h"
<<<<<<< Updated upstream:Gaedrip-중간완성본/Framework/Framework.h
=======

/////////////////////////////////////////////////////

#include "Components/StandardTransform.h"

#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"
#include "Geomatries/AnimationRect.h"
>>>>>>> Stashed changes:AvoidGame/Framework/Framework.h

#include "BasicObjects/Collider.h"





#define WinMaxWidth 1280
#define WinMaxHeight 720

const Vector3 WinCenterPos = Vector3({WinMaxWidth / 2, WinMaxHeight / 2, 0});
const Vector3 WinSize = Vector3({ WinMaxWidth, WinMaxHeight, 0 });

const wstring ShaderPath = L"../_Shaders/";
const wstring TexturePath = L"../_Textures/";
const wstring SoundPath = L"../Sounds/";

const wstring PathGaedrip = L"../_Textures/Gaedrip/";



const wstring PathPlayerIdle = L"../_Textures/Player/Idle/";
const wstring PathPlayerDuck = L"../_Textures/Player/Duck/";
const wstring PathPlayerJump = L"../_Textures/Player/Jump/";
const wstring PathPlayerOverWorldPlayer = L"../_Textures/Player/OverworldPlayer/";
const wstring PathPlayerParry = L"../_Textures/Player/Parry/";
const wstring PathPlayerRun = L"../_Textures/Player/Run/";
const wstring PathPlayerDash = L"../_Textures/Player/Dash/";







extern HWND handle;
