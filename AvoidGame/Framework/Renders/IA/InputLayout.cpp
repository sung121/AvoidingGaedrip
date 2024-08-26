#include "Framework.h"
#include "InputLayout.h"

InputLayout::~InputLayout()
{   
    SAFE_RELEASE(inputLayout);
}

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC* desc, uint count, ID3DBlob* blob)
{
    // 매게 변수중 하나라도 없다면 폭파
    if (!desc || !count || !blob)
        CHECK(false);

    // blob = 쉐이더 코드나 버터의 데이터 등을 저장하는 메모리

    HRESULT hr = DEVICE->CreateInputLayout
    (
        desc,                    // InputLayout의 Desc
        count,                   // InputLayout의 개수
        blob->GetBufferPointer(),// 쉐이더 코드를 포함하는 블롭 포인터
        blob->GetBufferSize(),   // 쉐이더 코드를 포함하는 블롭 크기
        &inputLayout
    );
}

void InputLayout::SetIA()
{
    DC->IASetInputLayout(inputLayout);
}
