#include"Includes/Player.h"

void Player::Movement()
{
	this->movingFrame = MovingFrame::None;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))  // Move Up
	{
		this->sprite.move(0.f, -2.f);
		this->movingFrame = MovingFrame::Jump;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // Move Left
	{
		this->sprite.move(-2.f, 0.f);
		this->movingFrame = MovingFrame::Left;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) // Move Down
	{
		this->sprite.move(0.f, 2.f);
		this->movingFrame = MovingFrame::Down;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // Move Right
	{
		this->sprite.move(2.f, 0.f);
		this->movingFrame = MovingFrame::Right;
	}
}

void Player::UpdateAnimations()
{

	if (this->movingFrame == MovingFrame::None)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f)
		{
			this->currentFrame.Top = 8;

			this->currentFrame.Left += 25;

			if (this->currentFrame.Left >= 26)
				this->currentFrame.Left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(sf::IntRect(currentFrame.Left, currentFrame.Top, currentFrame.Width, currentFrame.Height));
		}
	}

	else if (this->movingFrame == MovingFrame::Right)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f)
		{
			this->currentFrame.Top = 79;

			this->currentFrame.Left += 25;

			if (this->currentFrame.Left >= 72)
				this->currentFrame.Left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(sf::IntRect(currentFrame.Left, currentFrame.Top, currentFrame.Width, currentFrame.Height));
		}
	}

}

void Player::Update()
{
	this->Movement();
	this->UpdateAnimations();
}

void Player::Render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
