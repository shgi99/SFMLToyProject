#include "stdafx.h"
#include "Player.h"


Player::Player()
{
    // �ؽ�ó �ε�
    if (!texture.loadFromFile("graphics/TurboPlayer.png"))
    {
        // ���� ó��
    }

    sprite.setTexture(texture);
    sprite.setPosition(900 / 2, (1000 / 2) + 270); // �ʱ� ��ġ ����
    speed = 500.0f; // �̵� �ӵ� ����
}

void Player::Update(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        sprite.move(-speed * dt, 0); // �������� �̵�
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        sprite.move(speed * dt, 0); // ���������� �̵�
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        sprite.move(0, -speed * dt); // ���� �̵� (Y�� ����)
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        sprite.move(0, speed * dt); // �Ʒ��� �̵� (Y�� ����)
    }
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(sprite); // �÷��̾� �׸���
}
