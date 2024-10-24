#pragma once
#include "stdafx.h"
class SpriteGo : public GameObject
{
protected:
	sf::Sprite sprite;
	std::string textureId;
public:
	SpriteGo(const std::string& texId, const std::string& name = "");
	~SpriteGo() = default;

	sf::FloatRect GetGlobalBound() const
	{
		return sprite.getGlobalBounds();
	}

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& Scale) override;
	void Draw(sf::RenderWindow& window) override;

	void Reset() override;
	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f& newOrigin);

	const sf::Texture* GetTexture() const
	{
		return sprite.getTexture();
	}
	void SetTextureRect(const sf::IntRect& rect)
	{
		sprite.setTextureRect(rect);
	}
	float getWidth() const; // 너비 가져오기 메서드 선언
	float getHeight() const; // 높이 가져오기 메서드 선언

};

