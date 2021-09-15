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

	sf::Vector2f velocity;
	float acceleration{ 0 };
	float drag{ 0 };
	float velocityMin{ 0 };
	float maxVelocity{ 15.f };
	float gravity{ 4.f };
	float velocityMaxY{ 15.f };
	bool animationSwitch{ true };

	virtual void Animations() {}
	virtual void UpdateAnimations() {}
	virtual void Movement() {}
	virtual void Update() {}
	virtual void UpdatePhysics() {}
	virtual void move(const float dir_x, const float dir_y) {}
	virtual void Render(sf::RenderTarget* target) {}
	virtual void ResetAnimationTimer() {}
	virtual bool& GetAnimationSwitch() = 0;
	virtual sf::FloatRect GetGlobalBounds() const = 0;
	virtual sf::Vector2f GetPosition() const = 0;
	virtual void ResetVelocityY() {};
	virtual void SetPosition(const float x, const float y) {};

	virtual ~BasePlayer() {}

	MovingFrame movingFrame = MovingFrame::None;

	CurrentFrame currentFrame;

private:

};