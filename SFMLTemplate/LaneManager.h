#pragma once
#include <vector>
#include <utility>

class LaneManager
{
private:
    std::vector<float> lanes;  // ������ X ��ǥ
    std::vector<bool> laneUsed;  // �� ������ ��� ����
public:
    LaneManager(const std::vector<float>& lanePositions);

    // ��� ������ ������ X ��ǥ�� ��ȯ, ������ -1 ��ȯ
    float GetAvailableLane() const;

    // Ư�� ����(X ��ǥ)�� ��� ���θ� ����
    void SetLaneUsed(float lane, bool used);

};