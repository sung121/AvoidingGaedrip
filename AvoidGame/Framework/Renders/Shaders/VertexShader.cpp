#include "Framework.h"
#include "VertexShader.h"

VertexShader::~VertexShader()
{
	Clear();
}

void VertexShader::Create(const wstring path, const string entryName)
{
	// 경로와 진입점 저장
	this->path = path;
	this->entryName = entryName;

	// 쉐이더 컴파일
	CompileShader(path, entryName, "vs_5_0", &blob);

	// 버텍스 쉐이더 생성
	HRESULT hr = DEVICE->CreateVertexShader
	(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&shader
	);
	CHECK(hr);
}

void VertexShader::Clear()
{
	SAFE_RELEASE(blob);
	SAFE_RELEASE(shader);
}

void VertexShader::SetShader()
{
	DC->VSSetShader(shader, nullptr, 0);
}
