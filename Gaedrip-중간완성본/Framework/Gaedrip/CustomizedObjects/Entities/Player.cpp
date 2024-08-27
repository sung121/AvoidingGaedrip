#include "Framework.h"
#include "Player.h"

<<<<<<< Updated upstream:Gaedrip-ì¤‘ê°„ì™„ì„±ë³¸/Framework/Gaedrip/CustomizedObjects/Entities/Player.cpp
=======
#include "BasicObjects/Collider.h"

>>>>>>> Stashed changes:AvoidGame/Framework/Gaedrip/CustomizedObjects/Entities/Player.cpp
Player::Player()
{
	rect = &AddComponent<Rect>();
	rect->transform.SetPosition(WinCenterPos);
	rect->transform.SetSize({500, 500, 0});
	//transform.SetPosition(WinCenterPos);
	//rect = new Rect(WinCenterPos, { 500, 500, 0 }, 0);
	collider = new Collider(WinCenterPos, { 500, 500, 0 }, 0);


	transform.AddTransform(rect->getTransformPointer());
	transform.AddTransform(collider->getTransformPointer());

	transform.SetSize( {30, 30, 0} );
	
	//rect->transform.SetSize(transform.GetSize());
	//collider->transform.SetSize(transform.GetSize());
	
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
	//cout << collider->transform.GetSize().y << endl;
	//cout << transform.GetSize().y << endl;
	//cout << rect->transform.GetSize().y << endl;
	
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

	cout << "¸®¼Â½Ã collider: " << collider->transform.GetPosition().y << endl;
	cout << "¸®¼Â½Ã gameobject: " << transform.GetPosition().y << endl;

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
		cout << "³²Àº ¿¡³ÊÁö: " << energy << endl;
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
	// Á¡ÇÁ ½ÃÀÛ
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
	}	// Á¡ÇÁ ³¡³ª°í ¶³¾îÁö´ÂÁß
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

		//±âÁØ½Ã°£º¸´Ù ÀûÀ»½Ã yÃà°¨¼Ó¿îµ¿
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
	// ¹«ÀûÀÌ¶ó¸é
	immortalTime -= Time::Delta();

	if (immortalTime > 0)
		return;

	// ¹«Àû½Ã°£ÀÌ 0 ÀÌÇÏ¶ó¸é
	rect->SetColor(Color(0, 0, 100, 0));
	isImmortal = false;

}
