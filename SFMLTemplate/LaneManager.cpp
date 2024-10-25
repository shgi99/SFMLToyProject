
#include "stdafx.h"
#include "LaneManager.h"

LaneManager::LaneManager(const std::vector<float>& lanePositions) : lanes(lanePositions)
{
    laneUsed.resize(lanePositions.size(), false);  // ��� ������ ������ �������� �ʱ�ȭ
}

// ��� ������ ������ X ��ǥ ��ȯ, ������ -1 ��ȯ
float LaneManager::GetAvailableLane() const
{
    for (int i = 0; i < laneUsed.size(); ++i)
    {
        if (!laneUsed[i])  // ������ ���� ������ ã���� �� ������ X ��ǥ ��ȯ
        {
            return lanes[i];
        }
    }
    return -1.0f;  // ��� ������ ������ ���� ���
}

// Ư�� ����(X ��ǥ)�� ��� ���θ� ����
void LaneManager::SetLaneUsed(float lane, bool used)
{
    for (int i = 0; i < lanes.size(); ++i)
    {
        if (lanes[i] == lane)  // �ش� X ��ǥ�� ��ġ�ϴ� ���� ã��
        {
            laneUsed[i] = used;  // �ش� ������ ��� ���� ����
            std::cout << "Lane " << lane << " set to " << (used ? "used" : "free") << std::endl;
            return;
        }
    }
}
