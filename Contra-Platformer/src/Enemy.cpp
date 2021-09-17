#include "Includes\Enemy.h"

void Enemy::Render(sf::RenderTarget* target)
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

void Enemy::Movement(float x, float y)
{
	if (this->sprite.getPosition().x != this->xPos)
	{
		if (this->movingFrame == MovingFrame::Right)
			this->sprite.move(-2.f, 0);

		if (this->movingFrame == MovingFrame::Left)
			this->sprite.move(2.f, 0);

		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f or this->GetAnimationSwitch())
		{
			this->currentFrame.Top = 79;

			this->currentFrame.Left += 25;

			if (this->currentFrame.Left >= 259)
				this->currentFrame.Left = 209;

			this->animationTimer.restart();
			this->sprite.setTextureRect(sf::IntRect(currentFrame.Left, currentFrame.Top, currentFrame.Width, currentFrame.Height));
		}
	}

	else
	{
		this->canShoot = true;
	}
}

void Enemy::Shoot()
{
	if (canShoot == true)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f)
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

			sf::Sprite tempSprite = this->sprite;
			tempSprite.setTextureRect(sf::IntRect(82, 9, 6, 6));
			tempSprite.setPosition(this->sprite.getPosition().x + tempStruct.xPosOffset, this->sprite.getPosition().y + (this->sprite.getGlobalBounds().height / 2) - 15);
			tempStruct.sprite = tempSprite;
			this->BulletsSprites.push_back(tempStruct);
			this->animationTimer.restart();
		}
	}
}

bool Enemy::GetAnimationSwitch()
{
	return false;
}

sf::FloatRect Enemy::GetGlobalBounds() const
{
	return sf::FloatRect();
}

sf::Vector2f Enemy::GetPosition() const
{
	return sf::Vector2f();
}
