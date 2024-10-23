#include "stdafx.h"
#include "ObstaclePool.h"

ObstaclePool::ObstaclePool(const std::vector<std::string>& textures, const std::vector<float>& lanes, float spd, int initialCnt)
	: textureIds(textures), lanePositions(lanes), speed(spd)
{
    for (int i = 0; i < initialCnt; ++i)
    {
        int textureIndex = GetRandomInt(0, textureIds.size() - 1);
        Obstacle* obstacle = new Obstacle(textureIds[textureIndex], lanePositions, speed);
        obstacle->SetActive(false);  // ��Ȱ��ȭ ���·� ����
        obstacles.push_back(obstacle);  // Ǯ�� �߰�
        std::cout << "Obstacle created and added to pool" << std::endl;
    }
}

Obstacle* ObstaclePool::GetInactiveObstacle()
{

    for (auto& obstacle : obstacles)
    {
        if (!obstacle->IsActive())  // ��Ȱ��ȭ�� ��ֹ��� ã��
        {
            obstacle->SetActive(true);  // ��ֹ� Ȱ��ȭ
            obstacle->Reset();  // ��ġ�� �ؽ�ó �缳��
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
        if (obstacle)  // ��Ȱ��ȭ�� ��ֹ��� ã�� ���
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
