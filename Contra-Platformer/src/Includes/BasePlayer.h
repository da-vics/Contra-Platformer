#pragma once

#include <SFML/Graphics.hpp>
#include<vector>
#include<SFML/Audio.hpp>

enum class MovingFrame {

	None,
	Left,
	Right,
	UpLeft,
	UpRight,
	Up,
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

enum class BulletOrientation {

	Right,
	Left
};


struct Sprites
{
	sf::Sprite sprite;
	int movement;
	float xPosOffset;
};

class BasePlayer {

public:
	sf::Texture	textureSheet;
	sf::Sprite sprite;
	sf::Clock animationTimer;
	sf::SoundBuffer soundBuffer;
	sf::Sound GameSound;
	sf::Vector2f velocity;

	int Health{ 100 };
	float acceleration{ 0 };
	float drag{ 0 };
	float velocityMin{ 0 };
	float maxVelocity{ 15.f };
	float gravity{ 0.5f };
	float velocityMaxY{ 5.f };
	float onGround{ true };
	bool animationSwitch{ true };
	bool canJump{ false };
	std::vector<Sprites> BulletsSprites;


	virtual void Animations() {}
	virtual void UpdateAnimations() {}
	virtual void Movement(float x, float y) {}
	virtual void Update(float x, float y) {}
	virtual void UpdatePhysics() {}
	virtual void move(const float dir_x, const float dir_y) {}
	virtual void Render(sf::RenderTarget* target) {}
	virtual void ResetAnimationTimer() {}
	virtual bool GetAnimationSwitch() = 0;
	virtual sf::FloatRect GetGlobalBounds() const = 0;
	virtual sf::Vector2f GetPosition() const = 0;
	virtual void ResetVelocityY() {};
	virtual void SetPosition(const float x, const float y) {};


	virtual ~BasePlayer() {}

	MovingFrame movingFrame = MovingFrame::None;
	BulletOrientation bulletOrientation = BulletOrientation::Right;

	CurrentFrame currentFrame;

private:

};