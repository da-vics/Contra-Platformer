#include "Includes/GamePlayPage.h"
#include <string>

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

	this->Score.setFont(this->_HeaderFont);
	this->Score.setPosition(5, 10);
	this->Score.setCharacterSize(15);
	this->Score.setString("Score: " + std::to_string(this->score));
	this->Score.setStyle(sf::Text::Bold);
	this->Score.setFillColor(sf::Color(18, 20, 128));

	this->Hp.setFont(this->_HeaderFont);
	this->Hp.setPosition(5, 35);
	this->Hp.setCharacterSize(15);
	this->Hp.setString("HP: ");
	this->Hp.setStyle(sf::Text::Bold);
	this->Hp.setFillColor(HpColor);

	this->HealthBar.setPosition(35, 35);
	this->HealthBar.setSize(sf::Vector2f(this->mainPlayer->Health * 2.f, 20.f));
	this->HealthBar.setFillColor(HpColor);

	sf::Sprite tempSprite;

	tempSprite.setTexture(this->PlatformTexture);
	tempSprite.setTextureRect(sf::IntRect(86, 349, 426, 82));
	tempSprite.setPosition(5, 430);
	this->PlatoformSprites.push_back(tempSprite);

	tempSprite.setTextureRect(sf::IntRect(445, 244, 61, 96));
	tempSprite.setPosition(450, this->_window->getSize().y - tempSprite.getGlobalBounds().height);
	this->PlatoformSprites.push_back(tempSprite);

	tempSprite.setTextureRect(sf::IntRect(83, 265, 331, 83));
	tempSprite.setPosition(500, 300);
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

	if (this->mainPlayer->onGround == false)
	{
		this->mainPlayer->velocity.y += this->mainPlayer->gravity * 250.f;
		if (this->mainPlayer->velocity.y > this->mainPlayer->velocityMaxY)
			this->mainPlayer->velocity.y = this->mainPlayer->velocityMaxY;
	}




	if (this->mainPlayer->GetPosition().x >= this->PlatoformSprites[0].getPosition().x and
		this->mainPlayer->GetPosition().x <= this->PlatoformSprites[0].getPosition().x + this->PlatoformSprites[0].getGlobalBounds().width and
		(int)this->mainPlayer->GetPosition().y == (int)this->PlatoformSprites[0].getPosition().y + this->PlatoformSprites[0].getGlobalBounds().height)
	{
		this->mainPlayer->canJump = false;
	}

	else
		this->mainPlayer->canJump = true;


	if (this->mainPlayer->GetPosition().y + this->mainPlayer->GetGlobalBounds().height > this->_window->getSize().y)
	{
		this->mainPlayer->velocity.y = 0;
		this->mainPlayer->onGround = true;
		this->mainPlayer->ResetVelocityY();
		this->mainPlayer->SetPosition(this->mainPlayer->GetPosition().x, this->_window->getSize().y - this->mainPlayer->GetGlobalBounds().height);
	}

	auto begin = this->mainPlayer->BulletsSprites.begin();
	auto end = this->mainPlayer->BulletsSprites.end();

	for (auto iterator = begin; iterator != end;++iterator)
	{
		auto tempStruct = iterator->sprite;
		auto tempBulletSprite = tempStruct;
		if (tempBulletSprite.getPosition().x < 0 or tempBulletSprite.getPosition().x > this->_window->getSize().x)
		{
			this->mainPlayer->BulletsSprites.erase(iterator);
			break;
		}
	}
}

void GamePlayPage::Display()
{
	this->_window->clear();

	this->_window->draw(this->_bgSprite);

	this->_window->draw(this->Score);

	this->_window->draw(this->Hp);
	this->_window->draw(HealthBar);

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

	if (event->type == sf::Event::KeyReleased and (
		event->key.code == sf::Keyboard::A or
		event->key.code == sf::Keyboard::D or
		event->key.code == sf::Keyboard::W or
		event->key.code == sf::Keyboard::S or
		event->key.code == sf::Keyboard::Space))
	{
		this->mainPlayer->ResetAnimationTimer();
	}
}

GamePlayPage::~GamePlayPage()
{
	delete this->mainPlayer;
}
