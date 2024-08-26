#include "Framework.h"
#include "IShader.h"

void IShader::CompileShader(wstring path, string entryName, string profile, ID3DBlob** blob)
{
    // 컴파일러 오류 메세지를 저장할 Blob 포인터
    ID3DBlob* error = nullptr;
    
    // 쉐이더 파일을 컴파일하고 결과를 매게변수로 받은 Blob에 전달
    HRESULT hr = D3DCompileFromFile
    (
        // 쉐이더 경로
        path.c_str(),
        // 쉐이더 파일의 헤더 위치
        nullptr,
        // Include 인터페이스를 구현한 클래스를 사용해 쉐이더 파일에서
        // 다른 파일을 include 할 때 사용할 수 있는 컨택스트
        nullptr,
        // 쉐이더 파일의 최초 진입점
        entryName.c_str(),
        // 쉐이더 파일의 프로필 이름
        profile.c_str(),
        // 컴파일 경고 옵션
        D3DCOMPILE_ENABLE_STRICTNESS,
        // 디버그 정보가 포함된 컴파일 결과를 생성하기 위한 옵샨
        0,
        // 컴파일 결과를 저장할 blob 포인터
        blob,
        // 컴파일러 오류 메세지를 저장할 blob 포인터 주소값
        &error
    );
    // 컴파일러 오류가 발생하면 메세지를 출력할 함수
    CheckShaderError(hr, error);
    SAFE_RELEASE(error);
}

void IShader::CheckShaderError(HRESULT hr, ID3DBlob* error)
{
    if (FAILED(hr))
    {
        if (error)
        {
            string str = (const char*)error->GetBufferPointer();
            MessageBoxA(handle, str.c_str(), "Shader Error", MB_OK);
        }
        // 프로그램 중단
        CHECK(false);
    }
}

/*
ID3DBlob
- 메모리에 할당된 데이터 덩어리
- 대표적으로 쉐이더 코드나 버퍼 데이터 등이 존재한다. 
- 메모리에 할당된 데이터 덩어리를 조작해 정보를 추출할 수 있다.
*/