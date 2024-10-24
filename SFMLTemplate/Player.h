#pragma once
#include "SpriteGo.h"


class Player : public SpriteGo
{
private:
    float speed; // �̵� �ӵ�
    sf::Vector2f direction;
public:
    Player(const std::string& texId, const std::string& name = ""); 
    void Reset() override; 
    void Update(float dt) override; 
    void Draw(sf::RenderWindow& window) override; 
    sf::Vector2f GetPosition() const;
};
