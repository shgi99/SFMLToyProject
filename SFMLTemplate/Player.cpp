#include "stdafx.h"
#include "Player.h"

Player::Player(const std::string & texId, const std::string & name)
    : SpriteGo(texId, name), speed(500.f)
{
}

void Player::Reset()
{
    SpriteGo::Reset();
    SetPosition(sf::Vector2f(400, 600));
}

void Player::Update(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        sprite.move(-speed * dt, 0); // 왼쪽으로 이동
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        sprite.move(speed * dt, 0); // 오른쪽으로 이동
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        sprite.move(0, -speed * dt); // 위로 이동 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        sprite.move(0, speed * dt); // 아래로 이동 
    }
}

void Player::Draw(sf::RenderWindow& window)
{
    SpriteGo::Draw(window);
    window.draw(sprite); // 플레이어 그리기
}

