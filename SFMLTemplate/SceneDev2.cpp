#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Obstacle.h"
#include "ObstaclePool.h"
#include "Scene.h"
#include "Player.h"
#include "Fuel.h"
#include "LaneManager.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{
}

void SceneDev2::Init()
{
	std::cout << "SceneDev2::Init()" << std::endl;

	player = new Player("graphics/TurboPlayer.png", "Player");
	player->SetOrigin(Origins::BC);  // �߽��� �������� ����
	player->SetPosition({ 450, 800 });  // �ʱ� ��ġ ����
	AddGo(player, "player");  // ���� ������Ʈ ��Ͽ� �߰�

	std::vector<float> lanePositions = { 100.0f, 300.0f, 500.0f, 700.0f };
	laneManager = new LaneManager(lanePositions);

	std::vector<std::string> obstacleTextures = { "graphics/TurboObstacle_0.png", "graphics/TurboObstacle_1.png", "graphics/TurboObstacle_2.png", "graphics/TurboObstacle_3.png" };
	obstaclePool = new ObstaclePool(obstacleTextures, lanePositions, 500.0f, 10);  // 10���� ��ֹ��� �̸� ����

	fuelItem = new Fuel("graphics/TurboFuel.png", "fuel", 500.f);
	fuelItem->SetActive(false);
	fuelItem->SetOrigin(Origins::MC);
	AddGo(fuelItem, "fuelItem");


	// �÷��̾� �ʱ�ȭ
	player->Reset(); 

	// timeBar �ʱ�ȭ
	timeBar.SetTotalTime(5.0f); // �� �ð��� �����ϴ� ����

	for (Obstacle* obstacle : obstaclePool->GetRandomObstacles(3))
	{
		obstacle->SetActive(true);
		AddGo(obstacle, "obstacle");
	}
	GameObject* obj = AddGo(new SpriteGo("graphics/TurboMap.png"),"TurboMap");
	obj->SetOrigin(Origins::MC);
	obj->SetPosition({ 900 / 2, 1000 / 2 });



	GameObject* scoreTextObj = AddGo(new TextGo("fonts/KOMIKAP_.ttf"), "ScoreText");
	scoreTextObj->SetOrigin(Origins::TL);
	scoreTextObj->SetPosition({ 0, 20 }); // ���� ��ġ ����
	scoreTextObj->SetTextSize(50); // �ؽ�Ʈ ũ�� ����
	scoreTextObj->SetString("Score: 0"); // �ʱ� ���� ����

	GameObject* PauseTextObj = AddGo(new TextGo("fonts/KOMIKAP_.ttf"), "PauseText");
	PauseTextObj->SetOrigin(Origins::MC);
	PauseTextObj->SetPosition({ 900 / 2, 1000 / 2 }); // ���� ��ġ ����
	PauseTextObj->SetTextSize(50); // �ؽ�Ʈ ũ�� ����
	PauseTextObj->SetString("Press Enter to Start!!"); // �ʱ� ���� ����
	PauseTextObj->SetActive(true); // �ʱ� ���¿��� ��Ȱ��ȭ

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
	if (!TEXTURE_MGR.Load("graphics/TurboPlayer.png")) {
		std::cout << "Failed to load TurboPlayer.png" << std::endl;
	}
	TEXTURE_MGR.Load("graphics/TurboFuel.png");
	TEXTURE_MGR.Load("graphics/TurboMap.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");

	Scene::Enter();
}

