#include "Framework.h"
#include "PixelShader.h"

PixelShader::~PixelShader()
{
    Clear();
}

void PixelShader::Create(const wstring path, const string entryName)
{
    // 경로와 진입점 저장
    this->path = path;
    this->entryName = entryName;

    // 쉐이더 컴파일
    CompileShader(path, entryName, "ps_5_0", &blob);

    // 버텍스 쉐이더 생성
    HRESULT hr = DEVICE->CreatePixelShader
    (
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &shader
    );
    CHECK(hr);
}

void PixelShader::Clear()
{
    SAFE_RELEASE(blob);
    SAFE_RELEASE(shader);
}

void PixelShader::SetShader()
{
    DC->PSSetShader(shader, nullptr, 0);
}
