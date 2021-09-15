#pragma once

#include <SFML/Graphics.hpp>

enum class MovingFrame {

	None,
	Left,
	Right,
	Jump,
	Down
};

struct CurrentFrame
{
	int Left;
	int Top;
	int Width;
	int Height;

	CurrentFrame(int left, int top, int width, int height)
	{
		Left = left;
		Top = top;
		Width = width;
		Height = height;
	}

	CurrentFrame() = default;
};

class BasePlayer {

public:
	sf::Texture	textureSheet;
	sf::Sprite sprite;
	sf::Clock animationTimer;

	virtual void Animations() {}
	virtual void UpdateAnimations() {}
	virtual void Movement() {}
	virtual void Update() {}
	virtual void Render(sf::RenderTarget* target) {}

	virtual ~BasePlayer() {}

	MovingFrame movingFrame = MovingFrame::None;

	CurrentFrame currentFrame;

private:

};