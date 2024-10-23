#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Scene.h"



SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{
}

void SceneDev2::Init()
{
	std::cout << "SceneDev2::Init()" << std::endl;

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
	TEXTURE_MGR.Load("graphics/TurboMap.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");

	Scene::Enter();
}

void SceneDev2::Exit()
{
	std::cout << "SceneDev2::Exit()" << std::endl;
	TEXTURE_MGR.Unload("graphics/TurboMap.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
	Scene::Exit();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	scoreTimer += dt; //score타이머

	if (scoreTimer >= scoreInterval) // 주기적 업데이트
	{
		score += 1; // 점수 10점 증가
		scoreTimer = 0.0f; // 타이머 리셋
	}
	if (!isPause) // 일시정지 부분
	{
		player.Update(dt);
		timeBar.Update(dt);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev1);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter)) //엔터키 누르면 일시정지
	{
		isPause = !isPause;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape)) //esc 누르면 메인화면 복귀
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev1); 
	}
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	player.Draw(window);
	timeBar.Draw(window);

	GameObject* scoreTextObj = dynamic_cast<TextGo*>(GetGameObject("ScoreText")); // 점수 객체 찾기
	if (scoreTextObj)
	{
		scoreTextObj->SetString("Score: " + std::to_string(score)); // 점수 업데이트
	}
}
