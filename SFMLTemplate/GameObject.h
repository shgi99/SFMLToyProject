#pragma once
#include "defines.h"

class GameObject
{
protected:
	std::string name;

	bool active = true;

	sf::Vector2f position;
	Origins originPreset;
	sf::Vector2f origin;
	sf::Vector2f scale;
	sf::Text text; // text size 만들기위한 모든 gameobject 텍스트 추가
public:
	GameObject(const std::string& name = "");
	virtual ~GameObject() = default;

	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;

	const std::string& GetName() const { return name; }
	void SetName(const std::string& n) { name = n; }

	bool IsActive() const { return active; }
	void SetActive(bool a) { active = a; }
	virtual void SetScale(const sf::Vector2f& Scale) { scale = Scale; }

	sf::Vector2f GetPosition() const { return position; }
	virtual void SetPosition(const sf::Vector2f& pos) { position = pos; }
	sf::Vector2f GetOrigin() const { return origin; }
	virtual void SetOrigin(Origins preset);


	virtual void SetOrigin(const sf::Vector2f& newOrigin)
	{
		origin = newOrigin;
		originPreset = Origins::Custom;

	}
	// 텍스트 관련 메서드 추가
	virtual void SetString(const std::string& str = ""); // textsetString(str)추가
	virtual void SetTextSize(int size) { text.setCharacterSize(size); }


	virtual void Init(); // 생성 시 초기화
	virtual void Release(); // 동적 할당시 사용
	virtual void Reset(); //
	virtual void Update(float dt); // 활성, 비활성된 객체 업데이트 유무
	virtual void Draw(sf::RenderWindow& window);

};

