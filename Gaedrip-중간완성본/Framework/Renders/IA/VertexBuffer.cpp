#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
    // I로 시작하는 DX자료형은 RELEASE를 사용해 해제한다.
    SAFE_RELEASE(buffer);
}

void VertexBuffer::SetIA()
{
    // IA에 정점 버퍼를 건내주는 함수
    DC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
}
