#pragma once

#include <SFML/Graphics.hpp>


class BasePlayer {

public:
	sf::Texture	textureSheet;
	sf::Sprite sprite;

	virtual void Update() {}
	virtual void Render(sf::RenderTarget* target) {}

	virtual ~BasePlayer() {}

private:

};