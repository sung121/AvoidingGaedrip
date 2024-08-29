#pragma once

template <typename T>
class Singleton : public Component
{
public:

	Singleton(GameObject& gameObject) : Component(gameObject)
	{
	}

	static void Create()
	{
		if (instance == nullptr)
		{
			gameObject = new GameObject();
			gameObject->AddComponent<T>();
		}
	}

	static void Delete()
	{
		delete instance;
		instance = nullptr;
	}

	static T* Get()
	{
		if (instance != nullptr)
		{
			return instance;
		}

		GameObject* gameObject = new GameObject();
		gameObject->AddComponent<T>();
		instance = &(gameObject->AddComponent<T>());
		//instance = gameObject->AddComponent<T>();
		return instance;
	}

protected:
	static T* instance;
};
template<typename T>
T* Singleton<T>::instance = nullptr;