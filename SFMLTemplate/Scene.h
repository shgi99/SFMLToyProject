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

	virtual GameObject* AddGo(GameObject* obj, const std::string& name); // 추가 매개 변수 받기위한 string name 추가
	virtual void RemoveGo(GameObject* obj);

	virtual GameObject* FindGo(const std::string& name);
	virtual int FindGoAll(const std::string& name, std::list <GameObject*>& list);
	// 추가: 이름으로 GameObject 찾기
	virtual GameObject* GetGameObject(const std::string& name);
};

