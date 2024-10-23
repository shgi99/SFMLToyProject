#pragma once
#include "Obstacle.h"
class ObstaclePool
{
private:
    std::vector<Obstacle*> obstacles;  // 풀에 있는 장애물들
    std::vector<std::string> textureIds;  // 텍스처 목록
    std::vector<float> lanePositions;  // 차선 목록
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

