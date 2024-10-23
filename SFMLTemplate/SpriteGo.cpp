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
        return; // 유효하지 않은 텍스처인 경우 함수 종료
    }

    sprite.setTexture(texture);  // 텍스처 설정
    SetOrigin(originPreset);

    // 스프라이트 크기 확인
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
    if (sprite.getTexture() != nullptr) // 텍스처가 설정된 경우에만 그리기
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
