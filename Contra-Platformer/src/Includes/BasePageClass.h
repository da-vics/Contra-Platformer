#pragma once

#include<iostream>
#include <SFML/Graphics.hpp>

enum class GamePages
{
	None,
	StartPage,
	GamePlayPage_P,
};

class BasePageClass
{

public:

	BasePageClass(sf::RenderWindow* window) {

		this->_window = window;
		this->Init();
	}

	virtual void Display() {}
	virtual void HandleEvents(sf::Event*) {}

	sf::Texture _bgTexture;
	sf::Sprite _bgSprite;
	sf::Font _HeaderFont;

	std::string _pageID{ " " };
	bool ChangePage{ false };
	GamePages NavTOPage{ GamePages::StartPage };

	sf::RenderWindow* _window = nullptr;

	bool IsMouseOverButton(const sf::RectangleShape&);

	void AlertWindow(sf::Font cFont, std::string AlertMessage, int Wx, int Wy, sf::Color bgcolor = sf::Color(138, 183, 248), sf::Color messageColor = sf::Color::Black);

private:
	void Init();

};