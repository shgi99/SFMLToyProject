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

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2),uvOffset(0)
{
}

void SceneDev2::Init()
{
	std::cout << "SceneDev2::Init()" << std::endl;

	player = new Player("graphics/TurboPlayer.png", "Player");
	player->SetScale({ 2.f, 2.f });
	player->SetOrigin(Origins::BC);  // �߽��� �������� ����
	player->SetPosition({ 768 / 2, 1024 / 2 });  // �ʱ� ��ġ ����
	AddGo(player, "player");  // ���� ������Ʈ ��Ͽ� �߰�

	std::vector<float> lanePositions = { 150.0f, 300.0f, 450.0f, 600.0f };
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
	//GameObject* mapObject = AddGo(new SpriteGo("graphics/TurboMap.png"),"TurboMap");
	//mapObject->SetOrigin(Origins::MC);
	//mapObject->SetPosition({ 768 / 2, 1024 / 2 });
	//mapObject->SetScale({ 0.7f,1.0f });
	//AddGo(mapObject, "TurboMap");
	mapObject = dynamic_cast<SpriteGo*>(AddGo(new SpriteGo("graphics/TurboMap.png"), "TurboMap")); // mapObject �ʱ�ȭ
	if (mapObject)
	{
		mapObject->SetOrigin(Origins::MC);
		mapObject->SetPosition({ 768 / 2, 1024 / 2 });
		mapObject->SetScale({ 0.7f, 2.0f });
	}

	GameObject* scoreTextObj = AddGo(new TextGo("fonts/KOMIKAP_.ttf"), "ScoreText");
	scoreTextObj->SetOrigin(Origins::TL);
	scoreTextObj->SetPosition({ 0, 20 }); // ���� ��ġ ����
	scoreTextObj->SetTextSize(50); // �ؽ�Ʈ ũ�� ����
	scoreTextObj->SetString("Score: 0"); // �ʱ� ���� ����

	GameObject* PauseTextObj = AddGo(new TextGo("fonts/KOMIKAP_.ttf"), "PauseText");
	PauseTextObj->SetOrigin(Origins::MC);
	PauseTextObj->SetPosition({ 768 / 2, 1024 / 2 }); // ���� ��ġ ����
	PauseTextObj->SetTextSize(50); // �ؽ�Ʈ ũ�� ����
	PauseTextObj->SetString("Press Enter to Start!!"); // �ʱ� ���� ����
	PauseTextObj->SetActive(false); // �ʱ� ���¿��� ��Ȱ��ȭ


	GameObject* gameOverTextObj = AddGo(new TextGo("fonts/KOMIKAP_.ttf"), "gameOverText");
	gameOverTextObj->SetOrigin(Origins::MC);
	gameOverTextObj->SetPosition({ 768 / 2, 1024 / 2 }); // ���� ��ġ ����
	gameOverTextObj->SetTextSize(50); // �ؽ�Ʈ ũ�� ����
	gameOverTextObj->SetString("Game Over..."); // �ʱ� ���� ����
	gameOverTextObj->SetActive(false); // �ʱ� ���¿��� ��Ȱ��ȭ

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

	FRAMEWORK.SetTimeScale(1.f);

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
	isGameOver = false;
}

void SceneDev2::Update(float dt)
{
	if (timeBar.IsGameOver())
	{
		isGameOver = true; // ���� ���� ���·� ����
		isPause = true; // ������ ����

		// ESC Ű�� ������ ���� �޴��� ���ư���
		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			SCENE_MGR.ChangeScene(SceneIds::Dev1);  // ���� �޴��� ���ư���
			Reset();  // ���� ���� �ʱ�ȭ
			return; // �߰����� ������Ʈ�� ���� ����
		}
	}

    if (isPause)
    {
		// ESC Ű�� ������ ���� �޴��� ���ư���
		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			SCENE_MGR.ChangeScene(SceneIds::Dev1);  // ���� �޴��� ���ư���
			Reset();  // ���� ���� �ʱ�ȭ
			return; // �߰����� ������Ʈ�� ���� ����
		}

        // �����̽��ٸ� ������ ������ �ٽ� ����
        if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
        {
            isPause = false;  // ���� �簳
        }

		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			Reset();  // ���� ���� �ʱ�ȭ
			isGameOver = false;  // ���� ���� ����
			isPause = false;  // �Ͻ����� ����
			return;
		}
		return;
	
    }

	// UV ������ ������Ʈ
	uvOffset -= 1500 * dt;  // UV �̵� �ӵ� ����

	if (mapObject && mapObject->GetTexture())
	{
		auto textureSize = mapObject->GetTexture()->getSize(); // �ؽ�ó ũ�� ��������
		int height = textureSize.y;

		// ���� �ֱ� ���� (2��)
		float resetInterval = 0.2f; // ���� �ֱ� (��)
		static float elapsedTime = 0.0f; // ��� �ð�

		elapsedTime += dt; // �����Ӹ��� �ð� �߰�

		if (isGameOver)  // ���� ���� ���� üũ
		{
			// ���� Ű�� ������ ���� �޴��� ���ư���
			if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
			{
				SCENE_MGR.ChangeScene(SceneIds::Dev1);  // ���� �޴��� ���ư���
				Reset();  // ���� ���� �ʱ�ȭ
			}
			return; // ���� ���� ���¿����� �ٸ� ������Ʈ�� ���� ����
		}

		// UV �������� �ؽ�ó ���̺��� �۾����� ��ġ�� ����
		if (uvOffset <= -height || elapsedTime >= resetInterval)
		{
			uvOffset = 0; // �������� 0���� ����
			elapsedTime = 0.0f; // ��� �ð� �ʱ�ȭ

			// ���� Y ��ġ�� �������� ����
			float newYPosition = 1024 / 2; // �⺻ ��ġ (���� �ʿ�)
			mapObject->SetPosition({ static_cast<float>(768) / 2, newYPosition });
		}

		// �ؽ�ó�� UV �ִϸ��̼� ����
		mapObject->SetTextureRect(sf::IntRect(0, static_cast<int>(uvOffset), mapObject->GetTexture()->getSize().x, mapObject->GetTexture()->getSize().y));
		player->Update(dt);


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
        if (obstacle && obstacle->IsActive())  // Ȱ��ȭ�� ��ֹ��� üũ
        {
            sf::FloatRect obstacleBounds = obstacle->GetGlobalBound();
            if (playerBounds.intersects(obstacleBounds))  // �浹 �߻� ��
            {
                isPause = true;  // ������ ����
				isGameOver = true;
                break;  // �浹 �߻� �� �� �̻� Ȯ������ ����
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
			if (pos.y > 1100)
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
	
	if (isPause && !isGameOver)
	{
		GameObject* PauseTextObj = dynamic_cast<TextGo*>(GetGameObject("PauseText"));
		if (PauseTextObj)
		{
			PauseTextObj->Draw(window); // PauseText �׸���
		}
	}

	// ���� ���� �ؽ�Ʈ �׸���
	if (isGameOver)
	{
		GameObject* gameOverTextObj = dynamic_cast<TextGo*>(GetGameObject("gameOverText"));
		if (gameOverTextObj)
		{
			gameOverTextObj->Draw(window); // Game Over �޽��� �׸���
		}
	}
}
