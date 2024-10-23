#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "SpriteGo.h"


class Player : public GameObject
{
private:
    sf::Texture texture; // 텍스처 변수
    sf::Sprite sprite;   // 스프라이트 변수   
    float speed;// 이동 속도
public:
    Player();                        // 생성자
    void Update(float dt);          // 업데이트 메서드
    void Draw(sf::RenderWindow& window); // 그리기 메서드

};
