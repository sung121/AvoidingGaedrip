#pragma once

// 상속을 하기위한 객체로 인터페스라고 한다.
class IShader
{
public:
    // 생성
    virtual void Create(const wstring path, const string entryName) = 0;
    // 객체 초기화
    virtual void Clear() = 0;
    // 쉐이더 세팅
    virtual void SetShader() = 0;

protected:
    void CompileShader(wstring path, string entryName, string profile,
        ID3DBlob** blob);

    wstring path = L"";
    string entryName = "";

private:
    void CheckShaderError(HRESULT hr, ID3DBlob* error);
};