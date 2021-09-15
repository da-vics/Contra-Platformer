#include "Includes/GamePlayPage.h"


void GamePlayPage::setUp() {

	this->mainPlayer = new Player();
	this->mainPlayer->SetPosition(0, this->_window->getSize().y - this->mainPlayer->GetPosition().y);
}

void GamePlayPage::updatePlayer()
{
	this->mainPlayer->Update();
	this->CheckCollision();
}

void GamePlayPage::CheckCollision()
{
	if (this->mainPlayer->GetPosition().y + this->mainPlayer->GetGlobalBounds().height > this->_window->getSize().y)
	{
		this->mainPlayer->ResetVelocityY();
		this->mainPlayer->SetPosition(this->mainPlayer->GetPosition().x, this->_window->getSize().y - this->mainPlayer->GetGlobalBounds().height);
	}
}

void GamePlayPage::Display() {

	this->_window->clear();

	this->mainPlayer->Render(this->_window);

	this->_window->display();

	this->updatePlayer();
}

void GamePlayPage::HandleEvents(sf::Event* event) {

	if (event->type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) // Go back to startPage
		{
			this->ChangePage = true;
			this->NavTOPage = GamePages::StartPage;
		}
	}

	if (event->type == sf::Event::KeyReleased && (
		event->key.code == sf::Keyboard::A ||
		event->key.code == sf::Keyboard::D ||
		event->key.code == sf::Keyboard::W ||
		event->key.code == sf::Keyboard::S))
	{
		this->mainPlayer->ResetAnimationTimer();
	}
}

GamePlayPage::~GamePlayPage()
{
	delete this->mainPlayer;
}
