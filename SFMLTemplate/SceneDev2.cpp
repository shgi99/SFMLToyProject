#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Obstacle.h"
#include "ObstaclePool.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{
}

void SceneDev2::Init()
{
	std::cout << "SceneDev2::Init()" << std::endl;

	GameObject* textObj = AddGo(new TextGo("fonts/KOMIKAP_.ttf"));
	textObj->SetOrigin(Origins::TL);
	textObj->SetPosition({0, 0});
	textObj->SetString("Dev2");

	std::vector<float> lanePositions = { 100.0f, 300.0f, 500.0f, 700.0f };
	std::vector<std::string> obstacleTextures = { "graphics/TurboObstacle_0.png", "graphics/TurboObstacle_1.png", "graphics/TurboObstacle_2.png", "graphics/TurboObstacle_3.png" };
	obstaclePool = new ObstaclePool(obstacleTextures, lanePositions, 500.0f, 10);  // 10개의 장애물을 미리 생성

	for (Obstacle* obstacle : obstaclePool->GetRandomObstacles(3))
	{
		obstacle->SetActive(true);
		AddGo(obstacle);
		std::cout << "Obstacle added at position: " << obstacle->Getposition().x << ", " << obstacle->Getposition().y << std::endl;
	}

	Scene::Init();
}

void SceneDev2::Enter()
{
	std::cout << "SceneDev2::Enter()" << std::endl;
	if (!TEXTURE_MGR.Load("graphics/TurboObstacle_0.png")) {
		std::cout << "Failed to load TurboObstacle_0.png" << std::endl;
	}
	if (!TEXTURE_MGR.Load("graphics/TurboObstacle_1.png")) {
		std::cout << "Failed to load TurboObstacle_1.png" << std::endl;
	}
	if (!TEXTURE_MGR.Load("graphics/TurboObstacle_2.png")) {
		std::cout << "Failed to load TurboObstacle_2.png" << std::endl;
	}
	if (!TEXTURE_MGR.Load("graphics/TurboObstacle_3.png")) {
		std::cout << "Failed to load TurboObstacle_3.png" << std::endl;
	}
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");

	Scene::Enter();
	Scene::Enter();
}

void SceneDev2::Exit()
{
	std::cout << "SceneDev2::Exit()" << std::endl;
	TEXTURE_MGR.Unload("graphics/TurboObstacle_0.png");
	TEXTURE_MGR.Unload("graphics/TurboObstacle_1.png");
	TEXTURE_MGR.Unload("graphics/TurboObstacle_2.png");
	TEXTURE_MGR.Unload("graphics/TurboObstacle_3.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
	Scene::Exit();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev1);
	}

	static float timer = 0.0f;
	timer += dt;
	std::cout << "Timer: " << timer << std::endl;
	if (timer > 2.0f)  // 2초마다 새로운 장애물 그룹 생성
	{
		std::cout << "Adding new obstacles" << std::endl;
		int numObstacles = ObstaclePool::GetRandomInt(2, 3);  // 2~3개의 장애물 활성화
		for (Obstacle* obstacle : obstaclePool->GetRandomObstacles(numObstacles))
		{
			obstacle->SetActive(true);
			AddGo(obstacle);
			std::cout << "Obstacle added at position: " << obstacle->Getposition().x << ", " << obstacle->Getposition().y << std::endl;
		}
		timer = 0.0f;
	}

	obstaclePool->Update(dt);  // 모든 장애물 업데이트
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	obstaclePool->Draw(window);
	Scene::Draw(window);
}
