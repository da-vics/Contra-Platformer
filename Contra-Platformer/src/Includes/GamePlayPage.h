#pragma once

#include<vector>
#include "BasePageClass.h"
#include "Player.h"
#include"Enemy.h"

class GamePlayPage : public BasePageClass
{

public:

	GamePlayPage(sf::RenderWindow* window, bool compPlay) : BasePageClass(window)
	{
		this->_pageID = "MainPage";
		this->NavTOPage = GamePages::None;
		this->setUp();
	}

	void Display() override;
	void HandleEvents(sf::Event*) override;

	~GamePlayPage();

private:

	sf::Texture PlatformTexture;
	std::vector<sf::Sprite>PlatoformSprites;
	std::vector <Enemy> Enemies;
	Player* mainPlayer;
	void setUp();
	void updatePlayer();
	bool GamePlay{ true };
	void CheckCollision();
	sf::Text Score;
	sf::Text Hp;
	sf::Text GameOver;
	sf::RectangleShape HealthBar;
	int score{ 0 };
	int PlayerHeight{ 0 };
	sf::Color HpColor = sf::Color(19, 224, 16);


};