#pragma once

class GameObject;
class Rigidbody;

class SceneBase : public IObject
{
public:
	void Init() override;
	void Destroy() override;
	void PhysicsUpdate() override;
	void Update() override;
	void Render() override;
	void PostRender() override;
	void GUI() override;

public:
	vector<GameObject> getGameObjects() { return gameObjects; };
	vector<Rigidbody> getRigidbodies() { return rigidBodies; };

private:
	vector<GameObject> gameObjects;
	vector<Rigidbody> rigidBodies;
};

