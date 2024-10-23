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
	scoreTextObj->SetPosition({ 0, 20 }); // ���� ��ġ ����
	scoreTextObj->SetTextSize(50); // �ؽ�Ʈ ũ�� ����
	scoreTextObj->SetString("Score: 0"); // �ʱ� ���� ����

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
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter)) //����Ű ������ �Ͻ�����
	{
		isPause = !isPause;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape)) //esc ������ ����ȭ�� ����
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev1); 
	}
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	player.Draw(window);
	timeBar.Draw(window);

	GameObject* scoreTextObj = dynamic_cast<TextGo*>(GetGameObject("ScoreText")); // ���� ��ü ã��
	if (scoreTextObj)
	{
		scoreTextObj->SetString("Score: " + std::to_string(score)); // ���� ������Ʈ
	}
}
