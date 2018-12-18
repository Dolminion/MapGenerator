#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <math.h>
#include "tileType.h"

class MapTile : public sf::RectangleShape
{
private:
	sf::Vector2i m_NearestNeighbour;
	TileType m_TileType;
	std::string m_sEnvironment;
	std::string m_sTerrain;

public:
	MapTile();
	void compareSites(sf::Vector2i sitePos, std::string sTileType);
	float findMagnitude(sf::Vector2i pointOne, sf::Vector2i pointTwo);
	std::string pickType();
	void setType(std::string terrainType);
	std::string getEnvironmentType();
	std::string getTerrainType();
	/*void alterParameters(std::string sTileType);
	void normaliseParameters();*/
};