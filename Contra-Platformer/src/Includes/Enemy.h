#pragma once

#include"BasePlayer.h"
#include<iostream>

class Enemy :public BasePlayer
{

public:
	Enemy(sf::Vector2f pos, MovingFrame mFrame, std::string textSheet = " ", sf::Sprite* Tsprite = nullptr)
	{
		if (textSheet != " ")
		{
			this->textureSheet.loadFromFile(textSheet);
			this->sprite.setTexture(this->textureSheet);
		}
		else
			this->sprite = *Tsprite;
		this->currentFrame = CurrentFrame(209, 79, 24, 35);
		this->sprite.setTextureRect(sf::IntRect(currentFrame.Left, currentFrame.Top, currentFrame.Width, currentFrame.Height));
		this->sprite.setScale(2.5f, 2.5f);
		this->sprite.setPosition(pos);

		this->animationTimer.restart();
		this->maxVelocity = 12.f;
		this->acceleration = 3.f;
		this->drag = 0.65f;
		this->velocityMin = 1.f;
		this->Health = 100;

		if (mFrame == MovingFrame::Left)
		{
			this->sprite.setScale(2.5f, 2.5f);
			this->sprite.setOrigin(0, 0);
			this->bulletOrientation = BulletOrientation::Right;
		}

		else if (mFrame == MovingFrame::Right)
		{
			this->sprite.setScale(-2.5f, 2.5f);
			this->sprite.setOrigin(0, 0);
			this->bulletOrientation = BulletOrientation::Left;
		}

		this->movingFrame = mFrame;
	}

	void Shoot();
	virtual void Render(sf::RenderTarget* target) override;
	virtual bool GetAnimationSwitch() override;
	virtual sf::FloatRect GetGlobalBounds() const override;
	virtual sf::Vector2f GetPosition() const override;
};

