#include "stdafx.h"
#include "SceneDev1.h"
#include "SpriteGo.h"
#include "TextGo.h"
SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	std::cout << "SceneDev1::Init()" << std::endl;

	GameObject* obj = AddGo(new SpriteGo("graphics/TurboMain.png"),"Main");
	obj->SetName("MainSprite");
	obj->SetOrigin(Origins::MC);
	obj->SetPosition({ 768 / 2, 1024 / 2 });
	obj->SetScale({ 0.45f,0.5f });



	//GameObject* StartTextObj = AddGo(new TextGo("fonts/KOMIKAP_.ttf"), "StartText");
	//StartTextObj->SetOrigin(Origins::MC);
	//StartTextObj->SetPosition({ 900 / 2, 1000 / 2 }); // 점수 위치 설정
	//StartTextObj->SetTextSize(50); // 텍스트 크기 설정
	//StartTextObj->SetString("Press Space Button to Start!!"); // 초기 점수 설정


	Scene::Init();
}

void SceneDev1::Enter()
{
	std::cout << "SceneDev1::Enter()" << std::endl;
	TEXTURE_MGR.Load("graphics/TurboMain.png");

	Scene::Enter();
}

void SceneDev1::Exit()
{
	std::cout << "SceneDev1::Exit()" << std::endl;
	TEXTURE_MGR.Unload("graphics/TurboMain.png");

	Scene::Exit();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev2);
	}
	
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
