// VertexInput 구조체 정의

struct VertexInput
{
    float4 position : POSITION0; // 정점의 위치
    float2 uv : TEXCOORD0; // uv 좌표
};

struct PixelInput
{
    float4 position : SV_POSITION0; // 정점의 위치
    float2 uv : TEXCOORD0; // 정점의 색상   
};


cbuffer WorldBuffer : register(b0)
{
    matrix _world;
};

cbuffer VPBuffer : register(b1)
{
    matrix _view;
    matrix _projection;
};

// 버텍스 쉐이더
PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    // 이 순서대로 곱해야 원하는 위치에 값을 얻을 수 있다.
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);
    
    output.uv = input.uv;
    
    return output;
};

// 텍스처 데이터
Texture2D _sourceTex : register(t0);

//샘플링 데이터
SamplerState _samp : register(s0);

// 픽셀 쉐이더
float4 PS(PixelInput input) : SV_Target
{
    float4 color = _sourceTex.Sample(_samp, (float2) input.uv);
    if (color.r >= 0.90f && color.g <= 0.9f && color.b >= 0.90f)
        discard;
    
    
        
        
        return color;
};

/*
Semantic : 세멘틱(녹색 대문자 문자들)
- HLSL 쉐이더에서 데이터의 의미를 지정하는 데 사용
- 쉐이더가 입력 데이터와 출력 데이터를 올바르게 해석하고 처리할 수 있도록 도와줌
- 변수 이름 뒤에 ':' 기호와 함께 지정
- 시스템 값 세멘틱은 'SV_' 접두사로 시작하며 Directx3D에서 정의된 특별한 의미를 지닌다.
- 시스템 값 세멘틱은 쉐이더 스테이지 간의 데이터를 전달하는데 사용된다.

slot
- GPU에서 사용하는 상수 버퍼, 텍스처, 샘플러 등의 자원을 식별하는 인덱스
- 각 슬롯은 고유한 번호를 가지며, 해당 자원의 유형과 역할에 따라 다르게 할당됨
- register라는 키워드를 사용하여 지정
- 각 자원이 어떤 슬롯에 할당될 것인지 명시적으로 지정할 수 있음
- 주요 슬롯 
    1) 상수 버퍼 슬롯
    - 상수 데이터를 지정하는데 사용되며, VS와 PS에서 공유될 수 있다.
    - 상수 버퍼 슬롯은 register(b#)을 사용하여 지정한다.
    
    2) 텍스처 슬롯
    - 이미지 데이터를 저장하는데 사용
    - 텍스처 슬롯은 register(t#)을 사용하여 지정
    
    3) 샘플러 슬롯
    - 텍스처를 샘플링하는데 사용
    - 샘플러 슬롯은 register(s#)을 사용하여 지정

cbuffer = Contant Buffer : 상수 버퍼
- 쉐이더에서 사용하는 전역 변수를 저장하는데 사용
- 각 상수 버퍼 레지스터에는 한 개의 상수 버퍼만 할당할 수 있음

- 상수 버퍼 내부에는 여러 개의 변수를 선언할 수 있다.




*/



 