#pragma once

#include"BasePlayer.h"

class Player :public BasePlayer
{

public:

	Player()
	{
		this->textureSheet.loadFromFile("Assets/Images/ContraSheet.png");
		this->sprite.setTexture(this->textureSheet);
		this->currentFrame = CurrentFrame(1, 8, 24, 34);
		this->sprite.setTextureRect(sf::IntRect(currentFrame.Left, currentFrame.Top, currentFrame.Width, currentFrame.Height));
		this->sprite.setScale(2.5f, 2.5f);

		this->animationTimer.restart();
		this->maxVelocity = 12.f;
		this->acceleration = 3.f;
		this->drag = 0.65f;
		this->velocityMin = 1.f;
	}

	virtual void Update() override;
	virtual void Render(sf::RenderTarget* target) override;
	virtual bool& GetAnimationSwitch() override;
	virtual void ResetAnimationTimer();
	virtual sf::FloatRect GetGlobalBounds() const override;
	virtual void ResetVelocityY() override;
	virtual void SetPosition(const float x, const float y) override;
	virtual sf::Vector2f GetPosition() const override;


private:
	virtual void Movement() override;
	virtual void UpdateAnimations() override;
	virtual void UpdatePhysics() override;
	virtual void move(const float dir_x, const float dir_y) override;


};

