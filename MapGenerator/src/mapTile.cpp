#include "mapTile.h"

MapTile::MapTile()
{
	m_NearestNeighbour = sf::Vector2i(-1, -1);
}

void MapTile::compareSites(sf::Vector2i sitePos, std::string sTileType)
{
	//if first site
	if (m_NearestNeighbour == sf::Vector2i(-1, -1))
	{
		m_NearestNeighbour = sitePos;
		m_sEnvironment = sTileType;
		m_TileType.typeParameters(sTileType);
	}
	//else, already at least one site
	else
		//if new site closer than old site, set new site as nearest
		if (findMagnitude(sf::Vector2i(getPosition().x, getPosition().y), sitePos) <= findMagnitude(sf::Vector2i(getPosition().x, getPosition().y), m_NearestNeighbour))
		{
			m_NearestNeighbour = sitePos;
			m_sEnvironment = sTileType;
			m_TileType.typeParameters(sTileType);
		}
}

//find the distance between two points (the magnitude of the vector)
float MapTile::findMagnitude(sf::Vector2i pointOne, sf::Vector2i pointTwo)
{
	int xOne = pointOne.x;
	int xTwo = pointTwo.x;
	int yOne = pointOne.y;
	int yTwo = pointTwo.y;
	int square;
	float magnitude;

	square = ((xTwo - xOne) * (xTwo - xOne)) + ((yTwo - yOne) * (yTwo - yOne));
	magnitude = float(sqrt(square));
	return magnitude;
}

void MapTile::setType(std::string terrainType)
{
	if (terrainType == "ocean")
	{
		m_sTerrain = "ocean";
		setFillColor(sf::Color(0, 50, 130, 255));
	}

	else if (terrainType == "water")
	{
		m_sTerrain = "water";
		setFillColor(sf::Color(0, 90, 200, 255));
	}

	else if (terrainType == "sand")
	{
		m_sTerrain = "sand";
		setFillColor(sf::Color(240, 230, 60, 255));
	}

	else if (terrainType == "grass")
	{
		m_sTerrain = "grass";
		setFillColor(sf::Color(50, 210, 80, 255));
	}

	else if (terrainType == "forest")
	{
		m_sTerrain = "forest";
		setFillColor(sf::Color(10, 100, 30, 255));
	}

	else if (terrainType == "rock")
	{
		m_sTerrain = "rock";
		setFillColor(sf::Color(100, 100, 100, 255));
	}

	else if (terrainType == "snow")
	{
		m_sTerrain = "snow";
		setFillColor(sf::Color(220, 240, 240, 255));
	}

	else if (terrainType == "lava")
	{
		m_sTerrain = "lava";
		setFillColor(sf::Color(240, 160, 60, 255));
	}
}

std::string MapTile::pickType()
{
	m_sTerrain = m_TileType.pickType();
	return m_sTerrain;
}

std::string MapTile::getEnvironmentType()
{
	return m_sEnvironment;
}

std::string MapTile::getTerrainType()
{
	return m_sTerrain;
}