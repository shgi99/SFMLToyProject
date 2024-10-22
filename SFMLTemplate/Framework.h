#pragma once
class Framework : public Singleton<Framework>
{
	friend Singleton<Framework>;

protected:
	Framework() = default;
	virtual ~Framework() = default;

	Framework(const Framework& other) = delete;
	Framework& operator=(const Framework& other) = delete;

	sf::RenderWindow window;
	sf::Clock clock;

	float timeScale = 1.f;
	float time = 0.f;
	float deltaTime = 0.f;
	float realTime = 0.f;
	float realDeltaTime = 0.f;
public:

	float GetTime() const { return time; }
	float GetDeltaTime() const { return deltaTime; }
	float GetRealTime() const { return realTime; }
	float GetRealDeltaTime() const { return realDeltaTime; }
	
	void SetTimeScale(float newTimeScale) { timeScale = newTimeScale; }
	float GetTimeScale() const { return timeScale; }

	virtual void Init(int width, int height, const std::string& name); // 최초 초기화
	virtual void Do(); // 메인 루프
	virtual void Release(); // 메모리 정리

};
#define FRAMEWORK Framework::Instance()
