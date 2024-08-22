#include "Framework.h"
#include "Texture2D.h"

using namespace DirectX;
vector<TextureDesc> Textures::descs;

Texture2D::Texture2D(wstring filePath)
    : filePath(filePath)
{
    Textures::Load(this);
}

void Texture2D::ReadPixel(vector<Color>* pixels)
{
    ID3D11Texture2D* texture;
    srv->GetResource((ID3D11Resource**)&texture);

    ReadPixel(texture, pixels);
    SAFE_RELEASE(texture);
}

void Texture2D::ReadPixel(ID3D11Texture2D* texture, vector<Color>* pixels)
{
    // 원본의 데이터를 저장해둘 설계도
    D3D11_TEXTURE2D_DESC srcDesc;
    // 매게변수 받은 원본의 데이터를 뽑아 설계도에 저장
    texture->GetDesc(&srcDesc);

    // 결과로 사용할 설계도
    D3D11_TEXTURE2D_DESC destDesc;
    ZeroMemory(&destDesc, sizeof(D3D11_TEXTURE2D_DESC));

    // 결과 텍스쳐 설계도 설정
    {
        // 사용 목적
        destDesc.Usage = D3D11_USAGE_STAGING;
        // CPU 접근 권한
        destDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        // 가로와 세로는 원본의 값을 넣는다.
        destDesc.Width = srcDesc.Width;
        destDesc.Height = srcDesc.Height;
        // mipmap 레벨을 1로 조정
        // mipmap은 그림의 퀄리티 레벨
        // 우리는 사용하지 않기에 1로 고정 
        destDesc.MipLevels = 1;
        // 배열 크기는 1로 설정
        destDesc.ArraySize = 1;
        // 포멧값은 원본의 포멧값으로
        destDesc.Format = srcDesc.Format;
        // 샘플링 방식은 원본의 방식으로
        destDesc.SampleDesc = srcDesc.SampleDesc;
    }

    ID3D11Texture2D* destTex = nullptr;
    HRESULT hr = DEVICE->CreateTexture2D(&destDesc, nullptr,
        &destTex);
    CHECK(hr);
    // 원본그림의 데이터를 destTex에 복사해 넣음
    D3DX11LoadTextureFromTexture(DC, texture, nullptr,
        destTex);

    // 픽셀 개수
    int pixelNum = destDesc.Width * destDesc.Height;

    // 픽셀 개수 만큼의 공간 확보
    UINT* colors = new UINT[pixelNum];

    D3D11_MAPPED_SUBRESOURCE subResoucre;
    DC->Map(destTex, 0, D3D11_MAP_READ, 0, &subResoucre);
    {
        memcpy(colors, subResoucre.pData,
            sizeof(UINT) * pixelNum);
    }
    DC->Unmap(destTex, 0);

    UINT* alpha = new UINT[pixelNum];
    UINT* red   = new UINT[pixelNum];
    UINT* green = new UINT[pixelNum];
    UINT* blue  = new UINT[pixelNum];

    for (int i = 0; i < pixelNum; i++)
    {
        // colors에서 ARGB 데이터 추출
        alpha[i] = (colors[i] & 0xFF000000);
        red[i]   = (colors[i] & 0x00FF0000);
        green[i] = (colors[i] & 0x0000FF00);
        blue[i]  = (colors[i] & 0x000000FF);

        // OpenGL의 코드와 호완되기 위해
        red[i]  = colors[i] >> 16;
        blue[i] = colors[i] << 16;

        // 컬러 재배치
        colors[i] = alpha[i] | red[i] | green[i] | blue[i];
    }

    // pixels에 colors 할당
    pixels->assign(&colors[0], &colors[pixelNum - 1]);

    SAFE_DELETE_ARRAY(colors);
    SAFE_RELEASE(destTex);
}

void Textures::Delete()
{
    for (TextureDesc desc : descs)
        SAFE_RELEASE(desc.srv);
}

void Textures::Load(Texture2D* texture)
{
    HRESULT hr;
    TexMetadata metaData;

    // texture가 가지고있는 파일 경로의
    // 파일 확장자라는 얻어낸다.
    wstring ext = Path::GetExtension(texture->filePath);
    if (ext == L"tga")
    {
        hr = GetMetadataFromTGAFile(texture->filePath.c_str(),
            metaData);
        CHECK(hr);
    }
    else if (ext == L"dds")
    {
        hr = GetMetadataFromDDSFile(texture->filePath.c_str(),
            DDS_FLAGS_NONE, metaData);
        CHECK(hr);
    }
    else
    {
        hr = GetMetadataFromWICFile(texture->filePath.c_str(),
            WIC_FLAGS_NONE, metaData);
        CHECK(hr);
    }

    // 메타 데이터에서 너비와 높이를 저장
    UINT width = metaData.width;
    UINT height = metaData.height;

    TextureDesc desc;
    desc.filePath = texture->filePath;
    desc.width = width;
    desc.height = height;

    // 중복 검사를 위한 desc와 bool값
    TextureDesc exist;
    bool bExist = false;

    for (TextureDesc temp : descs)
    {
        if (desc == temp) // 이거 할려고 구조체에 오퍼레이더 만듬
        {
            bExist = true;
            exist = temp;

            break;
        }
    }

    // 중복 됐다면
    if (bExist)
    {
        texture->srv = exist.srv;
        texture->metaData = metaData;
    }
    else // 존재하지 않는다면
    {
        // 이미지 파일 데이터를 읽고 쓰게 해주는 클래스
        ScratchImage image;

        if (ext == L"tga")
        {
            hr = LoadFromTGAFile(texture->filePath.c_str(),
                &metaData, image);
            CHECK(hr);
        }
        else if (ext == L"dds")
        {
            hr = LoadFromDDSFile(texture->filePath.c_str(),
                DDS_FLAGS_NONE, &metaData, image);
            CHECK(hr);
        }
        else
        {
            hr = LoadFromWICFile(texture->filePath.c_str(),
                WIC_FLAGS_NONE, &metaData, image);
            CHECK(hr);
        }

        ID3D11ShaderResourceView* srv = nullptr;
        hr = CreateShaderResourceView(DEVICE, image.GetImages(),
            image.GetImageCount(), metaData, &srv);
        CHECK(hr);

        desc.srv = srv;
        texture->srv = srv;
        texture->metaData = metaData;

        descs.push_back(desc);
    }
}

/*
DirectTex
- 그림 관련 데이터 가공할수 있는 기능이 많은 라이브러리

Metadata
- 그림의 너비,높이,깊이,배열 크기, 미핑 맵 수 등
그림에 있을수 있는 데이터들을 저장하는 구조체
*/