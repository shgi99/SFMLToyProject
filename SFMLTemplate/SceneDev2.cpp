#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGo.h"
#include "TextGo.h"
<<<<<<< HEAD
#include "Obstacle.h"
#include "ObstaclePool.h"
=======
#include "Scene.h"


>>>>>>> Dev.Park

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{
}

void SceneDev2::Init()
{
	std::cout << "SceneDev2::Init()" << std::endl;

<<<<<<< HEAD
	GameObject* textObj = AddGo(new TextGo("fonts/KOMIKAP_.ttf"));
	textObj->SetOrigin(Origins::TL);
	textObj->SetPosition({0, 0});
	textObj->SetString("Dev2");

	std::vector<float> lanePositions = { 100.0f, 300.0f, 500.0f, 700.0f };
	std::vector<std::string> obstacleTextures = { "graphics/TurboObstacle_0.png", "graphics/TurboObstacle_1.png", "graphics/TurboObstacle_2.png", "graphics/TurboObstacle_3.png" };
	obstaclePool = new ObstaclePool(obstacleTextures, lanePositions, 500.0f, 10);  // 10���� ��ֹ��� �̸� ����

	for (Obstacle* obstacle : obstaclePool->GetRandomObstacles(3))
	{
		obstacle->SetActive(true);
		AddGo(obstacle);
		std::cout << "Obstacle added at position: " << obstacle->Getposition().x << ", " << obstacle->Getposition().y << std::endl;
	}
=======
	GameObject* obj = AddGo(new SpriteGo("graphics/TurboMap.png"),"TurboMap");
	obj->SetOrigin(Origins::MC);
	obj->SetPosition({ 900 / 2, 1000 / 2 });



	GameObject* scoreTextObj = AddGo(new TextGo("fonts/KOMIKAP_.ttf"), "ScoreText");
	scoreTextObj->SetOrigin(Origins::TL);
	scoreTextObj->SetPosition({ 0, 20 }); // ���� ��ġ ����
	scoreTextObj->SetTextSize(50); // �ؽ�Ʈ ũ�� ����
	scoreTextObj->SetString("Score: 0"); // �ʱ� ���� ����
>>>>>>> Dev.Park

	Scene::Init();
}

void SceneDev2::Enter()
{
	std::cout << "SceneDev2::Enter()" << std::endl;
<<<<<<< HEAD
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
=======
	TEXTURE_MGR.Load("graphics/TurboMap.png");
>>>>>>> Dev.Park
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");

	Scene::Enter();
	Scene::Enter();
}

void SceneDev2::Exit()
{
	std::cout << "SceneDev2::Exit()" << std::endl;
<<<<<<< HEAD
	TEXTURE_MGR.Unload("graphics/TurboObstacle_0.png");
	TEXTURE_MGR.Unload("graphics/TurboObstacle_1.png");
	TEXTURE_MGR.Unload("graphics/TurboObstacle_2.png");
	TEXTURE_MGR.Unload("graphics/TurboObstacle_3.png");
=======
	TEXTURE_MGR.Unload("graphics/TurboMap.png");
>>>>>>> Dev.Park
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
	Scene::Exit();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	scoreTimer += dt; //scoreŸ�̸�

	if (scoreTimer >= scoreInterval) // �ֱ��� ������Ʈ
	{
		score += 1; // ���� 10�� ����
		scoreTimer = 0.0f; // Ÿ�̸� ����
	}
	if (!isPause) // �Ͻ����� �κ�
	{
		player.Update(dt);
		timeBar.Update(dt);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev1);
	}
<<<<<<< HEAD

	static float timer = 0.0f;
	timer += dt;
	std::cout << "Timer: " << timer << std::endl;
	if (timer > 2.0f)  // 2�ʸ��� ���ο� ��ֹ� �׷� ����
	{
		std::cout << "Adding new obstacles" << std::endl;
		int numObstacles = ObstaclePool::GetRandomInt(2, 3);  // 2~3���� ��ֹ� Ȱ��ȭ
		for (Obstacle* obstacle : obstaclePool->GetRandomObstacles(numObstacles))
		{
			obstacle->SetActive(true);
			AddGo(obstacle);
			std::cout << "Obstacle added at position: " << obstacle->Getposition().x << ", " << obstacle->Getposition().y << std::endl;
		}
		timer = 0.0f;
	}

	obstaclePool->Update(dt);  // ��� ��ֹ� ������Ʈ
=======
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter)) //����Ű ������ �Ͻ�����
	{
		isPause = !isPause;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape)) //esc ������ ����ȭ�� ����
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev1); 
	}
>>>>>>> Dev.Park
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	obstaclePool->Draw(window);
	Scene::Draw(window);
	player.Draw(window);
	timeBar.Draw(window);

	GameObject* scoreTextObj = dynamic_cast<TextGo*>(GetGameObject("ScoreText")); // ���� ��ü ã��
	if (scoreTextObj)
	{
		scoreTextObj->SetString("Score: " + std::to_string(score)); // ���� ������Ʈ
	}
}
