#include"Includes/Player.h"

void Player::Update()
{
}

void Player::Render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
