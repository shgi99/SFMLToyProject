#include "stdafx.h"
#include "Obstacle.h"


Obstacle::Obstacle(const std::string& texId, const std::vector<float>& lanes, float spd, const std::string& name)
	: SpriteGo(texId ,name), speed(spd), lanePositions(lanes)
{
	
}

Obstacle::~Obstacle()
{
}

void Obstacle::Reset()
{
	SpriteGo::Reset();

	// 텍스처가 작으므로 스프라이트 크기를 확장
	sprite.setScale(2.0f, 2.0f);  // 가로 2배, 세로 2배로 확대

	// 랜덤 차선 선택
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(lanePositions.begin(), lanePositions.end(), g);
	float randomX = lanePositions[0];
	float randomY = -(rand() % 200 - 100);
	// 위치와 원점 설정

	SetPosition(sf::Vector2f(randomX, randomY));
	SetOrigin(Origins::MC);
}


void Obstacle::Update(float dt)
{
	if (!IsActive())
	{
		return;
	}

	sf::Vector2f pos = GetPosition();
	pos.y += speed * dt;
	SetPosition(pos);

	
}

void Obstacle::Draw(sf::RenderWindow& window)
{
	if (IsActive())    
	{
		SpriteGo::Draw(window);
	}
}

