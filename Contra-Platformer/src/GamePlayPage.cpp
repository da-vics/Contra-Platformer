#include "Includes/GamePlayPage.h"

void GamePlayPage::setUp()
{
	this->mainPlayer = new Player();
	this->mainPlayer->SetPosition(0, this->_window->getSize().y - this->mainPlayer->GetPosition().y);


	if (!this->_bgTexture.loadFromFile("Assets/Images/Cloud.png")) {
		std::cout << "Error Loading Assets/Images/Cloud.png" << std::endl;
		std::cout << "Shutting Down!" << std::endl;
		this->_window->close();
	}


	if (!this->PlatformTexture.loadFromFile("Assets/Images/Platform1.png")) {
		std::cout << "Error Loading Assets/Images/Platform1.png" << std::endl;
		std::cout << "Shutting Down!" << std::endl;
		this->_window->close();
	}

	sf::Sprite tempSprite;

	tempSprite.setTexture(this->PlatformTexture);
	tempSprite.setTextureRect(sf::IntRect(86, 349, 426, 82));
	tempSprite.setPosition(10, 400);
	this->PlatoformSprites.push_back(tempSprite);

	tempSprite.setTextureRect(sf::IntRect(445, 244, 61, 96));
	tempSprite.setPosition(400, this->_window->getSize().y - tempSprite.getGlobalBounds().height);
	this->PlatoformSprites.push_back(tempSprite);

	tempSprite.setTextureRect(sf::IntRect(83, 265, 331, 83));
	tempSprite.setPosition(500, 200);
	this->PlatoformSprites.push_back(tempSprite);


	auto textureSize = this->_bgTexture.getSize();
	auto WindowSize = this->_window->getSize();

	auto ScaleX = (float)WindowSize.x / textureSize.x;
	auto ScaleY = (float)WindowSize.y / textureSize.y;

	this->_bgSprite.setTexture(this->_bgTexture);
	this->_bgSprite.setScale(ScaleX, ScaleY);
}

void GamePlayPage::updatePlayer()
{
	this->mainPlayer->Update(this->_window->getSize().x, this->_window->getSize().y);
	this->CheckCollision();
}

void GamePlayPage::CheckCollision()
{
	if (this->mainPlayer->GetPosition().y + this->mainPlayer->GetGlobalBounds().height > this->_window->getSize().y)
	{
		this->mainPlayer->ResetVelocityY();
		this->mainPlayer->SetPosition(this->mainPlayer->GetPosition().x, this->_window->getSize().y - this->mainPlayer->GetGlobalBounds().height);
	}

	auto begin = this->mainPlayer->BulletsSprites.begin();
	auto end = this->mainPlayer->BulletsSprites.end();

	for (auto iterator = begin; iterator != end;++iterator)
	{
		auto tempStruct = iterator->sprite;
		auto tempBulletSprite = tempStruct;
		if (tempBulletSprite.getPosition().x < 0 || tempBulletSprite.getPosition().x > this->_window->getSize().x)
		{
			this->mainPlayer->BulletsSprites.erase(iterator);
			std::cout << mainPlayer->BulletsSprites.size() << std::endl;
			break;
		}

	}
}

void GamePlayPage::Display()
{
	this->_window->clear();

	this->_window->draw(this->_bgSprite);

	for (auto sprite : this->PlatoformSprites)
		this->_window->draw(sprite);

	this->mainPlayer->Render(this->_window);

	this->_window->display();

	this->updatePlayer();
}

void GamePlayPage::HandleEvents(sf::Event* event)
{
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
