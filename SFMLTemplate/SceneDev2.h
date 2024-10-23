#pragma once
#include "Scene.h"
#include "ObstaclePool.h"
class SceneDev2 : public Scene
{
protected:
	ObstaclePool* obstaclePool = nullptr;
public:
	SceneDev2();
	~SceneDev2() = default;
	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

