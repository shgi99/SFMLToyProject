#include "stdafx.h"
#include "SpriteGo.h"

SpriteGo::SpriteGo(const std::string& texId, const std::string& name) 
	:GameObject(name), textureId(texId)
{

}

void SpriteGo::Reset()
{
    sf::Texture& texture = TEXTURE_MGR.Get(textureId);
    if (texture.getSize().x == 0 || texture.getSize().y == 0)
    {
        std::cout << "Texture not found or invalid size: " << textureId << std::endl;
        return; // ��ȿ���� ���� �ؽ�ó�� ��� �Լ� ����
    }

    sprite.setTexture(texture);  // �ؽ�ó ����
    SetOrigin(originPreset);

    // ��������Ʈ ũ�� Ȯ��
    sf::FloatRect bounds = sprite.getGlobalBounds();
    std::cout << "Sprite size after setting texture: " << bounds.width << "x" << bounds.height << std::endl;
}


void SpriteGo::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void SpriteGo::Draw(sf::RenderWindow& window)
{
    if (sprite.getTexture() != nullptr) // �ؽ�ó�� ������ ��쿡�� �׸���
    {
        window.draw(sprite);
        std::cout << "Drawing sprite at position: " << sprite.getPosition().x << ", " << sprite.getPosition().y << std::endl;
    }
    else
    {
        std::cout << "Sprite has no texture" << std::endl;
    }
}

void SpriteGo::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(sprite, originPreset);
}

void SpriteGo::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	sprite.setOrigin(origin);
}
