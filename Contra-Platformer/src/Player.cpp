#include"Includes/Player.h"

void Player::Movement(float x, float y)
{
	this->movingFrame = MovingFrame::None;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::Up))  // Move Up
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			this->movingFrame = MovingFrame::UpLeft;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			this->movingFrame = MovingFrame::UpRight;

			auto bound = this->sprite.getPosition().x + this->sprite.getGlobalBounds().width;

			if (bound < x)
				this->move(0.6f, 0.f);
		}

		else
			this->movingFrame = MovingFrame::Up;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // Move Left
	{
		if (this->sprite.getPosition().x > 0)
			this->move(-0.6f, 0.f);
		this->movingFrame = MovingFrame::Left;
		bulletOrientation = BulletOrientation::Left;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) // Move Down
	{
		this->move(0.f, 0.6f);
		this->movingFrame = MovingFrame::Down;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // Move Right
	{
		auto bound = this->sprite.getPosition().x + this->sprite.getGlobalBounds().width;

		if (bound < x)
			this->move(0.6f, 0.f);
		this->movingFrame = MovingFrame::Right;
		bulletOrientation = BulletOrientation::Right;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // Jump
	{
		if (this->onGround == true && canJump)
		{
			this->velocity.y = -250.f;
			this->movingFrame = MovingFrame::Jump;
			this->onGround = false;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) // Shoot
	{
		Sprites tempStruct;

		if (this->bulletOrientation == BulletOrientation::Right)
		{
			tempStruct.movement = 5; tempStruct.xPosOffset = this->sprite.getGlobalBounds().width;
		}

		else
		{
			tempStruct.movement = -5; tempStruct.xPosOffset = 0;
		}

		sf::Sprite tempSprite;
		tempSprite.setTexture(this->textureSheet);
		tempSprite.setTextureRect(sf::IntRect(97, 9, 6, 6));
		tempSprite.setPosition(this->sprite.getPosition().x + tempStruct.xPosOffset, this->sprite.getPosition().y + (this->sprite.getGlobalBounds().height / 2) - 15);
		tempStruct.sprite = tempSprite;
		this->BulletsSprites.push_back(tempStruct);
		this->GameSound.play();
	}

}

void Player::UpdateAnimations()
{
	if (this->movingFrame == MovingFrame::None)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.5f or this->GetAnimationSwitch())
		{
			this->currentFrame.Top = 8;

			this->currentFrame.Left += 25;

			if (this->currentFrame.Left >= 26)
				this->currentFrame.Left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(sf::IntRect(currentFrame.Left, currentFrame.Top, currentFrame.Width, currentFrame.Height));
		}
	}

	else if (this->movingFrame == MovingFrame::Up)
	{
		this->sprite.setTextureRect(sf::IntRect(1, 149, 16, 35));
		this->animationTimer.restart();
	}

	else if (this->movingFrame == MovingFrame::Right)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f or this->GetAnimationSwitch())
		{
			this->currentFrame.Top = 79;

			this->currentFrame.Left += 25;

			if (this->currentFrame.Left >= 72)
				this->currentFrame.Left = 1;

			this->animationTimer.restart();
			this->sprite.setTextureRect(sf::IntRect(currentFrame.Left, currentFrame.Top, currentFrame.Width, currentFrame.Height));
		}
		this->sprite.setScale(2.5f, 2.5f);
		this->sprite.setOrigin(0, 0);
	}

	else if (this->movingFrame == MovingFrame::UpRight)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f or this->GetAnimationSwitch())
		{
			this->currentFrame.Top = 149;

			this->currentFrame.Left += playerMove[moveIndex++];

			if (this->currentFrame.Left >= 51)
			{
				this->currentFrame.Left = 1;
				moveIndex = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(sf::IntRect(currentFrame.Left, currentFrame.Top, currentFrame.Width, currentFrame.Height));
		}
		this->sprite.setScale(2.5f, 2.5f);
		this->sprite.setOrigin(0, 0);
	}

	else if (this->movingFrame == MovingFrame::Left)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f or this->GetAnimationSwitch())
		{
			this->currentFrame.Top = 79;

			this->currentFrame.Left += 25;

			if (this->currentFrame.Left >= 72)
				this->currentFrame.Left = 1;

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

	this->sprite.move(this->velocity);
}

void Player::move(const float dir_x, const float dir_y)
{
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

void Player::Update(float x, float y)
{
	this->Movement(x, y);
	this->UpdateAnimations();
	this->UpdatePhysics();
}

void Player::Render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	if (this->BulletsSprites.size() > 0)
		for (int i = 0; i < this->BulletsSprites.size(); ++i)
		{
			auto tempStruct = this->BulletsSprites[i];
			auto sprite = tempStruct.sprite;
			sprite.setPosition((sprite.getPosition().x) + tempStruct.movement, sprite.getPosition().y);
			target->draw(sprite);
			tempStruct.sprite = sprite;
			this->BulletsSprites[i] = tempStruct;
		}
}

bool& Player::GetAnimationSwitch()
{
	bool temp = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return temp;
}
