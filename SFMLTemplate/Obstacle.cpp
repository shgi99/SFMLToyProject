#include "stdafx.h"
#include "Obstacle.h"

Obstacle::Obstacle()
{
}

Obstacle::Obstacle(const std::string& texId, const std::vector<float>& lanes, float spd, const std::string& name)
	: SpriteGo(texId ,name), speed(spd), lanePositions(lanes)
{
	Reset();
}

Obstacle::~Obstacle()
{
}

void Obstacle::Reset()
{
	SpriteGo::Reset();

	// �ؽ�ó�� �����Ƿ� ��������Ʈ ũ�⸦ Ȯ��
	sprite.setScale(2.0f, 2.0f);  // ���� 2��, ���� 2��� Ȯ��

	// ���� ���� ����
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(lanePositions.begin(), lanePositions.end(), g);
	float randomX = lanePositions[0];

	// ��ġ�� ���� ����
	SetPosition(sf::Vector2f(randomX, -50.0f));
	SetOrigin(Origins::MC);
}


void Obstacle::Update(float dt)
{
	if (!IsActive())
	{
		return;
	}

	sf::Vector2f pos = Getposition();
	pos.y += speed * dt;
	SetPosition(pos);

	if (pos.y > 1000)
	{
		SetActive(false);
	}
}

void Obstacle::Draw(sf::RenderWindow& window)
{
	if (IsActive())    
	{
		std::cout << "Obstacle Size: " << sprite.getGlobalBounds().width << "x" << sprite.getGlobalBounds().height << std::endl;
		SpriteGo::Draw(window);
	}
}

