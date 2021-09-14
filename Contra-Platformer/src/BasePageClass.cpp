#include "Includes/BasePageClass.h"

bool BasePageClass::IsMouseOverButton(const sf::RectangleShape& Btn) {

	float mouseX = sf::Mouse::getPosition(*this->_window).x;
	float mouseY = sf::Mouse::getPosition(*this->_window).y;

	float btnPosX = Btn.getPosition().x;
	float btnPosY = Btn.getPosition().y;

	auto btnPosWidth = btnPosX + Btn.getLocalBounds().width;
	auto btnPosHeight = btnPosY + Btn.getLocalBounds().height;

	if (mouseX < btnPosWidth && mouseX > btnPosX && mouseY <btnPosHeight && mouseY>btnPosY)
		return true;

	return false;
}


void BasePageClass::AlertWindow(sf::Font cFont, std::string AlertMessage, int Wx, int Wy, sf::Color bgcolor, sf::Color messageColor) {

	sf::RenderWindow win(sf::VideoMode(Wx, Wy), "Alert", sf::Style::Close | sf::Style::None);
	sf::Text PlayNameText;

	PlayNameText.setFont(cFont);
	PlayNameText.setFillColor(messageColor);
	PlayNameText.setStyle(sf::Text::Bold);
	PlayNameText.setCharacterSize(15);
	PlayNameText.setString(AlertMessage);
	PlayNameText.setPosition(win.getSize().x / 2.f - PlayNameText.getLocalBounds().width / 2.f, win.getSize().y / 2.f - PlayNameText.getLocalBounds().height / 2.f);

	while (win.isOpen())
	{
		sf::Event evt;
		while (win.pollEvent(evt))
		{
			if (evt.type == sf::Event::Closed)
				win.close();
		}//

		win.clear(bgcolor);
		win.draw(PlayNameText);
		win.display();
	}
}

void BasePageClass::Init() {

	if (!this->_HeaderFont.loadFromFile("Assets/Fonts/Handlee.ttf")) {
		std::cout << "Error Loading Fonts" << std::endl;
		std::cout << "Shutting Down!" << std::endl;
		this->_window->close();
	}

}