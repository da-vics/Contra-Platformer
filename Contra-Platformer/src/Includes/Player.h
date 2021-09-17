#pragma once

#include"BasePlayer.h"
#include<iostream>

class Player :public BasePlayer
{

public:

	Player()
	{
		if (!this->textureSheet.loadFromFile("Assets/Images/ContraSheet.png"))
		{
			std::cout << "error" << std::endl;
		}
		this->sprite.setTexture(this->textureSheet);
		this->currentFrame = CurrentFrame(1, 8, 24, 35);
		this->sprite.setTextureRect(sf::IntRect(currentFrame.Left, currentFrame.Top, currentFrame.Width, currentFrame.Height));
		this->sprite.setScale(2.5f, 2.5f);

		this->animationTimer.restart();
		this->maxVelocity = 12.f;
		this->acceleration = 3.f;
		this->drag = 0.65f;
		this->velocityMin = 1.f;

		if (!this->soundBuffer.loadFromFile("Assets/Audio/shootGun.wav")) {
			std::cout << "Error Loading Assets/Audio/shootGun.wav" << std::endl;
		}

		this->GameSound.setBuffer(this->soundBuffer);
		this->GameSound.setVolume(50);
	}

	virtual void Update(float x, float y) override;
	virtual void Render(sf::RenderTarget* target) override;
	virtual bool GetAnimationSwitch() override;
	virtual void ResetAnimationTimer();
	virtual sf::FloatRect GetGlobalBounds() const override;
	virtual void ResetVelocityY() override;
	virtual void SetPosition(const float x, const float y) override;
	virtual sf::Vector2f GetPosition() const override;


private:
	virtual void Movement(float x, float y) override;
	virtual void UpdateAnimations() override;
	virtual void UpdatePhysics() override;
	virtual void move(const float dir_x, const float dir_y) override;

	int playerMove[3] = { 17,17,17 };
	int moveIndex = 0;
};

