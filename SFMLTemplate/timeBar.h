#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class timeBar : public GameObject
{
protected:
	sf::RectangleShape timeBar1;
	float timeBarWidth;
	float timeBarHeight;
	float totalTime; // ��ü �ð�
	float elapsedTime; // ��� �ð�
public:

	timeBar();                      
	void Update(float dt);        
	void Draw(sf::RenderWindow& window); 

	void SetTotalTime(float time); // �� �ð��� �����ϴ� �޼���
	void Reset();
};

