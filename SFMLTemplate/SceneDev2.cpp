#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Obstacle.h"
#include "ObstaclePool.h"
#include "Scene.h"
#include "Player.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{
}

void SceneDev2::Init()
{
	std::cout << "SceneDev2::Init()" << std::endl;

    player = new Player("graphics/TurboPlayer.png");  // 플레이어의 텍스처 파일 경로
    player->SetOrigin(Origins::BC);  // 중심을 원점으로 설정
    player->SetPosition({ 450, 800 });  // 초기 위치 설정
    AddGo(player, "player");  // 게임 오브젝트 목록에 추가


	std::vector<float> lanePositions = { 100.0f, 300.0f, 500.0f, 700.0f };
	std::vector<std::string> obstacleTextures = { "graphics/TurboObstacle_0.png", "graphics/TurboObstacle_1.png", "graphics/TurboObstacle_2.png", "graphics/TurboObstacle_3.png" };
	obstaclePool = new ObstaclePool(obstacleTextures, lanePositions, 500.0f, 10);  // 10개의 장애물을 미리 생성

	for (Obstacle* obstacle : obstaclePool->GetRandomObstacles(3))
	{
		obstacle->SetActive(true);
        obstacle->Reset();
		AddGo(obstacle, "obstacle");
	}
	GameObject* obj = AddGo(new SpriteGo("graphics/TurboMap.png"),"TurboMap");
	obj->SetOrigin(Origins::MC);
	obj->SetPosition({ 900 / 2, 1000 / 2 });



	GameObject* scoreTextObj = AddGo(new TextGo("fonts/KOMIKAP_.ttf"), "ScoreText");
	scoreTextObj->SetOrigin(Origins::TL);
	scoreTextObj->SetPosition({ 0, 20 }); // 점수 위치 설정
	scoreTextObj->SetTextSize(50); // 텍스트 크기 설정
	scoreTextObj->SetString("Score: 0"); // 초기 점수 설정

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
        std::cout << "Failed to load TurboObstacle_3.png" << std::endl;
    }
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
	TEXTURE_MGR.Unload("graphics/TurboMap.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
	Scene::Exit();
}

void SceneDev2::Update(float dt)
{
    if (isPause)
    {
        // 스페이스바를 누르면 게임을 다시 시작
        if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
        {
            isPause = false;  // 게임 재개
        }

        // ESC 키를 누르면 메인 메뉴로 돌아가거나 게임 종료
        if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
        {
            SCENE_MGR.ChangeScene(SceneIds::Dev1);  // 메인 메뉴로 돌아가기
        }

        // 게임이 멈춘 상태에서는 더 이상 업데이트를 하지 않음
        return;
    }

    Scene::Update(dt);

    scoreTimer += dt; // 점수 타이머

    if (scoreTimer >= scoreInterval) // 주기적 업데이트
    {
        score += 1; // 점수 증가
        scoreTimer = 0.0f; // 타이머 리셋
    }

    // 플레이어와 장애물 간의 충돌 체크
    sf::FloatRect playerBounds = player->GetGlobalBound();  // 플레이어 경계 사각형

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
                break;  // 충돌 발생 시 더 이상 확인하지 않음
            }
        }
    }

    // 2초마다 새로운 장애물 그룹 생성
    static float timer = 0.0f;
    timer += dt;
    if (timer > 2.0f)  // 2초마다 새로운 장애물 그룹 생성
    {
        int numObstacles = ObstaclePool::GetRandomInt(2, 3);  // 2~3개의 장애물 활성화
        for (Obstacle* obstacle : obstaclePool->GetRandomObstacles(numObstacles))
        {
            obstacle->SetActive(true);
            AddGo(obstacle, "obstacle");
        }
        timer = 0.0f;
    }

    // 엔터 키를 누르면 일시정지
    if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
    {
        isPause = true;
    }
    player->Update(dt);
    timeBar.Update(dt);
    obstaclePool->Update(dt);
}


void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	obstaclePool->Draw(window);
	player->Draw(window);
	timeBar.Draw(window);

	GameObject* scoreTextObj = dynamic_cast<TextGo*>(GetGameObject("ScoreText")); // 점수 객체 찾기
	if (scoreTextObj)
	{
		scoreTextObj->SetString("Score: " + std::to_string(score)); // 점수 업데이트
	}
}
