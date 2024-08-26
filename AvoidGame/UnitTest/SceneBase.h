#pragma once

class GameObject;

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
	vector<GameObject> gameObjects;
	//vector<>

};

