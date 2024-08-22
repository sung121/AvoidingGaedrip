#pragma once

#include "Framework.h"

class ShaderBuffer
{
public:
    void SetVSBuffer(uint slot)
    {
        MapData();
        DC->VSSetConstantBuffers(slot, 1, &buffer);
    }
    void SetPSBuffer(uint slot)
    {
        MapData();
        DC->PSSetConstantBuffers(slot, 1, &buffer);
    }
protected:
    ShaderBuffer(void* data, uint dataSize)
        : data(data), dataSize(dataSize)
    {
        // 버퍼 사용 용도
        desc.Usage = D3D11_USAGE_DYNAMIC;
        // 버퍼 크기
        desc.ByteWidth = dataSize;
        // 바인딩 대상
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        // cpu 접근 방식
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &buffer);
        CHECK(hr);
    }

private:
    void MapData()
    {
        // 데이터 맵핑을 위한 구조체 
        D3D11_MAPPED_SUBRESOURCE subResource;

        HRESULT hr = DC->Map
        (
            buffer,                 // 매핑할 대상
            0,                      // 매핑 시작 위치
            D3D11_MAP_WRITE_DISCARD,// 매핑 방법 (discard 지웠다가 새로 쓴다)
            0,                      // 매핑할 하위 리소스
            &subResource            // 매핑된 메모리를 전달할 대상
        );
        CHECK(hr);

        // 데이터 복사
        memcpy(subResource.pData, data, dataSize);
        
        // 언매핑
        DC->Unmap(buffer, 0);
    }

private:
    D3D11_BUFFER_DESC desc = { 0 };
    ID3D11Buffer* buffer = nullptr;

    void* data = nullptr;
    uint dataSize = 0;
};