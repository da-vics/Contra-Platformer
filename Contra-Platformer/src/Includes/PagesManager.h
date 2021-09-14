#pragma once

#include "StartPage.h"
#include"Includes/GamePlayPage.h"


class PagesManager
{

public:

	PagesManager(sf::RenderWindow* window) {

		this->_window = window;
		this->_currentPage = new StartPage(this->_window);
	}

	void HandleEvents(sf::Event*);
	void Display();

private:
	sf::RenderWindow* _window;
	BasePageClass* _currentPage = nullptr;

};