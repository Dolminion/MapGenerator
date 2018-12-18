#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class UIManager : public sf::Drawable
{
private:
	sf::RectangleShape m_MenuBox;
	sf::RectangleShape m_MapUIBox;
	sf::RectangleShape m_MapBox;

	static const int s_kiNumMenuButtons = 3;
	static const int s_kiNumMapButtons = 9;

	sf::RectangleShape m_MenuButtons[s_kiNumMenuButtons];
	sf::RectangleShape m_MapButtons[s_kiNumMapButtons];
	sf::Color m_aMapColors[s_kiNumMapButtons - 2];

	bool m_bCircleActive;
	sf::CircleShape m_PointerCircle;
	std::vector<sf::CircleShape> m_vMapCircles;

	sf::Font m_Font;
	sf::Text m_MenuText[s_kiNumMenuButtons];
	sf::Text m_MapText[s_kiNumMapButtons];

	enum m_MenuButtons
	{
		start,
		sound,
		exit
	};

	enum m_MapButtons
	{
		ocean,
		grassland,
		forest,
		desert,
		mountains,
		volcano,
		swamp,
		generate,
		back
	};

	bool m_bOnMenu;
	bool m_bTypeSelected;

public:
	UIManager();
	UIManager(unsigned int uiWindowSize);
	bool onMenu();
	//sf::Vector2i findTile(sf::Vector2i checkPos, int iArraySize);
	bool checkBounds(sf::Vector2i checkPos, bool& bStart, bool& bGenerate, bool& bExit, std::string& sButtonClicked); //have return type? or call button.pressed()
	sf::Vector2f getMapSize();
	sf::Vector2f getMapPosition();
	void moveCircle(sf::Window& window);
	void setCircle();
	bool loadFont(std::string sFontPath);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};