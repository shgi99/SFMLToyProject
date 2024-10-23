#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "SpriteGo.h"


class Player : public GameObject
{
private:
    sf::Texture texture; // �ؽ�ó ����
    sf::Sprite sprite;   // ��������Ʈ ����   
    float speed;// �̵� �ӵ�
public:
    Player();                        // ������
    void Update(float dt);          // ������Ʈ �޼���
    void Draw(sf::RenderWindow& window); // �׸��� �޼���

};
