#pragma once

#include<vector>
#include "BasePageClass.h"
#include "Player.h"

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
	Player* mainPlayer;
	void setUp();
	void updatePlayer();
	bool GamePlay{ true };
	void CheckCollision();

};