void SceneDev2::Exit()
{
	std::cout << "SceneDev2::Exit()" << std::endl;
	TEXTURE_MGR.Unload("graphics/TurboObstacle_0.png");
	TEXTURE_MGR.Unload("graphics/TurboObstacle_1.png");
	TEXTURE_MGR.Unload("graphics/TurboObstacle_2.png");
	TEXTURE_MGR.Unload("graphics/TurboObstacle_3.png");
    TEXTURE_MGR.Unload("graphics/TurboPlayer.png");
	TEXTURE_MGR.Unload("graphics/TurboFuel.png");
	TEXTURE_MGR.Unload("graphics/TurboMap.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
	Scene::Exit();
}

void SceneDev2::Reset()
{
	// �÷��̾� �ʱ�ȭ
	player->Reset(); 

	// Ÿ�̸� �ʱ�ȭ
	score = 0;
	scoreTimer = 0.0f;

	// timeBar �ʱ�ȭ
	timeBar.Reset(); 

	// ��ֹ� Ǯ �ʱ�ȭ
	obstaclePool->Reset(); 

	// ��ֹ� ��Ȱ��ȭ
	for (auto& obj : gameObjects)
	{
		if (obj->GetName() == "obstacle")
		{
			obj->SetActive(false);
		}
	}
}

void SceneDev2::Update(float dt)
{
	if (isPause)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			isPause = false;
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			SCENE_MGR.ChangeScene(SceneIds::Dev1);
			Reset();
		}

		return;
	}

	Scene::Update(dt);

	scoreTimer += dt;

	if (scoreTimer >= scoreInterval)
	{
		score += 1;
		scoreTimer = 0.0f;
	}

	sf::FloatRect playerBounds = player->GetGlobalBound();

	std::list<GameObject*> obstacleList;
	int obstacleCount = FindGoAll("obstacle", obstacleList);

	// ��ֹ��� �÷��̾� �浹 ���� Ȯ��
	for (GameObject* obj : obstacleList)
	{
		Obstacle* obstacle = dynamic_cast<Obstacle*>(obj);
		if (obstacle && obstacle->IsActive())
		{
			sf::FloatRect obstacleBounds = obstacle->GetGlobalBound();
			if (playerBounds.intersects(obstacleBounds))
			{
				isPause = true;
				break;
			}
		}
	}

	// ��ֹ��� ȭ�� ������ ������ ��Ȱ��ȭ�ϰ� ���� ����
	for (GameObject* obj : obstacleList)
	{
		Obstacle* obstacle = dynamic_cast<Obstacle*>(obj);
		if (obstacle && obstacle->IsActive())
		{
			sf::Vector2f pos = obstacle->GetPosition();
			if (pos.y > 1000)
			{
				obstacle->SetActive(false);
				laneManager->SetLaneUsed(pos.x, false);  // ���� ����
			}
		}
	}

	// ��ֹ� ����
	obstacleSpawnTimer += dt;
	if (obstacleSpawnTimer > obstacleSpawnInterval)
	{
		obstacleSpawnTimer = 0.0f;

		int numObstacles = ObstaclePool::GetRandomInt(2, 3);
		for (Obstacle* obstacle : obstaclePool->GetRandomObstacles(numObstacles))
		{
			float lane = laneManager->GetAvailableLane();
			if (lane != -1.0f)
			{
				obstacle->SetPosition(sf::Vector2f(lane, -100.0f));
				laneManager->SetLaneUsed(lane, true);
				obstacle->SetActive(true);
				AddGo(obstacle, "obstacle");
			}
		}
	}


	// �⸧ ������ ����
	fuelSpawnTimer += dt;
	if (!fuelItem->IsActive() && fuelSpawnTimer > fuelSpawnInterval)
	{
		fuelSpawnTimer = 0.0f;

		// �⸧ �������� ��ֹ��� ��ġ�� �ʵ��� ������ ����
		float lane = laneManager->GetAvailableLane();
		bool laneOccupied = false;

		// ��ֹ��� ��ġ�� �ʴ� ������ ����
		for (GameObject* obj : obstacleList)
		{
			Obstacle* obstacle = dynamic_cast<Obstacle*>(obj);
			if (obstacle && obstacle->IsActive())
			{
				if (obstacle->GetPosition().x == lane)
				{
					laneOccupied = true;
					break;
				}
			}
		}

		if (lane != -1.0f && !laneOccupied)
		{
			fuelItem->SetPosition(sf::Vector2f(lane, -100.0f));
			fuelItem->SetActive(true);
			laneManager->SetLaneUsed(lane, true);
		}
	}

	// �÷��̾ �⸧ �����۰� �浹���� ��
	if (fuelItem->IsActive() && playerBounds.intersects(fuelItem->GetGlobalBound()))
	{
		fuelItem->SetActive(false);
		timeBar.AddTime(10.0f);  // Ÿ�ӹٿ� �ð� �߰�
		laneManager->SetLaneUsed(fuelItem->GetPosition().x, false);  // ���� ����
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		isPause = true;
	}
	player->Update(dt);
	timeBar.Update(dt);
	obstaclePool->Update(dt);
	fuelItem->Update(dt);
}


void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	obstaclePool->Draw(window);
	player->Draw(window);
	fuelItem->Draw(window);
	timeBar.Draw(window);

	GameObject* scoreTextObj = dynamic_cast<TextGo*>(GetGameObject("ScoreText")); // ���� ��ü ã��
	if (scoreTextObj)
	{
		scoreTextObj->SetString("Score: " + std::to_string(score)); // ���� ������Ʈ
	}
	
	if (isPause)
	{
		GameObject* pauseTextObj = dynamic_cast<TextGo*>(GetGameObject("PauseText"));
		if (pauseTextObj)
		{
			pauseTextObj->Draw(window); // PauseText �׸���
		}
	}
}
