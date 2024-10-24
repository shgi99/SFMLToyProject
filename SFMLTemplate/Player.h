#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "SpriteGo.h"


class Player : public SpriteGo
{
private:
    float speed; // 이동 속도
public:
    Player(const std::string& texId, const std::string& name = ""); 
    void Reset() override; 
    void Update(float dt); 
    void Draw(sf::RenderWindow& window); 
};