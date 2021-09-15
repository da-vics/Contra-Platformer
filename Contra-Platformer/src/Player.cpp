#include"Includes/Player.h"

void Player::Movement()
{
	this->movingFrame = MovingFrame::None;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))  // Move Up
	{
		this->move(0.f, -0.6f);
		this->movingFrame = MovingFrame::Jump;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // Move Left
	{
		this->move(-0.6f, 0.f);
		this->movingFrame = MovingFrame::Left;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) // Move Down
	{
		this->move(0.f, 0.6f);
		this->movingFrame = MovingFrame::Down;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // Move Right
	{
		this->move(0.6f, 0.f);
		this->movingFrame = MovingFrame::Right;
	}
}

void Player::UpdateAnimations()
{

	if (this->movingFrame == MovingFrame::None)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.5f || this->GetAnimationSwitch())
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
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->GetAnimationSwitch())
		{
			this->currentFrame.Top = 79;

			this->currentFrame.Left += 25;

			if (this->currentFrame.Left >= 72)
				this->currentFrame.Left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(sf::IntRect(currentFrame.Left, currentFrame.Top, currentFrame.Width, currentFrame.Height));
		}
		this->sprite.setScale(2.5f, 2.5f);
		this->sprite.setOrigin(0, 0);
	}

	else if (this->movingFrame == MovingFrame::Left)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->GetAnimationSwitch())
		{
			this->currentFrame.Top = 79;

			this->currentFrame.Left += 25;

			if (this->currentFrame.Left >= 72)
				this->currentFrame.Left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(sf::IntRect(currentFrame.Left, currentFrame.Top, currentFrame.Width, currentFrame.Height));
		}
		this->sprite.setScale(-2.5f, 2.5f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.5f, 0.f);
	}

	else
		this->animationTimer.restart();

}

void Player::UpdatePhysics()
{
	this->velocity *= this->drag;

	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0.f;

	this->sprite.move(this->velocity);
}

void Player::move(const float dir_x, const float dir_y)
{
	this->velocity.y += 1.0 * this->gravity;
	if (std::abs(this->velocity.y) > this->velocityMaxY)
		this->velocity.y = this->maxVelocity * ((this->velocity.y < 0.f) ? -1.f : 1.f);

	this->velocity.x += dir_x * this->acceleration;

	if (std::abs(this->velocity.x) > this->maxVelocity)
		this->velocity.x = this->maxVelocity * ((this->velocity.x < 0.f) ? -1.f : 1.f);
}

void Player::ResetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

sf::FloatRect Player::GetGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::ResetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::SetPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

sf::Vector2f Player::GetPosition() const
{
	return this->sprite.getPosition();
}

void Player::Update()
{
	this->Movement();
	this->UpdateAnimations();
	this->UpdatePhysics();
}

void Player::Render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

bool& Player::GetAnimationSwitch()
{
	bool temp = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return temp;
}
