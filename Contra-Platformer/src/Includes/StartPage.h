
#pragma once

#include"BasePageClass.h"

class StartPage : public BasePageClass
{
public:

	StartPage(sf::RenderWindow* window) :BasePageClass(window) {
		this->setUp();
		this->_pageID = "StartPage";
		this->NavTOPage = GamePages::None;
	}

	void Display() override;
	void HandleEvents(sf::Event*) override;

	const sf::Color DarkColor = sf::Color(69, 74, 70);

private:
	void setUp();
	void MouseMoveTigger();
	void OnFocusEvent();
	sf::Text _mainTitle;
	sf::RectangleShape _PlayGameButton;
	sf::RectangleShape _exitButton;
	sf::Text _playGameText;
	sf::Text _exitButtonText;
};