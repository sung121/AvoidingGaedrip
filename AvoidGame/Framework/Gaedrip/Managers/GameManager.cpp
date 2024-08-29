#include "Framework.h"
#include "GameManager.h"

#include "BasicObjects/GameObject.h"
#include "Gaedrip/CustomizedObjects/Entities/Player.h"
#include "UserInterfaceManager.h"
#include "LevelManager.h"

float GameManager::gravitySpd = 9.8f;

void GameManager::ApplyGravity(GameObject* gameObject, float additionalSpd)
{
	gameObject->transform.SetPositionY(gameObject->transform.GetPosition().y - 9.8f * additionalSpd * Time::Delta());
	
}

void GameManager::ApplyGravity(Player* player, float additionalSpd)
{
	player->transform.SetPositionY(player->transform.GetPosition().y - 9.8f * additionalSpd * Time::Delta());
}

void GameManager::ApplyGravityPlayer(Player* player, float additionalSpd)
{
	if (player->getApplysGravity() == true)
	{
		player->transform.SetPositionY(player->transform.GetPosition().y - 9.8f * additionalSpd * Time::Delta());
	}

}
bool GameManager::CheckCollide(Collider* collider, Collider* collider2)
{
	return BoundingBox::OBB(collider->GetCollider(), collider2->GetCollider());
}

float GameManager::CaculateDistance(const Vector3& position1, const Vector3& position2)
{
	Vector3 vec = (position1 - position2);

	float distance = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));

	return distance;
}

void GameManager::AttackPlayer(Player* player, int dmg, bool makesImmortal, float immortalTime)
{
	player->setHp(player->getHp() - dmg);
	player->setColor(Color(100, 0, 0, 0));
	
	if (player->getHp() <= 0) // Á×À¸¸é 
	{
		UserInterfaceManager::Get()->setIsMain(true);
	}

	if (!makesImmortal) 
		return;
	
	player->setImmortalTime(immortalTime);
	player->setIsImmortal(true);

}


