#include "stdafx.h"
#include "Player.h"


Player::Player(float jumpSpd, float jumpLimit)
	: jumpSpd(jumpSpd), jumpLimit(jumpLimit)
{

	player = new Rect(Vector3(500, 500, 0),
		Vector3(30, 30, 1), 0.0f);

	player->SetColor(Color(0, 0, 100, 1));
	lifes = standardLifes;

}

Player::~Player()
{
}

void Player::Update()
{
	player->Update();
}

void Player::SafeDelete()
{
	SAFE_DELETE(player);
}

bool Player::HasDamage()
{
	// 비무적일시 데미지 입음

	if (isPlayerImmortal == false)
	{
		lifes -= 1;
		printf("PalyerLife: %d\n", lifes);
		timeImmortal = 3;
		isPlayerImmortal = true;
		player->SetColor(Color(100, 0, 0, 1));
		
		return true;
	}
	else
	{
		return false;
	}
}

void Player::CheckDead()
{

}

void Player::Destroy()
{
	SAFE_DELETE(player);
}

void Player::Jump(float& gravitySpd, float standardgravitySpd)
{
	
		// 점프 코드
		{

			// 한 번 점프, 한계치o
			if (isJump == true && isJumpTwice == false && isReachAtLimit == true)
			{
				if (Keyboard::Get()->Down('W') || Keyboard::Get()->Down('w'))
				{
					isJumpTwice = true;
					isApplyGravity = false;
					timeJump = 0;
					isReachAtLimit = false;
					jumpSpd = 2000;


				}


			}
			// 한 번 점프 한계치 x
			if (isJump == true && isJumpTwice == false && isReachAtLimit == false)
			{
				if (Keyboard::Get()->Down('W') || Keyboard::Get()->Down('w'))
				{
					isJumpTwice = true;
					isApplyGravity = false;
					timeJump = 0;
					isReachAtLimit = false;
					jumpSpd = 2000;
				}

				float playerPosY = player->GetPosition().y;
				jumpSpd *= 0.95f;

				player->SetPosition(Vector3(player->GetPosition().x, playerPosY + jumpSpd * Time::Delta(), player->GetPosition().z));

				timeJump += Time::Delta();
				if (timeJump >= 0.2)
				{
					timeJump = 0;
					isReachAtLimit = true;
					isApplyGravity = true;
					gravitySpd = 400;
				}

			}

			// 한 번도 점프 안 했을 때
			if (isJump == false && isJumpTwice == false)
			{
				if (Keyboard::Get()->Down('W') || Keyboard::Get()->Down('w'))
				{
					isJump = true;
					isJumpTwice = false;
					isApplyGravity = false;
					timeJump = 0;
				}
			}

			// 이단 점프 했을 때
			if (isJumpTwice == true && isReachAtLimit == false)
			{
				float playerPosY = player->GetPosition().y;
				jumpSpd *= 0.95f;

				player->SetPosition(Vector3(player->GetPosition().x, playerPosY + jumpSpd * Time::Delta(), player->GetPosition().z));

				timeJump += Time::Delta();
				if (timeJump >= 0.2)
				{
					timeJump = 0;
					isApplyGravity = true;
					isReachAtLimit = true;
					gravitySpd = 400;

				}
			}
		}
}
