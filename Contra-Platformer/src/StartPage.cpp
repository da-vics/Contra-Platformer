#include "includes/StartPage.h"

void StartPage::setUp() {

	this->_mainTitle.setFont(this->_HeaderFont);
	this->_mainTitle.setString("Contra");
	this->_mainTitle.setCharacterSize(45);
	this->_mainTitle.setFillColor(sf::Color::Red);
	this->_mainTitle.setPosition(sf::Vector2f(this->_window->getSize().x / 2.0f - (4.f * 45.f) / 3.f, this->_window->getSize().y / 6.5f));
	this->_mainTitle.setStyle(sf::Text::Bold);

	auto Posx = this->_window->getSize().x / 2.2f - (170.f / 3.5f);
	auto Posy = this->_window->getSize().y / 3.f;

	const auto height = 40.f;
	this->_PlayGameButton.setSize(sf::Vector2f(170.f, height));
	this->_PlayGameButton.setPosition(sf::Vector2f(Posx, Posy));
	this->_PlayGameButton.setFillColor(DarkColor);

	this->_playGameText.setFillColor(sf::Color::White);
	this->_playGameText.setFont(this->_HeaderFont);
	this->_playGameText.setCharacterSize(20);
	this->_playGameText.setString("Play Game");
	auto Framex = Posx + this->_PlayGameButton.getLocalBounds().width / 1.4f - (this->_PlayGameButton.getLocalBounds().width / 2.f);
	auto Framey = Posy + this->_PlayGameButton.getLocalBounds().height / 1.5f - (this->_PlayGameButton.getLocalBounds().height / 2.f);
	this->_playGameText.setPosition(Framex, Framey);


	Posy += 65;
	this->_exitButton.setSize(sf::Vector2f(170.f, height));
	this->_exitButton.setPosition(sf::Vector2f(Posx, Posy));
	this->_exitButton.setFillColor(DarkColor);

	this->_exitButtonText.setFillColor(sf::Color::Red);
	this->_exitButtonText.setFont(this->_HeaderFont);
	this->_exitButtonText.setCharacterSize(20);
	this->_exitButtonText.setString("Quit");
	Framex = Posx + this->_exitButton.getLocalBounds().width / 1.15f - (this->_exitButton.getLocalBounds().width / 2.f);
	Framey = Posy + this->_exitButton.getLocalBounds().height / 1.5f - (this->_exitButton.getLocalBounds().height / 2.f);
	this->_exitButtonText.setPosition(Framex, Framey);
}

void StartPage::Display() {

	this->_window->clear(sf::Color::Black);
	this->_window->draw(this->_bgSprite);
	this->_window->draw(this->_mainTitle);
	this->_window->draw(this->_PlayGameButton);
	this->_window->draw(this->_playGameText);
	this->_window->draw(this->_exitButton);
	this->_window->draw(this->_exitButtonText);

	this->_window->display();
}

void StartPage::OnFocusEvent() {

	if (this->IsMouseOverButton(this->_PlayGameButton)) {

		this->ChangePage = true;
		this->NavTOPage = GamePages::GamePlayPage_P;
	}

	else if (this->IsMouseOverButton(this->_exitButton)) {

		this->_window->close();
	}
}

void StartPage::MouseMoveTigger() {

	if (this->IsMouseOverButton(this->_PlayGameButton)) {

		this->_PlayGameButton.setFillColor(sf::Color::White);
		this->_playGameText.setFillColor(DarkColor);
	}                                                                       //PlayGame Btn	
	else {
		this->_PlayGameButton.setFillColor(DarkColor);
		this->_playGameText.setFillColor(sf::Color::White);
	}

	if (this->IsMouseOverButton(this->_exitButton)) {

		this->_exitButton.setFillColor(sf::Color::White);
		this->_exitButtonText.setFillColor(DarkColor);
	}                                                                       //Exit
	else {
		this->_exitButton.setFillColor(DarkColor);
		this->_exitButtonText.setFillColor(sf::Color::White);
	}
}

void StartPage::HandleEvents(sf::Event* event) {

	if (event->type == sf::Event::MouseButtonPressed)
		this->OnFocusEvent();

	if (event->type == sf::Event::MouseMoved)
		this->MouseMoveTigger();
}