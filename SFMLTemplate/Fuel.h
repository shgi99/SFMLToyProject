#pragma once
#include "SpriteGo.h"

class Fuel : public SpriteGo
{
    float speed;
    int laneIndex;
public:
    Fuel(const std::string& texId, const std::string& name = "", float spd = 300.f);

    void SetLaneIndex(int index) { laneIndex = index; }
    int GetLaneIndex() const { return laneIndex; }

    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
};
