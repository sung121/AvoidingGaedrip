#pragma once

class AnimationClip
{
public:
    // Animator가 AnimationClip의 모든 데이터에 접근하는것을 허락하겠다.
    friend class Animator;

    AnimationClip(wstring clipName,
        Texture2D* srcTex, UINT frameCount,
        Vector2 startUV, Vector2 endUV,
        bool bReversed = false);

protected:
    wstring clipName = L"";
    vector<Vector2> keyFrames;
    UINT frameCount = 0;
    ID3D11ShaderResourceView* srv = nullptr;
    Vector2 texelFrameSize = Values::ZeroVec2;
    bool bReversed = false;

};

class Animator
{
public:
    Animator();
    ~Animator();

    void Update();

    Vector2 GetCurrentFrame() { return currentFrame; }
    Vector2 GetTexelFrameSize() 
    { return currentClip->texelFrameSize; }
    ID3D11ShaderResourceView* GetCurrentSRV()
    { return currentClip->srv; }

    void AddAnimClip(AnimationClip* animClip);
    void SetCurrentAnimClip(wstring clipName);
	wstring GetCurrentAnimClipName() { return currentClip->clipName; };

	void StopUpdating() { stop = true; play = false; }
	void StartUpdating() { play = true; stop = false; }

	bool CheckExist(wstring clipName)
	{
		return animClips.find(clipName) != animClips.end();
	}

	void SetPlayRate(float playRate) { this->playRate = playRate; }
	float GetPlayRate(float playRate) { return this->playRate; }

	
private:
    // 애니메이션 이름과 애니메이션이 들어가는 변수
    unordered_map<wstring, AnimationClip*> animClips;
    // 애니메이션이 중복인지 확인하고
    
    // 현제 실행중인 애니메이션과 그 데이터들
    AnimationClip* currentClip = nullptr;
    UINT currentFrameIndex = 0;
    Vector2 currentFrame = Values::ZeroVec2;

	bool stop = false;
	bool play = true;

    float deltaTime = 0.0f;
    float playRate = 1.0f / 15.0f;
};