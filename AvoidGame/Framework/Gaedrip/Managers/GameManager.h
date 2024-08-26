#pragma once


class LevelManager;
class GameObject;
class Player;
class UserInterfaceManager;
class Collider;

class GameManager
{
public:

	static void ApplyGravity(GameObject* gameObject, float spd = 1);

	static void ApplyGravity(Player* player, float spd = 1);
	static void ApplyGravityPlayer(Player* player, float spd = 1);

	static bool CheckCollide(Collider* firstCollider , Collider* secondCollider);
	
	static float CaculateDistance(const Vector3& position1, const Vector3& position2);

	static void AttackPlayer(Player* player, int dmg = 1, bool makesImmortal = true, float immortalTime = 1.5f );

private:

	static float gravitySpd;
};

