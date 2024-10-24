#pragma once
#include <vector>
#include <utility>

class LaneManager
{
private:
    std::vector<float> lanes;  // 차선의 X 좌표
    std::vector<bool> laneUsed;  // 각 차선의 사용 상태
public:
    LaneManager(const std::vector<float>& lanePositions);

    // 사용 가능한 차선의 X 좌표를 반환, 없으면 -1 반환
    float GetAvailableLane() const;

    // 특정 차선(X 좌표)의 사용 여부를 설정
    void SetLaneUsed(float lane, bool used);

};