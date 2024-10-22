#pragma once
class TextGo : public GameObject
{
protected:
	sf::Text text;
	std::string fontId;
public:
	TextGo() = default;
	~TextGo() = default;

	TextGo(const std::string& fontId, const std::string& name = "");
	void Reset() override;
	void SetPosition(const sf::Vector2f& pos) override;
	void Draw(sf::RenderWindow& window) override;

	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f& newOrigin);
	
	void SetString(const std::string& str = "") override; 
	void SetTextSize(int size);
	void SetTextColor(sf::Color color);
};

