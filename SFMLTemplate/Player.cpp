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
    // ���ο� ��ġ ���
    sf::Vector2f newPosition = GetPosition() + direction; // ���� ��ġ�� �̵� ���� �߰�

    // ȭ�� ��� ������ ��ġ ����
    if (newPosition.x < 30)
    {
        newPosition.x = 30; // ���� ��� ����
    }
    else if (newPosition.x > 825.f - getWidth())
    {
        newPosition.x = 825.f - getWidth(); // ������ ��� ����
    }

    if (newPosition.y < 0)
    {
        newPosition.y = 100; // ���� ��� ����
    }
    else if (newPosition.y > 1120.f - getHeight())
    {
        newPosition.y = 1120.f - getHeight(); // �Ʒ��� ��� ����
    }

    SetPosition(newPosition); // ���ѵ� ��ġ�� ����
}

void Player::Draw(sf::RenderWindow& window)
{
    SpriteGo::Draw(window);
    window.draw(sprite); // �÷��̾� �׸���
}

sf::Vector2f Player::GetPosition() const
{
    return sprite.getPosition();
}
