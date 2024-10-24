#pragma once
#include "SpriteGo.h"


class Player : public SpriteGo
{
private:
    float speed;// 이동 속도
public:
    Player(const std::string& texId, const std::string& name = ""); // 생성자
    void Reset() override; // 초기화
    void Update(float dt); // 업데이트 메서드
    void Draw(sf::RenderWindow& window); // 그리기 메서드
};
