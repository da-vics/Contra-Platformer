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

	this->PlayerHeight = this->_window->getSize().y - this->mainPlayer->GetGlobalBounds().height;

	if (this->Enemies.size() != 1)
	{
		sf::Vector2f tempPos;
		tempPos.y = this->PlayerHeight;
		tempPos.x = 840;

		this->Enemies.push_back(Enemy(tempPos, MovingFrame::Right, " ", &(this->mainPlayer->sprite)));
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
	for (auto& enemy : this->Enemies)
	{
		enemy.Movement(0, 0);
	}


	if (this->Enemies.size() == 1 && Enemies[0].movingFrame == MovingFrame::Right)
	{
		if (this->mainPlayer->sprite.getPosition().x > 100)
		{
			sf::Vector2f tempPos;
			tempPos.y = this->PlayerHeight;
			tempPos.x = 20;
			this->Enemies.push_back(Enemy(tempPos, MovingFrame::Left, " ", &(this->mainPlayer->sprite)));
		}
	}

	else if (this->Enemies.size() == 1 && Enemies[0].movingFrame == MovingFrame::Left)
	{
		if (this->mainPlayer->sprite.getPosition().x < 840)
		{
			sf::Vector2f tempPos;
			tempPos.y = this->PlayerHeight;
			tempPos.x = 840;
			this->Enemies.push_back(Enemy(tempPos, MovingFrame::Right, " ", &(this->mainPlayer->sprite)));
		}
	}
}

void GamePlayPage::CheckCollision()
{
	for (auto& enemy : this->Enemies)
		enemy.Shoot();

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

		bool found = false;

		auto Ebegin = this->Enemies.begin();
		auto Eend = this->Enemies.end();

		for (auto Eiterator = Ebegin; Eiterator != Eend; ++Eiterator)
		{
			if (tempBulletSprite.getGlobalBounds().intersects(Eiterator->sprite.getGlobalBounds()))
			{
				Eiterator->Health -= 1;

				if (Eiterator->Health <= 0)
				{
					this->Enemies.erase(Eiterator);
					this->score += 2;
					this->Score.setString("Score: " + std::to_string(this->score));
				}

				this->mainPlayer->BulletsSprites.erase(iterator);
				found = true;
				break;
			}
		}

		if (found)
			break;

		if (tempBulletSprite.getPosition().x < 0 or tempBulletSprite.getPosition().x > this->_window->getSize().x)
		{
			this->mainPlayer->BulletsSprites.erase(iterator);
			break;
		}
	}

	for (int i = 0; i < this->Enemies.size(); ++i)
	{
		auto begin = this->Enemies[i].BulletsSprites.begin();
		auto end = this->Enemies[i].BulletsSprites.end();

		for (auto iterator = begin; iterator != end;++iterator)
		{
			auto tempStruct = iterator->sprite;
			auto tempBulletSprite = tempStruct;

			if (tempBulletSprite.getGlobalBounds().intersects(this->mainPlayer->GetGlobalBounds()))
			{
				this->mainPlayer->Health -= 1;
				this->HealthBar.setSize(sf::Vector2f(this->mainPlayer->Health * 2.f, 20.f));
				if (this->mainPlayer->Health <= 70)
				{
					this->HealthBar.setFillColor(sf::Color(135, 9, 9));
					this->Hp.setFillColor(sf::Color(135, 9, 9));
				}
				this->Enemies[i].BulletsSprites.erase(iterator);
				if (this->mainPlayer->Health <= 0)
				{
					this->GamePlay = false;

					GameOver.setFont(this->_HeaderFont);
					GameOver.setPosition((this->_window->getSize().x / 2) - 130, this->_window->getSize().y / 2);
					GameOver.setCharacterSize(30);
					GameOver.setString("Game Over.. Press <-");
					GameOver.setStyle(sf::Text::Bold);
					GameOver.setFillColor(sf::Color(135, 9, 9));
				}
				break;
			}

			else if (tempBulletSprite.getPosition().x < 0 or tempBulletSprite.getPosition().x > this->_window->getSize().x)
			{
				this->Enemies[i].BulletsSprites.erase(iterator);
				break;
			}
		}
	}//
}

void GamePlayPage::Display()
{
	if (this->GamePlay)
	{
		this->_window->clear();

		this->_window->draw(this->_bgSprite);

		this->_window->draw(this->Score);

		this->_window->draw(this->Hp);
		this->_window->draw(HealthBar);

		for (auto sprite : this->PlatoformSprites)
			this->_window->draw(sprite);

		for (auto& enemy : this->Enemies)
			enemy.Render(this->_window);

		this->mainPlayer->Render(this->_window);

		this->_window->display();

		this->updatePlayer();
	}

	else
	{
		this->_window->draw(GameOver);
		this->_window->display();
	}

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
