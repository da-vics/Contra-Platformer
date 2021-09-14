#pragma once

#include"BasePlayer.h"

class Player :public BasePlayer
{

public:

	Player()
	{
		this->textureSheet.loadFromFile("Assets/Images/ContraSheet.gif");
		this->sprite.setTexture(this->textureSheet);
	}

	virtual void Update() override;
	virtual void Render(sf::RenderTarget* target) override;

private:


};

