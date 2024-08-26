#pragma once

class VertexBuffer
{
public:
    ~VertexBuffer();

    template<typename T>
    void Create(const vector<T>& vertices,
        const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

    ID3D11Buffer* GetResource() { return buffer; }

    uint GetStride() { return stride; }
    uint GetOffset() { return offset; }
    uint GetCount() { return count; }

    void SetIA();

private:
    ID3D11Buffer* buffer = nullptr;

    uint stride = 0;    // 정점 버퍼에서 한 정점의 크기
    uint offset = 0;    // 정점 버퍼에서 읽을 시작 위치
    uint count = 0;     // 정점 버퍼에서 읽을 정점 개수
};

template<typename T>
inline void VertexBuffer::Create(const vector<T>& vertices, const D3D11_USAGE& usage)
{
    stride = sizeof(T);             // 정점의 크기
    count = vertices.size();        // 정점의 개수

    D3D11_BUFFER_DESC desc;         // 버퍼 생성을 위한 구조체 (설계도) 
    ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC)); // 구조체 초기화

    // desc 설정
    {
        // 버퍼의 사용 용도
        desc.Usage = usage;
        // 버퍼의 종류 설정 (정점 버퍼로 사용 선언)
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        // 버퍼의 크기
        desc.ByteWidth = stride * count;

        // cpu 설정
        switch (usage)
        {
            // CPU가 읽고 쓰는게 불가능하다.
            // GPU만 접근할수 있다.
        case D3D11_USAGE_DEFAULT:
            // CPU가 읽고 쓰는게 불가능하다.
            // GPU또한 읽기만 가능하다.
        case D3D11_USAGE_IMMUTABLE:
            break;
            
            // CPU가 접근 가능하고 수정도 가능하다.
        case D3D11_USAGE_DYNAMIC:
            // cpu에서 수정 가능함을 설정
            desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            break;

            // CPU가 접근 가능하고 GPU가 쓸수 있도록 변환할수있다.
        case D3D11_USAGE_STAGING:
            desc.CPUAccessFlags = 
                D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
            break;
        }
    }

    // 생성
    {
        D3D11_SUBRESOURCE_DATA subData; // 정점 데이터를 담아둘 구조체
        ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA)); // 초기화

        subData.pSysMem = vertices.data();

        // HRESULT는 만든 데이터가 잘 만들어 졌는지 검사하는 역할
        HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);
        CHECK(hr);
    }
}
