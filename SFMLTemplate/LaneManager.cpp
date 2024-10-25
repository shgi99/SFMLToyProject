
#include "stdafx.h"
#include "LaneManager.h"

LaneManager::LaneManager(const std::vector<float>& lanePositions) : lanes(lanePositions)
{
    laneUsed.resize(lanePositions.size(), false);  // 모든 차선이 사용되지 않음으로 초기화
}

// 사용 가능한 차선의 X 좌표 반환, 없으면 -1 반환
float LaneManager::GetAvailableLane() const
{
    for (int i = 0; i < laneUsed.size(); ++i)
    {
        if (!laneUsed[i])  // 사용되지 않은 차선을 찾으면 그 차선의 X 좌표 반환
        {
            return lanes[i];
        }
    }
    return -1.0f;  // 사용 가능한 차선이 없을 경우
}

// 특정 차선(X 좌표)의 사용 여부를 설정
void LaneManager::SetLaneUsed(float lane, bool used)
{
    for (int i = 0; i < lanes.size(); ++i)
    {
        if (lanes[i] == lane)  // 해당 X 좌표와 일치하는 차선 찾기
        {
            laneUsed[i] = used;  // 해당 차선의 사용 상태 설정
            std::cout << "Lane " << lane << " set to " << (used ? "used" : "free") << std::endl;
            return;
        }
    }
}
