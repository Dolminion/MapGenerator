#include "uimanager.h"
//#include <iostream>

UIManager::UIManager()
{

}

//CONSTRUCTOR
UIManager::UIManager(unsigned int uiWindowSize)
{
	m_bOnMenu = true;
	m_bTypeSelected = true;
	//initialise array of buttons
	/*start, options, exit ---- maptiles, print, back*/

	//////////Set UI Areas
	m_MenuBox.setSize(sf::Vector2f(float(uiWindowSize * 0.5f), float(uiWindowSize * 0.8f)));
	m_MenuBox.setPosition(sf::Vector2f(float(uiWindowSize * 0.5f), float(uiWindowSize * 0.1f)));
	m_MenuBox.setOutlineColor(sf::Color::Green);
	m_MenuBox.setOutlineThickness(2.f);
	m_MenuBox.setFillColor(sf::Color::Transparent);

	m_MapUIBox.setSize(sf::Vector2f(float(uiWindowSize * 0.5f), float(uiWindowSize)));
	m_MapUIBox.setPosition(sf::Vector2f(0.f, 0.f));
	m_MapUIBox.setFillColor(sf::Color(150, 100, 255, 255));

	m_MapBox.setSize(sf::Vector2f(float(uiWindowSize), float(uiWindowSize)));
	m_MapBox.setPosition(sf::Vector2f(float(uiWindowSize * 0.5f), 0.f));
	m_MapBox.setFillColor(sf::Color::Transparent);
	///////End of UI Areas

	sf::Vector2f menuSize = m_MenuBox.getSize();
	sf::Vector2f menuPosition = m_MenuBox.getPosition();

	sf::Vector2f mapUISize = m_MapUIBox.getSize();
	sf::Vector2f mapPosition = m_MapUIBox.getPosition();

	///////////Set Buttons
	for (int i = 0; i < s_kiNumMenuButtons; i++)
	{
		m_MenuButtons[i].setSize(sf::Vector2f(menuSize.x * 0.8f, menuSize.y * 0.15f));
		m_MenuButtons[i].setPosition(sf::Vector2f(menuPosition.x + menuSize.x * 0.1f, menuPosition.y + ((menuSize.y * 0.25f) * (i + 1))));
		m_MenuButtons[i].setFillColor(sf::Color::White); // use sprite?
		m_MenuText[i].setCharacterSize(int(m_MenuButtons[i].getSize().y * 0.5f));
		m_MenuText[i].setPosition(sf::Vector2f(menuPosition.x + menuSize.x * 0.1f, menuPosition.y + ((menuSize.y * 0.25f) * (i + 1))));
		m_MenuText[i].setColor(sf::Color::Black);
	}

	for (int i = 0; i < s_kiNumMapButtons; i++)
	{
		m_MapButtons[i].setSize(sf::Vector2f(mapUISize.x * 0.7f, mapUISize.y * 0.08f));
		m_MapButtons[i].setPosition(sf::Vector2f(mapPosition.x + mapUISize.x * 0.15f, mapPosition.y + ((mapUISize.y * 0.1f) * (i + 1))));
		m_MapButtons[i].setFillColor(sf::Color::White);
		m_MapText[i].setCharacterSize(int(m_MenuButtons[i].getSize().y * 0.5f));
		m_MapText[i].setPosition(sf::Vector2f(mapPosition.x + mapUISize.x * 0.15f, mapPosition.y + ((mapUISize.y * 0.1f) * (i + 1))));
		m_MapText[i].setColor(sf::Color::Black);
	}

	m_aMapColors[ocean] = sf::Color(0, 50, 130, 255);
	m_aMapColors[grassland] = sf::Color(50, 210, 80, 255);
	m_aMapColors[forest] = sf::Color(10, 100, 30, 255);
	m_aMapColors[desert] = sf::Color(240, 230, 60, 255);
	m_aMapColors[mountains] = sf::Color(100, 100, 100, 255);
	m_aMapColors[volcano] = sf::Color(240, 160, 60, 255);
	m_aMapColors[swamp] = sf::Color(60, 0, 90, 255);

	m_PointerCircle.setRadius(3.f);

	m_MenuText[start].setString("Start");
	m_MenuText[sound].setString("Sound");
	m_MenuText[exit].setString("Exit");

	m_MapText[ocean].setString("Ocean");
	m_MapText[grassland].setString("Grassland");
	m_MapText[forest].setString("Forest");
	m_MapText[desert].setString("Desert");
	m_MapText[mountains].setString("Mountains");
	m_MapText[volcano].setString("Volcano");
	m_MapText[swamp].setString("Swamp");
	m_MapText[generate].setString("Generate");
	m_MapText[back].setString("Back");
	///////////End of Buttons
}

//CHECKS WHICH SCREEN
bool UIManager::onMenu()
{
	return m_bOnMenu;
}

