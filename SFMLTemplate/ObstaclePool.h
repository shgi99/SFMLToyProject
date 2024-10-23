#pragma once
#include "Obstacle.h"
class ObstaclePool
{
private:
    std::vector<Obstacle*> obstacles;  // Ǯ�� �ִ� ��ֹ���
    std::vector<std::string> textureIds;  // �ؽ�ó ���
    std::vector<float> lanePositions;  // ���� ���
    float speed;
    int cnt = 10;
public:
    ObstaclePool() = default;
    ~ObstaclePool() = default;

    ObstaclePool(const std::vector<std::string>& textures, const std::vector<float>& lanes, float spd, int initialCnt);
    Obstacle* GetInactiveObstacle();
    std::vector<Obstacle*> GetRandomObstacles(int count);
    void Update(float dt);
    void Draw(sf::RenderWindow& window);
    static int GetRandomInt(int min, int max);
};

