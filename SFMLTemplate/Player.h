#pragma once
#include "SpriteGo.h"


class Player : public SpriteGo
{
private:
    float speed;// �̵� �ӵ�
public:
    Player(const std::string& texId, const std::string& name = ""); // ������
    void Reset() override; // �ʱ�ȭ
    void Update(float dt); // ������Ʈ �޼���
    void Draw(sf::RenderWindow& window); // �׸��� �޼���
};
