#include "stdafx.h"
#include "timeBar.h"

timeBar::timeBar()
{
	timeBarWidth = 400;
	timeBarHeight = 80;
	totalTime = 5.0f; // �� �ð� ���� (��: 5��)
	elapsedTime = 0.0f; // �ʱ� ��� �ð�

	timeBar1.setSize(sf::Vector2f(timeBarWidth, timeBarHeight));
	timeBar1.setFillColor(sf::Color::Red);
	timeBar1.setPosition(10,80);
}

void timeBar::Update(float dt)
{
	if (elapsedTime < totalTime)
	{
		elapsedTime += dt; // ��� �ð� ������Ʈ
		float remainingWidth = timeBarWidth * (1.0f - (elapsedTime / totalTime)); // ���� �ʺ� ���
		timeBar1.setSize(sf::Vector2f(remainingWidth, timeBarHeight)); // ���� �ʺ�� ������ ����
	}

}

void timeBar::Draw(sf::RenderWindow& window)
{
	window.draw(timeBar1); // ������ �׸���
}
void timeBar::SetTotalTime(float time)
{
	totalTime = time; // �� �ð��� ����
}

void timeBar::Reset()
{
	elapsedTime = 0.0f; // ��� �ð� �ʱ�ȭ
	timeBar1.setSize(sf::Vector2f(timeBarWidth, timeBarHeight)); // Ÿ�ӹ� ũ�� �ʱ�ȭ
	timeBar1.setFillColor(sf::Color::Red); // ���� �ʱ�ȭ

}
