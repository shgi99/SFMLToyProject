#pragma once
#include "Scene.h"
#include "Player.h"
#include "timeBar.h"

class SceneDev2 : public Scene
{
protected:
	Player player;
	timeBar timeBar;
	bool isPause;

	int score = 0;             // ���� ���� ����
	float scoreTimer = 0.0f;   // ���� ������Ʈ Ÿ�̸�
	const float scoreInterval = 0.1f; // ���� ������Ʈ ���� (��)

public:
	SceneDev2();
	~SceneDev2() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

