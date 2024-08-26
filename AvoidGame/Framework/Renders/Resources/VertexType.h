#pragma once

// 색을 가지고 있는 정점
struct VertexColor
{
    VertexColor()
        : position(0,0,0), color(0,0,0,0) {}

    VertexColor(Vector3 position, Color color)
        : position(position), color(color) {}

    Vector3 position;   // 정점의 우치
    Color color;        // 정점의 색

    // 정점 데이터 구조를 서술
    static D3D11_INPUT_ELEMENT_DESC descs[];

    // 원소 개수
    static const uint count = 2;
};

// 그림을 가지고 있는 정점
struct VertexTexture
{
    VertexTexture()
        : position(0, 0, 0), uv(0, 0) {}

    VertexTexture(Vector3 position, Vector2 uv)
        : position(position), uv(uv) {}

    Vector3 position;   // 정점의 우치
    Vector2 uv;         // 그림의 좌표

    // 정점 데이터 구조를 서술
    static D3D11_INPUT_ELEMENT_DESC descs[];

    // 원소 개수
    static const uint count = 2;
};