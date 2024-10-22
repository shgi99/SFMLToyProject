#include "stdafx.h"

std::list<sf::Keyboard::Key> InputMgr::downKeyList;
std::list<sf::Keyboard::Key> InputMgr::upKeyList;
std::list<sf::Keyboard::Key> InputMgr::heldKeyList;

std::list<sf::Mouse::Button> InputMgr::downMouseList;
std::list<sf::Mouse::Button> InputMgr::upMouseList;
std::list<sf::Mouse::Button> InputMgr::heldMouseList;

void InputMgr::Clear()
{
	downKeyList.clear();
	upKeyList.clear();
	downMouseList.clear();
	upMouseList.clear();
}

void InputMgr::UpdateEvent(sf::Event ev)
{
	switch (ev.type)
	{
	case sf::Event::KeyPressed:
		if (std::find(heldKeyList.begin(), heldKeyList.end(), ev.key.code) == heldKeyList.end())
		{
			heldKeyList.push_back(ev.key.code);
			downKeyList.push_back(ev.key.code);
		}
		break;
	case sf::Event::KeyReleased:
		upKeyList.push_back(ev.key.code);
		heldKeyList.remove(ev.key.code);
		break;
	case sf::Event::MouseButtonPressed:
		if (std::find(heldMouseList.begin(), heldMouseList.end(), ev.mouseButton.button) == heldMouseList.end())
		{
			heldMouseList.push_back(ev.mouseButton.button);
			downMouseList.push_back(ev.mouseButton.button);
		}
		break;
	case sf::Event::MouseButtonReleased:
		upMouseList.push_back(ev.mouseButton.button);
		heldMouseList.remove(ev.mouseButton.button);
		break;
	}
}

bool InputMgr::GetKeyDown(sf::Keyboard::Key key)
{
	return std::find(downKeyList.begin(), downKeyList.end(), key) != downKeyList.end();
}

bool InputMgr::GetKey(sf::Keyboard::Key key)
{
	return std::find(heldKeyList.begin(), heldKeyList.end(), key) != heldKeyList.end();
}

bool InputMgr::GetKeyUp(sf::Keyboard::Key key)
{
	return std::find(upKeyList.begin(), upKeyList.end(), key) != upKeyList.end();
}

bool InputMgr::GetMouseDown(sf::Mouse::Button button)
{
	return std::find(downMouseList.begin(), downMouseList.end(), button) != downMouseList.end();
}

bool InputMgr::GetMouse(sf::Mouse::Button button)
{
	return std::find(heldMouseList.begin(), heldMouseList.end(), button) != heldMouseList.end();
}

bool InputMgr::GetMouseUp(sf::Mouse::Button button)
{
	return std::find(upMouseList.begin(), upMouseList.end(), button) != upMouseList.end();
}

sf::Vector2i InputMgr::GetMousePoint(const sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}

