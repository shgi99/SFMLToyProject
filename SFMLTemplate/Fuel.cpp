#include "stdafx.h"
#include "Fuel.h"

Fuel::Fuel(const std::string& texId, const std::string& name, float spd) : SpriteGo(texId, name), speed(spd)
{
}

void Fuel::Reset()
{
	SpriteGo::Reset();

	float randomX = static_cast<float>(rand() % 800 + 100);
    sprite.setScale(2.f, 2.f);
	SetPosition(sf::Vector2f(randomX, -100.0f));  
	SetOrigin(Origins::MC);  
}

void Fuel::Update(float dt)
{
    if (!IsActive()) return;

    // �⸧ �������� �Ʒ��� �̵�
    sf::Vector2f pos = GetPosition();
    pos.y += speed * dt;  
    SetPosition(pos);

    // ȭ���� ����� ��Ȱ��ȭ
    if (pos.y > 950)
    {
        SetActive(false);
    }
}

void Fuel::Draw(sf::RenderWindow& window)
{
    if (IsActive())
    {
        SpriteGo::Draw(window);
    }
}
