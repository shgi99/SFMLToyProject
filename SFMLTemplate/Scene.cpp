#include "stdafx.h"
#include "Scene.h"

Scene::Scene(SceneIds id) : id(id)
{
}

void Scene::Init()
{
	// 초기에 갖고 있어야하는 GameObject들을 add
	for (auto obj : gameObjects)
	{
		obj->Init();
	}
}

void Scene::Release()
{
	for (auto obj : gameObjects)
	{
		delete obj;
		obj->Release();
	}
}

void Scene::Enter()
{
	// Scene이 바뀌고 재시작할때마다 호출되는 함수
	for (auto obj : gameObjects)
	{
		obj->Reset();
	}
}

void Scene::Exit()
{
}

void Scene::Update(float dt)
{
	for (auto& obj : gameObjects)
	{
		if (!obj->IsActive())
		{
			continue;
		}

		obj->Update(dt);
	}
}

void Scene::Draw(sf::RenderWindow& window)
{
	for (auto& obj : gameObjects)
	{
		if (!obj->IsActive())
		{
			continue;
		}

		obj->Draw(window);
	}
}

void Scene::RemoveGo(GameObject* obj)
{
	gameObjects.remove(obj);
}


GameObject* Scene::FindGo(const std::string& name)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}

	return nullptr;
}

int Scene::FindGoAll(const std::string& name, std::list<GameObject*>& list)
{
	int cnt = 0;
	list.clear();

	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			list.push_back(obj);
			cnt++;
		}
	}

	return cnt;
}

GameObject* Scene::GetGameObject(const std::string& name)
{
	return FindGo(name); // FindGo 메서드를 사용하여 이름으로 객체를 찾음
}

