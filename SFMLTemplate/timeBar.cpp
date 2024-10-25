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
	// ��� �ð��� �� �ð��� ���� �ʵ��� ����
	elapsedTime += dt;
	if (elapsedTime > totalTime)
	{
		elapsedTime = totalTime; // ��� �ð��� �� �ð��� ���� �ʰ� ����
	}

	// ���� �ʺ� ���
	float remainingWidth = timeBarWidth * (1.0f - (elapsedTime / totalTime));

	// ���� �ʺ�� ������ ����
	timeBar1.setSize(sf::Vector2f(remainingWidth, timeBarHeight));
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

void timeBar::AddTime(float time)
{
	// ��� �ð��� �ٿ��� Ÿ�ӹٰ� �ٽ� �þ���� ����
	elapsedTime -= time;

	// ��� �ð��� 0���� �۾����� �ʵ��� ����
	if (elapsedTime < 0.0f)
	{
		elapsedTime = 0.0f;
	}

	// Ÿ�ӹ��� ũ�⸦ ������Ʈ
	float remainingWidth = timeBarWidth * (1.0f - (elapsedTime / totalTime));
	timeBar1.setSize(sf::Vector2f(remainingWidth, timeBarHeight));
}
bool timeBar::IsGameOver() const
{
	return elapsedTime >= totalTime;
}

