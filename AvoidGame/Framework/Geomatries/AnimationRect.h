#pragma once

#include "TextureRect.h"
#include "Utilities/Animator.h"

class GameObject;

class AnimationRect : public TextureRect
{
public:
    AnimationRect(GameObject& gameObject, Vector3 position, Vector3 size);
	AnimationRect(GameObject& gameObject, const Transform& transform);
	AnimationRect(GameObject& gameObject);

    ~AnimationRect();

	void MakeAnimator();

    void Update();
    void Render();

	void Play();
	void Stop();

	void AddClip(wstring clipName, wstring texturePath, UINT frameCount, Vector2 startUV, Vector2 endUV);
	void DeleteClip();

	void SetClip(wstring clipName);
	void SetClip(UINT);

	void SetPlayRate(float playRate) { animator->SetPlayRate(playRate); }




	vector<wstring> GetClipNames() { return clipNames; }
	wstring GetCurrentClipName() { return animator->GetCurrentAnimClipName(); }

	void SetTransform(Transform* transform);

private:
    Animator* animator = nullptr;
    ID3D11SamplerState* point[2];
    ID3D11BlendState* bPoint[2];

	vector<wstring> clipNames;

};