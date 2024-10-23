#include "stdafx.h"
#include "Player.h"


Player::Player()
{
    // 텍스처 로드
    if (!texture.loadFromFile("graphics/TurboPlayer.png"))
    {
        // 에러 처리
    }

    sprite.setTexture(texture);
    sprite.setPosition(900 / 2, (1000 / 2) + 270); // 초기 위치 설정
    speed = 500.0f; // 이동 속도 설정
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
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(sprite); // 플레이어 그리기
}