//CHECK IF MOUSE CLICK IS ON ANY UI ELEMENTS AND PROCESS
bool UIManager::checkBounds(sf::Vector2i checkPos, bool& bStart, bool& bGenerate, bool& bExit, std::string& sButtonClicked)
{
	if (m_bOnMenu)
	{
		//if start button clicked
		if (sf::FloatRect(m_MenuButtons[start].getPosition(), m_MenuButtons[start].getSize()).contains(float(checkPos.x), float(checkPos.y)))
		{
			m_bOnMenu = false;
			bStart = true;
		}

		/*else if (sf::FloatRect(m_MenuButtons[sound].getPosition(), m_MenuButtons[sound].getSize()).contains(float(checkPos.x), float(checkPos.y)))
			//mute sound */

		//if exit button clicked
		else if (sf::FloatRect(m_MenuButtons[exit].getPosition(), m_MenuButtons[exit].getSize()).contains(float(checkPos.x), float(checkPos.y)))
			bExit = true;
	}
	else
	{
		//if buttons clicked on
		//click Ocean Button
		if (sf::FloatRect(m_MapButtons[ocean].getPosition(), m_MenuButtons[ocean].getSize()).contains(float(checkPos.x), float(checkPos.y)))
		{
			sButtonClicked = "ocean";
			m_bTypeSelected = true;
			m_PointerCircle.setFillColor(m_aMapColors[ocean]);
		}

		//click Grassland Button
		if (sf::FloatRect(m_MapButtons[grassland].getPosition(), m_MenuButtons[grassland].getSize()).contains(float(checkPos.x), float(checkPos.y)))
		{
			sButtonClicked = "grassland";
			m_bTypeSelected = true;
			m_PointerCircle.setFillColor(m_aMapColors[grassland]);
		}

		//click Forest Button
		if (sf::FloatRect(m_MapButtons[forest].getPosition(), m_MenuButtons[forest].getSize()).contains(float(checkPos.x), float(checkPos.y)))
		{
			sButtonClicked = "forest";
			m_bTypeSelected = true;
			m_PointerCircle.setFillColor(m_aMapColors[forest]);
		}

		//click Desert Button
		if (sf::FloatRect(m_MapButtons[desert].getPosition(), m_MenuButtons[desert].getSize()).contains(float(checkPos.x), float(checkPos.y)))
		{
			sButtonClicked = "desert";
			m_bTypeSelected = true;
			m_PointerCircle.setFillColor(m_aMapColors[desert]);
		}

		//click Mountains Button
		if (sf::FloatRect(m_MapButtons[mountains].getPosition(), m_MenuButtons[mountains].getSize()).contains(float(checkPos.x), float(checkPos.y)))
		{
			sButtonClicked = "mountains";
			m_bTypeSelected = true;
			m_PointerCircle.setFillColor(m_aMapColors[mountains]);
		}

		//click Volcano Button
		if (sf::FloatRect(m_MapButtons[volcano].getPosition(), m_MenuButtons[volcano].getSize()).contains(float(checkPos.x), float(checkPos.y)))
		{
			sButtonClicked = "volcano";
			m_bTypeSelected = true;
			m_PointerCircle.setFillColor(m_aMapColors[volcano]);
		}

		//click Swamp Button
		if (sf::FloatRect(m_MapButtons[swamp].getPosition(), m_MenuButtons[swamp].getSize()).contains(float(checkPos.x), float(checkPos.y)))
		{
			sButtonClicked = "swamp";
			m_bTypeSelected = true;
			m_PointerCircle.setFillColor(m_aMapColors[swamp]);
		}

		//click Generate
		if (sf::FloatRect(m_MapButtons[generate].getPosition(), m_MenuButtons[generate].getSize()).contains(float(checkPos.x), float(checkPos.y)) && m_bTypeSelected)
		{
			m_PointerCircle.setFillColor(sf::Color::Transparent);
			bGenerate = true;
			for (int i = 0; i < m_vMapCircles.size(); i++)
				m_vMapCircles[i].setFillColor(sf::Color::Transparent);
		}

		//click Back
		if (sf::FloatRect(m_MapButtons[back].getPosition(), m_MenuButtons[back].getSize()).contains(float(checkPos.x), float(checkPos.y)))
		{
			m_bTypeSelected = false;
			m_bOnMenu = true;
		}

		//click Inside Map Element
		if (sf::FloatRect(m_MapBox.getPosition(), m_MapBox.getSize()).contains(float(checkPos.x), float(checkPos.y)) && m_bTypeSelected)
		{
			m_vMapCircles.push_back(m_PointerCircle);
			m_vMapCircles.back().setPosition(sf::Vector2f(float(checkPos.x), float(checkPos.y)));
			return true;
		}
		//end of buttons
	}

	return false;
}

//GET SIZE OF MAP ELEMENT
sf::Vector2f UIManager::getMapSize()
{
	return m_MapBox.getSize();
}

//GET POSITION OF MAP ELEMENT
sf::Vector2f UIManager::getMapPosition()
{
	return m_MapBox.getPosition();
}

void UIManager::moveCircle(sf::Window& window)
{
	m_PointerCircle.setPosition(sf::Vector2f(float(sf::Mouse::getPosition(window).x), float(sf::Mouse::getPosition(window).y)));
}

void UIManager::setCircle()
{
	m_bCircleActive = !m_bCircleActive;
}

bool UIManager::loadFont(std::string sFontPath)
{
	if (!m_Font.loadFromFile(sFontPath))
		return false;

	for (int i = 0; i < s_kiNumMenuButtons; i++)
		m_MenuText[i].setFont(m_Font);

	for (int i = 0; i < s_kiNumMapButtons; i++)
		m_MapText[i].setFont(m_Font);

	return true;
	//This font was downloaded from 1001fonts.com
	//ASCOTA Font is created by Andrian Dehasta and Situjuh Nazara
}

//DRAW UI
void UIManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_bOnMenu)
	{
		//target.draw(m_MenuBackground);
		target.draw(m_MenuBox, states);

		for (int i = 0; i < s_kiNumMenuButtons; i++)
		{
			target.draw(m_MenuButtons[i], states);
			target.draw(m_MenuText[i], states);
		}
	}
	else
	{
		target.draw(m_MapUIBox, states);

		for (int i = 0; i < s_kiNumMapButtons; i++)
		{
			target.draw(m_MapButtons[i], states);
			target.draw(m_MapText[i], states);
		}

		if (m_bTypeSelected)
		{
			target.draw(m_PointerCircle, states);
			for (int i = 0; i < m_vMapCircles.size(); i++)
				target.draw(m_vMapCircles[i], states);
		}
	}
}