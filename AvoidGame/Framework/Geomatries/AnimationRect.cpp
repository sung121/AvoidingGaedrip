#include "Framework.h"
#include "AnimationRect.h"

#include "BasicObjects/GameObject.h"

AnimationRect::AnimationRect(GameObject& gameObject, Vector3 position, Vector3 size)
    : TextureRect(gameObject, position, size, 0.0f, TexturePath + L"SolidBlack.png")
{
	MakeAnimator();
}

AnimationRect::AnimationRect(GameObject& gameObject, const Transform& transform)
	:TextureRect(gameObject, transform, TexturePath + L"SolidBlack.png")
{
	MakeAnimator();
}

AnimationRect::AnimationRect(GameObject& gameObject) : TextureRect(gameObject)
{
	MakeAnimator();
}

AnimationRect::~AnimationRect()
{
    SAFE_DELETE(animator);
}

void AnimationRect::MakeAnimator()
{
	animator = new Animator();
	Texture2D* srcTex = new Texture2D(TexturePath + L"Cat.png");
	AnimationClip* MoveR = new AnimationClip(L"MoveR", srcTex,
		8, { 0.0f, 32.0f * 4 }, { 32.0f * 8, 32.0f * 5 });

	clipNames.push_back(L"MoveR");

	animator->AddAnimClip(MoveR);

	animator->SetCurrentAnimClip(L"MoveR");

	SAFE_DELETE(srcTex);

	// Sampler 설정
	{
		// 선형 보간
		D3D11_SAMPLER_DESC desc;
		States::GetSamplerDesc(&desc);
		States::CreateSampler(&desc, &point[0]);

		// point Sampling
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		States::CreateSampler(&desc, &point[1]);
	}

	// Blend 설정
	{
		D3D11_BLEND_DESC desc;
		States::GetBlendDesc(&desc);
		States::CreateBlend(&desc, &bPoint[0]);

		desc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&desc, &bPoint[1]);
	}
}

void AnimationRect::Update()
{
    animator->Update();

    MapVertexBuffer();
    {
        vertices[0].uv.x = animator->GetCurrentFrame().x;
        vertices[0].uv.y = animator->GetCurrentFrame().y +
            animator->GetTexelFrameSize().y;

        vertices[1].uv.x = animator->GetCurrentFrame().x +
            animator->GetTexelFrameSize().x;
        vertices[1].uv.y = animator->GetCurrentFrame().y;

        vertices[2].uv.x = animator->GetCurrentFrame().x +
            animator->GetTexelFrameSize().x;
        vertices[2].uv.y = animator->GetCurrentFrame().y +
            animator->GetTexelFrameSize().y;

        vertices[3].uv.x = animator->GetCurrentFrame().x;
        vertices[3].uv.y = animator->GetCurrentFrame().y;
    }
    UnmapVertexBuffer();

    __super::Update();
}

void AnimationRect::Render()
{
    srv = animator->GetCurrentSRV();

    DC->PSSetSamplers(0, 1, &point[1]);
    DC->OMSetBlendState(bPoint[1], nullptr, 
        (UINT)0xFFFFFFFF);

    __super::Render();
}

void AnimationRect::Play()
{
	animator->StartUpdating();
}

void AnimationRect::Stop()
{
	animator->StopUpdating();
}

// UV값 집어넣을때: 좌상단 -> 우하단
void AnimationRect::AddClip(wstring clipName, wstring texturePath, UINT frameCount, Vector2 startUV, Vector2 endUV)
{
	Texture2D* srcTex = new Texture2D(texturePath);
	AnimationClip* clip = new AnimationClip(clipName, srcTex,
		frameCount, startUV, endUV);

	animator->AddAnimClip(clip);

	clipNames.push_back(clipName);
	SAFE_DELETE(srcTex);
}

void AnimationRect::DeleteClip()
{
}

void AnimationRect::SetClip(wstring clipName)
{
	for (int i = 0; i < clipNames.size(); i++)
	{
		if (clipNames[i] == clipName)
		{
			animator->SetCurrentAnimClip(clipName);
			return;
		}
	}
	throw out_of_range("존재하지 않는 클립 이름");
}

void AnimationRect::SetClip(UINT index)
{
	if (index > clipNames.size())
	{
		throw out_of_range("index 범위 초과");
	}
	animator->SetCurrentAnimClip(clipNames[index]);
}

void AnimationRect::SetTransform(Transform* transform)
{
	this->position = transform->GetPosition();
	this->size = transform->GetSize();
	this->rotation = transform->GetRotation();

}
