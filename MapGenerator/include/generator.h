#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include "mapTile.h"
#include "uimanager.h"

class Generator : public sf::Drawable 
{
private:
	unsigned int m_uiWindowSize;
	float m_fFPS;

	int m_iMapSize;
	std::vector<std::vector<MapTile>> m_vMapGrid;
	std::vector<int> m_vMapRandomiserOne;
	std::vector<int> m_vMapRandomiserTwo;

	UIManager m_UIManager;

	bool m_bOnMenu;
	bool m_bGenerate;
	bool m_bStart;
	bool m_bExit;

	float m_fTileSize;

	std::string m_sButtonClicked;

	/*audio
	ui
	vector& lands
	*/

public:
	Generator(unsigned int uiWindowSize, float fFPS, int iMapSize);

	void populateMap();
	void processClick(sf::Window& window);
	sf::Vector2i findTile(sf::Vector2i checkPos);
	void nearestNeighbour(sf::Vector2i tileNumber, std::string sTileType);
	void smoothMap();
	//bool getGenerate();
	//void setTypes(int iI, int iJ);
	bool exit();

	bool loadFont(std::string sFontPath);
	void update(float fElapsedTime, sf::Window& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/*void populateLands();
	void findBiomes();
	void fillLands();
	void smoothLands();*/
	/*loadAudio()
	  loadFont()*/

};