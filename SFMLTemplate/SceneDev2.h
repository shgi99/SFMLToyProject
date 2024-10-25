#pragma once
#include "Scene.h"
#include "Player.h"
#include "timeBar.h"
#include "ObstaclePool.h"
#include "LaneManager.h"
#include "Fuel.h"

class SceneDev2 : public Scene
{
protected:
	ObstaclePool* obstaclePool = nullptr;
	Player* player = nullptr;
	LaneManager* laneManager = nullptr;
	Fuel* fuelItem = nullptr;
	timeBar timeBar;

	bool isPause = false;
	bool isGameOver;

	int score = 0;             // ���� ���� ����
	float scoreTimer = 0.0f;   // ���� ������Ʈ Ÿ�̸�
	const float scoreInterval = 0.1f; // ���� ������Ʈ ���� (��)
	float fuelSpawnTimer = 0.0f; 
	float obstacleSpawnTimer = 0.0f;
	const float fuelSpawnInterval = 1.5f;  // �⸧ ������ ����� ����
	const float obstacleSpawnInterval = 2.f;  // ��ֹ� ����� ����

	SpriteGo* mapObject = nullptr;
	int uvOffset;
public:
	SceneDev2();
	~SceneDev2() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	// Reset �Լ� ����
	void Reset();

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

