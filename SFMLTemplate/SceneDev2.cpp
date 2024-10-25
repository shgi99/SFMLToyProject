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
	player->SetOrigin(Origins::BC);  // 중심을 원점으로 설정
	player->SetPosition({ 768 / 2, 1024 / 2 });  // 초기 위치 설정
	AddGo(player, "player");  // 게임 오브젝트 목록에 추가

	std::vector<float> lanePositions = { 150.0f, 300.0f, 450.0f, 600.0f };
	laneManager = new LaneManager(lanePositions);

	std::vector<std::string> obstacleTextures = { "graphics/TurboObstacle_0.png", "graphics/TurboObstacle_1.png", "graphics/TurboObstacle_2.png", "graphics/TurboObstacle_3.png" };
	obstaclePool = new ObstaclePool(obstacleTextures, lanePositions, 500.0f, 10);  // 10개의 장애물을 미리 생성

	fuelItem = new Fuel("graphics/TurboFuel.png", "fuel", 500.f);
	fuelItem->SetActive(false);
	fuelItem->SetOrigin(Origins::MC);
	AddGo(fuelItem, "fuelItem");


	// 플레이어 초기화
	player->Reset(); 

	// timeBar 초기화
	timeBar.SetTotalTime(5.0f); // 총 시간을 설정하는 예시

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
	mapObject = dynamic_cast<SpriteGo*>(AddGo(new SpriteGo("graphics/TurboMap.png"), "TurboMap")); // mapObject 초기화
	if (mapObject)
	{
		mapObject->SetOrigin(Origins::MC);
		mapObject->SetPosition({ 768 / 2, 1024 / 2 });
		mapObject->SetScale({ 0.7f, 2.0f });
	}

	GameObject* scoreTextObj = AddGo(new TextGo("fonts/KOMIKAP_.ttf"), "ScoreText");
	scoreTextObj->SetOrigin(Origins::TL);
	scoreTextObj->SetPosition({ 0, 20 }); // 점수 위치 설정
	scoreTextObj->SetTextSize(50); // 텍스트 크기 설정
	scoreTextObj->SetString("Score: 0"); // 초기 점수 설정

	GameObject* PauseTextObj = AddGo(new TextGo("fonts/KOMIKAP_.ttf"), "PauseText");
	PauseTextObj->SetOrigin(Origins::MC);
	PauseTextObj->SetPosition({ 768 / 2, 1024 / 2 }); // 점수 위치 설정
	PauseTextObj->SetTextSize(50); // 텍스트 크기 설정
	PauseTextObj->SetString("Press Enter to Start!!"); // 초기 점수 설정
	PauseTextObj->SetActive(false); // 초기 상태에서 비활성화


	GameObject* gameOverTextObj = AddGo(new TextGo("fonts/KOMIKAP_.ttf"), "gameOverText");
	gameOverTextObj->SetOrigin(Origins::MC);
	gameOverTextObj->SetPosition({ 768 / 2, 1024 / 2 }); // 점수 위치 설정
	gameOverTextObj->SetTextSize(50); // 텍스트 크기 설정
	gameOverTextObj->SetString("Game Over..."); // 초기 점수 설정
	gameOverTextObj->SetActive(false); // 초기 상태에서 비활성화

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

	// 플레이어 초기화
	player->Reset(); 

	// 타이머 초기화
	score = 0;
	scoreTimer = 0.0f;

	// timeBar 초기화
	timeBar.Reset(); 

	// 장애물 풀 초기화
	obstaclePool->Reset(); 

	// 장애물 비활성화
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
		isGameOver = true; // 게임 오버 상태로 설정
		isPause = true; // 게임을 멈춤

		// ESC 키를 누르면 메인 메뉴로 돌아가기
		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			SCENE_MGR.ChangeScene(SceneIds::Dev1);  // 메인 메뉴로 돌아가기
			Reset();  // 게임 상태 초기화
			return; // 추가적인 업데이트를 하지 않음
		}
	}

    if (isPause)
    {
		// ESC 키를 누르면 메인 메뉴로 돌아가기
		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			SCENE_MGR.ChangeScene(SceneIds::Dev1);  // 메인 메뉴로 돌아가기
			Reset();  // 게임 상태 초기화
			return; // 추가적인 업데이트를 하지 않음
		}

        // 스페이스바를 누르면 게임을 다시 시작
        if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
        {
            isPause = false;  // 게임 재개
        }

		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			Reset();  // 게임 상태 초기화
			isGameOver = false;  // 게임 오버 해제
			isPause = false;  // 일시정지 해제
			return;
		}
		return;
	
    }

	// UV 오프셋 업데이트
	uvOffset -= 1500 * dt;  // UV 이동 속도 조절

	if (mapObject && mapObject->GetTexture())
	{
		auto textureSize = mapObject->GetTexture()->getSize(); // 텍스처 크기 가져오기
		int height = textureSize.y;

		// 리셋 주기 설정 (2초)
		float resetInterval = 0.2f; // 리셋 주기 (초)
		static float elapsedTime = 0.0f; // 경과 시간

		elapsedTime += dt; // 프레임마다 시간 추가

		if (isGameOver)  // 게임 오버 상태 체크
		{
			// 엔터 키를 누르면 메인 메뉴로 돌아가기
			if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
			{
				SCENE_MGR.ChangeScene(SceneIds::Dev1);  // 메인 메뉴로 돌아가기
				Reset();  // 게임 상태 초기화
			}
			return; // 게임 오버 상태에서는 다른 업데이트를 하지 않음
		}

		// UV 오프셋이 텍스처 높이보다 작아지면 위치를 리셋
		if (uvOffset <= -height || elapsedTime >= resetInterval)
		{
			uvOffset = 0; // 오프셋을 0으로 리셋
			elapsedTime = 0.0f; // 경과 시간 초기화

			// 맵의 Y 위치를 동적으로 조정
			float newYPosition = 1024 / 2; // 기본 위치 (조정 필요)
			mapObject->SetPosition({ static_cast<float>(768) / 2, newYPosition });
		}

		// 텍스처에 UV 애니메이션 적용
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

     // 장애물과 플레이어 충돌 여부 확인
    for (GameObject* obj : obstacleList)
    {
        Obstacle* obstacle = dynamic_cast<Obstacle*>(obj);
        if (obstacle && obstacle->IsActive())  // 활성화된 장애물만 체크
        {
            sf::FloatRect obstacleBounds = obstacle->GetGlobalBound();
            if (playerBounds.intersects(obstacleBounds))  // 충돌 발생 시
            {
                isPause = true;  // 게임을 멈춤
				isGameOver = true;
                break;  // 충돌 발생 시 더 이상 확인하지 않음
            }
        }
    }

	// 장애물이 화면 밖으로 나가면 비활성화하고 차선 해제
	for (GameObject* obj : obstacleList)
	{
		Obstacle* obstacle = dynamic_cast<Obstacle*>(obj);
		if (obstacle && obstacle->IsActive())
		{
			sf::Vector2f pos = obstacle->GetPosition();
			if (pos.y > 1100)
			{
				obstacle->SetActive(false);
				laneManager->SetLaneUsed(pos.x, false);  // 차선 해제
			}
		}
	}

	// 장애물 생성
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


	// 기름 아이템 생성
	fuelSpawnTimer += dt;
	if (!fuelItem->IsActive() && fuelSpawnTimer > fuelSpawnInterval)
	{
		fuelSpawnTimer = 0.0f;

		// 기름 아이템이 장애물과 겹치지 않도록 차선을 선택
		float lane = laneManager->GetAvailableLane();
		bool laneOccupied = false;

		// 장애물과 겹치지 않는 차선만 선택
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

	// 플레이어가 기름 아이템과 충돌했을 때
	if (fuelItem->IsActive() && playerBounds.intersects(fuelItem->GetGlobalBound()))
	{
		fuelItem->SetActive(false);
		timeBar.AddTime(10.0f);  // 타임바에 시간 추가
		laneManager->SetLaneUsed(fuelItem->GetPosition().x, false);  // 차선 해제
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

	GameObject* scoreTextObj = dynamic_cast<TextGo*>(GetGameObject("ScoreText")); // 점수 객체 찾기
	if (scoreTextObj)
	{
		scoreTextObj->SetString("Score: " + std::to_string(score)); // 점수 업데이트
	}
	
	if (isPause && !isGameOver)
	{
		GameObject* PauseTextObj = dynamic_cast<TextGo*>(GetGameObject("PauseText"));
		if (PauseTextObj)
		{
			PauseTextObj->Draw(window); // PauseText 그리기
		}
	}

	// 게임 오버 텍스트 그리기
	if (isGameOver)
	{
		GameObject* gameOverTextObj = dynamic_cast<TextGo*>(GetGameObject("gameOverText"));
		if (gameOverTextObj)
		{
			gameOverTextObj->Draw(window); // Game Over 메시지 그리기
		}
	}
}
