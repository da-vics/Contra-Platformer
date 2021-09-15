#pragma once

#include"BasePlayer.h"

class Player :public BasePlayer
{

public:

	Player()
	{
		this->textureSheet.loadFromFile("Assets/Images/ContraSheet.png");
		this->sprite.setTexture(this->textureSheet);
		currentFrame = CurrentFrame(1, 8, 24, 34);
		this->sprite.setTextureRect(sf::IntRect(currentFrame.Left, currentFrame.Top, currentFrame.Width, currentFrame.Height));
		this->sprite.setScale(2.5f, 2.5f);
		this->animationTimer.restart();
	}

	virtual void Update() override;
	virtual void Render(sf::RenderTarget* target) override;

private:
	virtual void Movement() override;
	virtual void UpdateAnimations() override;


};

