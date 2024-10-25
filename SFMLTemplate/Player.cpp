#include "stdafx.h"
#include "Player.h"


Player::Player(const std::string& texId, const std::string& name)
    : SpriteGo(texId, name), speed(500.f)
{
}

void Player::Reset()
{
    SpriteGo::Reset();
    SetPosition({ 450, 800 });
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
        sprite.move(0, -speed * dt); // 위로 이동 (Y축 감소)
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        sprite.move(0, speed * dt); // 아래로 이동 (Y축 증가)
    }
    // 새로운 위치 계산
    sf::Vector2f newPosition = GetPosition() + direction; // 현재 위치에 이동 방향 추가

    // 화면 경계 내에서 위치 제한
    if (newPosition.x < 150.f - (getWidth() * 0.5f))
    {
        newPosition.x = 150.f - (getWidth() * 0.5f); // 왼쪽 경계 제한
    }
    else if (newPosition.x > 600 + (getWidth() * 0.5f))
    {
        newPosition.x = 600 + (getWidth() * 0.5f); // 오른쪽 경계 제한
    }

    if (newPosition.y < 0 + getHeight())
    {
        newPosition.y = 0 + getHeight(); // 위쪽 경계 제한
    }
    else if (newPosition.y > 1120.f - getHeight())
    {
        newPosition.y = 1120.f - getHeight(); // 아래쪽 경계 제한
    }

    SetPosition(newPosition); // 제한된 위치로 설정
}

void Player::Draw(sf::RenderWindow& window)
{
    SpriteGo::Draw(window);
    window.draw(sprite); // 플레이어 그리기
}

sf::Vector2f Player::GetPosition() const
{
    return sprite.getPosition();
}
