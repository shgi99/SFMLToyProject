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

	int score = 0;             // 점수 저장 변수
	float scoreTimer = 0.0f;   // 점수 업데이트 타이머
	const float scoreInterval = 0.1f; // 점수 업데이트 간격 (초)
	float fuelSpawnTimer = 0.0f; 
	float obstacleSpawnTimer = 0.0f;
	const float fuelSpawnInterval = 1.5f;  // 기름 아이템 재생성 간격
	const float obstacleSpawnInterval = 2.f;  // 장애물 재생성 간격

	SpriteGo* mapObject = nullptr;
	int uvOffset;
public:
	SceneDev2();
	~SceneDev2() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	// Reset 함수 선언
	void Reset();

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

