#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startUV, Vector2 endUV, bool bReversed)
    :clipName(clipName), frameCount(frameCount),
    bReversed(bReversed)
{
    srv = srcTex->GetSRV();

    float imageWidth = srcTex->GetWidth();
    float imageHeight = srcTex->GetHeight();

    // 애니메이션을 그릴 그림 부분의 총 길이
    // 첫번째 클립부터 마지막 클립까지의 크기
    Vector2 clipSize = endUV - startUV;

    // 애니메이션 클립 1개의 크기
    Vector2 frameSize;
    frameSize.x = clipSize.x / frameCount;
    frameSize.y = clipSize.y;

    // uv좌표에서 사용할 클립 크기
    // uv는 0 ~ 1 까지 있기 때문
    texelFrameSize.x = frameSize.x / imageWidth;
    texelFrameSize.y = frameSize.y / imageHeight;

    // 그림 시작점 좌표
    Vector2 texelStartPos;
    texelStartPos.x = startUV.x / imageWidth;
    texelStartPos.y = startUV.y / imageHeight;

    // 실제 재생될 프레임의 좌표
    Vector2 keyFrame;

    for (int i = 0; i < frameCount; i++)
    {
        keyFrame.x = 
            texelStartPos.x + (texelFrameSize.x * i);
        keyFrame.y = texelStartPos.y;

        keyFrames.push_back(keyFrame);
    }
}

Animator::Animator()
{
}

Animator::~Animator()
{
    for (auto clip : animClips)
        SAFE_DELETE(clip.second);
}

void Animator::Update()
{
	if (stop == true && play == false)
	{
		return;
	}
	else if (stop == false && play == true)
	{

		// 플레이 레이트보다 델타타임이 많으면 다음 프레임으로 설정
		if (deltaTime > playRate)
		{
			// 역재생이 아니라면
			if (currentClip->bReversed == false)
			{
				//if (deltaTime > playRate * 2)
				//{
				//	// 델타타임 나누기 플레이레이트로 누락된 프레임 개수 계산해서 인덱스에 추가해주기
				//		
				//	float missedFramefloor = floor(deltaTime / playRate);

				//	currentFrameIndex += missedFramefloor;

				//	//누락된 프레임 개수만큼 빼서 할당하기
				//	if (currentFrameIndex > currentClip->frameCount)
				//		currentFrameIndex = currentFrameIndex - currentClip->frameCount;
				//	
				//
				//}
				//else
				
				currentFrameIndex++;

				// 출력해야 하는 프레임이 최대값이라면
				// 다시 0으로 돌려서 루프시킨다.
				if (currentFrameIndex == currentClip->frameCount)
					currentFrameIndex = 0;

				// 프레임 변경
				currentFrame =
					currentClip->keyFrames[currentFrameIndex];
			}
			else // 역재생이라면
			{
				currentFrameIndex--;

				// 출력해야하는 번호가 -1보다 작아졌다면
				if (currentFrameIndex <= -1)
					currentFrameIndex = currentClip->frameCount - 1;

				// 프레임 변경
				currentFrame =
					currentClip->keyFrames[currentFrameIndex];
			}
			deltaTime = 0.0f;
		}
		else // 아직 프레임을 바꿀때가 아니라면
			deltaTime += Time::Delta();
	}
}

void Animator::AddAnimClip(AnimationClip* animClip)
{
    animClips.insert(make_pair(animClip->clipName,
        animClip));
}

void Animator::SetCurrentAnimClip(wstring clipName)
{   
    // 현제 실행중인 애니메이션이 없고
    // 매개변수로 받은 클립이 존재한다면
    // 바로 실행한다
    if (currentClip == nullptr &&
        CheckExist(clipName) == true)
    {
        currentClip = animClips.find(clipName)->second;
        return;
    }
    // 이미 실행중인 애니메이션이라면 아무것도 안함
    else if (currentClip != nullptr &&
        currentClip->clipName == clipName)
    {
        return;
    }

    // 실행중인 애니메이션이 있고
    // 지금 실행중인 에니메이션이 아니라면
    // 즉, 애니메이션을 바꿀꺼라면

    // 애니메이션이 있는지 확인
    if (CheckExist(clipName))
    {
        // 애니메이션 넣어주고 시간 초기화
        currentClip = animClips.find(clipName)->second;
        deltaTime = 0.0f;

        // 만약 지금 실행할 애니메이션이
        // 역재생으로 실행해야 하는 애니메이션이면
        if (currentClip->bReversed == true)
            currentFrameIndex = currentClip->frameCount - 1;
        else // 역재생 하지 않는 다면
            currentFrameIndex = 0;

        // 애니메이션 실행
        currentFrame = 
            currentClip->keyFrames[currentFrameIndex];
    }
}