#include "stdafx.h"
#include "timeBar.h"

timeBar::timeBar()
{
	timeBarWidth = 400;
	timeBarHeight = 80;
	totalTime = 5.0f; // 총 시간 설정 (예: 5초)
	elapsedTime = 0.0f; // 초기 경과 시간

	timeBar1.setSize(sf::Vector2f(timeBarWidth, timeBarHeight));
	timeBar1.setFillColor(sf::Color::Red);
	timeBar1.setPosition(10,80);
}

void timeBar::Update(float dt)
{
	// 경과 시간이 총 시간을 넘지 않도록 제한
	elapsedTime += dt;
	if (elapsedTime > totalTime)
	{
		elapsedTime = totalTime; // 경과 시간이 총 시간을 넘지 않게 조정
	}

	// 남은 너비 계산
	float remainingWidth = timeBarWidth * (1.0f - (elapsedTime / totalTime));

	// 남은 너비로 게이지 설정
	timeBar1.setSize(sf::Vector2f(remainingWidth, timeBarHeight));
}


void timeBar::Draw(sf::RenderWindow& window)
{
	window.draw(timeBar1); // 게이지 그리기
}
void timeBar::SetTotalTime(float time)
{
	totalTime = time; // 총 시간을 설정
}

void timeBar::Reset()
{
	elapsedTime = 0.0f; // 경과 시간 초기화
	timeBar1.setSize(sf::Vector2f(timeBarWidth, timeBarHeight)); // 타임바 크기 초기화
	timeBar1.setFillColor(sf::Color::Red); // 색상 초기화

}

void timeBar::AddTime(float time)
{
	// 경과 시간을 줄여서 타임바가 다시 늘어나도록 조정
	elapsedTime -= time;

	// 경과 시간이 0보다 작아지지 않도록 제한
	if (elapsedTime < 0.0f)
	{
		elapsedTime = 0.0f;
	}

	// 타임바의 크기를 업데이트
	float remainingWidth = timeBarWidth * (1.0f - (elapsedTime / totalTime));
	timeBar1.setSize(sf::Vector2f(remainingWidth, timeBarHeight));
}
bool timeBar::IsGameOver() const
{
	return elapsedTime >= totalTime;
}

