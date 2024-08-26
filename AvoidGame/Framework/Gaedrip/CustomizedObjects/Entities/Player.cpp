#include "Framework.h"
#include "Player.h"

#include "BasicObjects/Collider.h"
#include "Geomatries/Rect.h"

Player::Player()
{
	transform.SetPosition(WinCenterPos);
	rect = new Rect(WinCenterPos, { 500, 500, 0 }, 0);
	collider = new Collider(WinCenterPos, { 500, 500, 0 }, 0);


	transform.AddTransform(rect->getTransformPointer());
	transform.AddTransform(collider->getTransformPointer());

	transform.SetSize( {30, 30, 0} );
	
	jumpSpd = standardJumpSpd;

	collider->transform = this->transform;
	rect->transform = this->transform;

	rect->SetColor(Color(0, 0, 100, 1));


}

Player::~Player()
{
}

void Player::Update()
{
	rect->Update();
	collider->transform.SetPosition(this->transform.GetPosition());
	collider->Update();

	AdjustImmortal();

}

void Player::Render()
{
	if (rendersColliderWireFrame == true)
	{
		collider->Render();
	}
	else
	{
		rect->Render();
	}
}

void Player::GUI()
{
	//rect->GUI("Player");
	collider->GUI("PlayerCollider");
}

void Player::Reset()
{
	transform.SetPosition(WinCenterPos);

	cout << "리셋시 collider: " << collider->transform.GetPosition().y << endl;
	cout << "리셋시 gameobject: " << transform.GetPosition().y << endl;

	jumps = false;

	hp = maxHp;

	jumps = false;
	jumpsTwice = false;
	jumpsFirst = false;
	moves = false;

	energy = 1.5f;
	standardEnergy = 1.5f;

	isExhausted = false;

	dashs = false;
	dashsFirst = false;

	reachsAtJumpLimit = true;
	reachsAtGround = true;

	applysGravity = true;

	jumpSpd;
	standardJumpSpd = 1400;

	moveSpd = 450;
	standardMoveSpd = 450;

	jumpTime = 0;
	standardJumpTime = 0.25;

	moveL = false;
	moveR = false;

	moveU = false;
}

void Player::MoveWidth()
{
	
	if (Keyboard::Get()->Up('D') || Keyboard::Get()->Up(VK_RIGHT))
	{
		moves = false;
		moveR = false;
	}
	if (Keyboard::Get()->Up('A') || Keyboard::Get()->Up(VK_LEFT))
	{
		moves = false;
		moveL = false;
	}
	if (dashs == false)
	{

		if (Keyboard::Get()->Press('A') || Keyboard::Get()->Press(VK_LEFT))
		{
			moveL = true;
			moves = true;
			transform.SetPositionX(transform.GetPosition().x - moveSpd * Time::Delta());
			if ((Keyboard::Get()->Press('D') || Keyboard::Get()->Press(VK_RIGHT)) && !moveR)
			{
				moveL = false;
				transform.SetPositionX(transform.GetPosition().x + moveSpd * 2 * Time::Delta());
			}
		}
		else if (Keyboard::Get()->Press('D') || Keyboard::Get()->Press(VK_RIGHT))
		{
			moves = true;
			moveR = true;
			transform.SetPositionX(transform.GetPosition().x + moveSpd * Time::Delta());
		}
	}
}

void Player::CheckAndSetRuns()
{
	if (Keyboard::Get()->Press(VK_SHIFT) && isExhausted == false)
	{
		cout << "남은 에너지: " << energy << endl;
		if (energy < 0)
			isExhausted = true;
		else
		{
			moveSpd = standardMoveSpd + 350;
			if (moves == true)
			{
				energy -= Time::Delta();
			}
		}
		
	}
	else
	{
		moveSpd = standardMoveSpd;
		energy += Time::Delta() / 2;
		if (energy > standardEnergy)
		{
			isExhausted = false;
			energy = standardEnergy;
		}
	}
}

void Player::Jump()
{
	// 점프 시작
	if ((Keyboard::Get()->Down(VK_UP)) && jumpsTwice == false && jumpsFirst == true)
	{
		jumps = true;
		jumpsTwice = true;
		reachsAtGround = false;
		applysGravity = false;
		reachsAtJumpLimit = false;
		jumpTime = 0;
		jumpSpd = standardJumpSpd;
	}

	if ((Keyboard::Get()->Down(VK_UP)) && (jumps == false) && reachsAtGround == true)
	{
		reachsAtGround = false;
		jumps = true;
		applysGravity = false;
		reachsAtJumpLimit = false;
		jumpsFirst = true;
	}	// 점프 끝나고 떨어지는중
	else if (reachsAtJumpLimit == true && reachsAtGround == false)
	{
		jumpTime = 0;
		jumpSpd = standardJumpSpd;
		jumps = false;
		applysGravity = true;
	}


	if (jumps == true)
	{
		jumpTime += Time::Delta();

		//기준시간보다 적을시 y축감속운동
		if (jumpTime <= standardJumpTime)
		{
			float playerPosY = transform.GetPosition().y;
			transform.SetPosition(Vector3(transform.GetPosition().x, playerPosY + jumpSpd * Time::Delta(), transform.GetPosition().z));
			jumpSpd *= 0.90f;
		}
		else if (jumpTime <= standardJumpTime + 0.01f)
		{

		}
		else if(jumpTime > standardJumpTime + 0.01f)
		{
			reachsAtGround = false;
			reachsAtJumpLimit = true;
			return;
		}

	}



}

void Player::ChangeRenderStates()
{
	rendersColliderWireFrame = !rendersColliderWireFrame;
}

void Player::AdjustImmortal()
{
	if (!isImmortal)
		return;
	// 무적이라면
	immortalTime -= Time::Delta();

	if (immortalTime > 0)
		return;

	// 무적시간이 0 이하라면
	rect->SetColor(Color(0, 0, 100, 0));
	isImmortal = false;

}
