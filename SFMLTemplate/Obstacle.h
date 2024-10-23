#pragma once
#include "SpriteGo.h"
#include <random>
class Obstacle : public SpriteGo
{
protected:
	float speed;
	std::vector<float> lanePositions;
public:
	Obstacle();
	Obstacle(const std::string& texId, const std::vector<float>& lanes, float spd, const std::string& name = "");
	~Obstacle();
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

