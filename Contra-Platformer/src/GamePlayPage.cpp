#include "Includes/GamePlayPage.h"


void GamePlayPage::setUp() {

	this->mainPlayer = new Player();
}

void GamePlayPage::updatePlayer()
{
	this->mainPlayer->Update();
}

void GamePlayPage::Display() {

	this->_window->clear();

	this->mainPlayer->Render(this->_window);

	this->_window->display();
}

void GamePlayPage::HandleEvents(sf::Event* event) {

	this->updatePlayer();

	if (event->type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) // Go back to startPage
		{
			this->ChangePage = true;
			this->NavTOPage = GamePages::StartPage;
		}
	}
}

GamePlayPage::~GamePlayPage()
{
	delete this->mainPlayer;
}
