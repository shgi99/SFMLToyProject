#pragma once
#include "Defines.h"
class Utils
{
public:
	// Origin
	static sf::Vector2f SetOrigin(sf::Sprite& obj, Origins preset);
	static sf::Vector2f SetOrigin(sf::Text& obj, Origins preset);
};