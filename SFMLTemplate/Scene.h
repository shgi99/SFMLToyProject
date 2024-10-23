#pragma once
class Scene
{
protected:
	const SceneIds id;
	std::list<GameObject*> gameObjects;
public:
	Scene(SceneIds id);
	virtual ~Scene() = default;

	virtual void Init();
	virtual void Release();

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

<<<<<<< HEAD
	template<typename T>
	inline T* AddGo(T* obj);
=======
	virtual GameObject* AddGo(GameObject* obj, const std::string& name); // �߰� �Ű� ���� �ޱ����� string name �߰�
>>>>>>> Dev.Park
	virtual void RemoveGo(GameObject* obj);

	virtual GameObject* FindGo(const std::string& name);
	virtual int FindGoAll(const std::string& name, std::list <GameObject*>& list);
	// �߰�: �̸����� GameObject ã��
	virtual GameObject* GetGameObject(const std::string& name);
};
template<typename T>
inline T* Scene::AddGo(T* obj)
{
	if (std::find(gameObjects.begin(), gameObjects.end(), obj) == gameObjects.end())
	{
		gameObjects.push_back(obj);
	}
	return obj;
}
