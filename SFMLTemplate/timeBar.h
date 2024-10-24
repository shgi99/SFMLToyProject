#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class timeBar : public GameObject
{
protected:
	sf::RectangleShape timeBar1;
	float timeBarWidth;
	float timeBarHeight;
	float totalTime; // 전체 시간
	float elapsedTime; // 경과 시간
public:

	timeBar();                      
	void Update(float dt);        
	void Draw(sf::RenderWindow& window); 

	void SetTotalTime(float time); // 총 시간을 설정하는 메서드
	void Reset();
};

