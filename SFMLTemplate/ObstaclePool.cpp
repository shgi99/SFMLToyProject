#include "stdafx.h"
#include "ObstaclePool.h"

ObstaclePool::ObstaclePool(const std::vector<std::string>& textures, const std::vector<float>& lanes, float spd, int initialCnt)
	: textureIds(textures), lanePositions(lanes), speed(spd)
{
    for (int i = 0; i < initialCnt; ++i)
    {
        int textureIndex = GetRandomInt(0, textureIds.size() - 1);
        Obstacle* obstacle = new Obstacle(textureIds[textureIndex], lanePositions, speed);
        obstacle->SetActive(false);  // 비활성화 상태로 시작
        obstacles.push_back(obstacle);  // 풀에 추가
        std::cout << "Obstacle created and added to pool" << std::endl;
    }
}

Obstacle* ObstaclePool::GetInactiveObstacle()
{

    for (auto& obstacle : obstacles)
    {
        if (!obstacle->IsActive())  // 비활성화된 장애물을 찾음
        {
            obstacle->SetActive(true);  // 장애물 활성화
            obstacle->Reset();  // 위치와 텍스처 재설정
            std::cout << "Obstacle Activated" << std::endl;
            return obstacle;
        }
    }
    std::cout << "No inactive obstacle found" << std::endl;
	return nullptr;
}

std::vector<Obstacle*> ObstaclePool::GetRandomObstacles(int count)
{
    std::vector<Obstacle*> activeObstacles;

    for (int i = 0; i < count; ++i)
    {
        Obstacle* obstacle = GetInactiveObstacle();
        if (obstacle)  // 비활성화된 장애물을 찾은 경우
        {
            std::cout << "Obstacle found and activated" << std::endl;
            activeObstacles.push_back(obstacle);
        }
        else
        {
            std::cout << "No inactive obstacle found" << std::endl;
        }
    }

	return activeObstacles;
}

void ObstaclePool::Update(float dt)
{
    for (auto& obstacle : obstacles)
    {
        if (obstacle->IsActive())
        {
            obstacle->Update(dt); 
        }
    }
}

void ObstaclePool::Draw(sf::RenderWindow& window)
{
    for (auto& obstacle : obstacles)
    {
        if (obstacle->IsActive())
        {
            obstacle->Draw(window); 
        }
    }
}

int ObstaclePool::GetRandomInt(int min, int max)
{
    static std::random_device rd;
    std::uniform_int_distribution<> dis(min, max);
    return dis(rd);
}
