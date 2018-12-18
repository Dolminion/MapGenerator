#include "generator.h"

Generator::Generator(unsigned int uiWindowSize, float fFPS, int iMapSize)
{
	m_uiWindowSize = uiWindowSize;
	m_fFPS = fFPS;
	m_iMapSize = iMapSize;
	m_bOnMenu = true;
	m_bGenerate = false;
	m_bStart = false;
	m_bExit = false;

	m_UIManager = UIManager(m_uiWindowSize);
	m_fTileSize = float(m_UIManager.getMapSize().x / m_iMapSize);

	for (int i = 0; i < m_iMapSize; i++)
	{
		m_vMapRandomiserOne.push_back(i);
		m_vMapRandomiserTwo.push_back(i);
	}

	std::random_shuffle(m_vMapRandomiserOne.begin(), m_vMapRandomiserOne.end());
	std::random_shuffle(m_vMapRandomiserTwo.begin(), m_vMapRandomiserTwo.end());
}

//Initialise Map
void Generator::populateMap()
{
	sf::Vector2f mapPosition = m_UIManager.getMapPosition();

	//create 2d grid of MapTiles, set position and size and color
	for (int i = 0; i < m_iMapSize; i++)
	{
		m_vMapGrid.push_back(std::vector<MapTile>());

		for (int j = 0; j < m_iMapSize; j++)
		{
			m_vMapGrid[i].push_back(MapTile());
			m_vMapGrid[i][j].setSize(sf::Vector2f(m_fTileSize, m_fTileSize));
			m_vMapGrid[i][j].setPosition(mapPosition.x + (i * m_fTileSize), mapPosition.y + (j * m_fTileSize));
			m_vMapGrid[i][j].setFillColor(sf::Color(int((i + j) / 2), int((i + j) / 2),int((i+j)/2),255));
			/*m_vMapGrid[i][j].setOutlineColor(sf::Color::Black);
			m_vMapGrid[i][j].setOutlineThickness(2.f);*/
		}
	}
}

void Generator::processClick(sf::Window& window)
{
	if (m_UIManager.checkBounds(sf::Mouse::getPosition(window), m_bStart, m_bGenerate, m_bExit, m_sButtonClicked))
	{
		sf::Vector2i tileNum;									//tileNum = m_UIManager.findTile(sf::Mouse::getPosition(window), m_iMapSize);
		tileNum = findTile(sf::Mouse::getPosition(window));
		std::cout << tileNum.x << "," << tileNum.y << std::endl; //DEBUG
		nearestNeighbour(tileNum, m_sButtonClicked);
	}

}

//find which tile is being selected
sf::Vector2i Generator::findTile(sf::Vector2i checkPos)
{
	//interpolate position of mouse with position in 2d array
	sf::Vector2f mapPos = m_UIManager.getMapPosition();
	sf::Vector2f mapSize = m_UIManager.getMapSize();
	int iX;
	int iY;

	iX = m_iMapSize * float((checkPos.x - (m_UIManager.getMapPosition().x)) / m_UIManager.getMapSize().x);
	iY = m_iMapSize * float((checkPos.y - (m_UIManager.getMapPosition().y)) / m_UIManager.getMapSize().y);

	return sf::Vector2i(iX, iY);
}

void Generator::nearestNeighbour(sf::Vector2i tileNumber, std::string sTileType)
{
	for (int i = 0; i < m_iMapSize; i++)
	{
		for (int j = 0; j < m_iMapSize; j++)
		{
			m_vMapGrid[i][j].compareSites(sf::Vector2i(m_vMapGrid[tileNumber.x][tileNumber.y].getPosition()), sTileType);
		}
	}
}

void Generator::smoothMap()
{
	std::string environmentType;

	//for each tile
	for (int i = 0; i < m_iMapSize; i++)
	{
		for (int j = 0; j < m_iMapSize; j++)
		{
			std::string neighbourType;
			int ocean = 0,
				water = 0,
				sand = 0,
				grass = 0,
				forest = 0,
				rock = 0,
				snow = 0,
				lava = 0;

			environmentType = m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].getEnvironmentType();

			//for each surrounding tile, alter parameters based on their type
			for (int k = m_vMapRandomiserOne[i] - 1; k < m_vMapRandomiserOne[i] + 2; k++)
			{
				for (int l = m_vMapRandomiserTwo[j] - 1; l < m_vMapRandomiserTwo[j] + 2; l++)
				{
					if (!(k < 0 || k > m_iMapSize - 1 || l < 0 || l > m_iMapSize - 1))
					{
						if (!(k == m_vMapRandomiserOne[i] && l == m_vMapRandomiserTwo[j]))
						{
							neighbourType = m_vMapGrid[k][l].getTerrainType();
							if (neighbourType == "ocean")
								ocean++;
							if (neighbourType == "water")
								water++;
							if (neighbourType == "sand")
								sand++;
							if (neighbourType == "grass")
								grass++;
							if (neighbourType == "forest")
								forest++;
							if (neighbourType == "rock")
								rock++;
							if (neighbourType == "snow")
								snow++;
							if (neighbourType == "lava")
								lava++;
						}
					}

					if (m_vMapRandomiserOne[i] == 0 || m_vMapRandomiserOne[i] == (m_iMapSize - 1) || m_vMapRandomiserTwo[j] == 0 || m_vMapRandomiserTwo[j] == (m_iMapSize - 1))
					{
						if (environmentType == "ocean")
							m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("ocean");
						if (environmentType == "grassland")
							m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("grass");
						if (environmentType == "forest")
							m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("forest");
						if (environmentType == "desert")
							m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("sand");
						if (environmentType == "mountains")
							m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("rock");
						if (environmentType == "volcano")
							m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("lava");
						if (environmentType == "swamp")
							m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("swamp");
					}
					else
					{
						if (environmentType == "ocean")
						{
							if (ocean > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("ocean");
							if (water > 3)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("water");
							if (sand > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("sand");
							if (grass > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("grass");
							if (forest > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("forest");
							if (rock > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("rock");
							if (snow > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("snow");
							if (lava > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("lava");
						}

						if (environmentType == "grassland")
						{
							if (ocean > 3)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("ocean");
							if (water > 2)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("water");
							if (sand > 3)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("sand");
							if (grass > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("grass");
							if (forest > 3)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("forest");
							if (rock > 3)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("rock");
							if (snow > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("snow");
							if (lava > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("lava");
						}

						if (environmentType == "forest")
						{
							if (ocean > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("ocean");
							if (water > 2)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("water");
							if (sand > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("sand");
							if (grass > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("grass");
							if (forest > 5)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("forest");
							if (rock > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("rock");
							if (snow > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("snow");
							if (lava > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("lava");
						}

						if (environmentType == "desert")
						{
							if (ocean > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("ocean");
							if (water > 3)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("water");
							if (sand > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("sand");
							if (grass > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("grass");
							if (forest > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("forest");
							if (rock > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("rock");
							if (snow > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("snow");
							if (lava > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("lava");
						}

						if (environmentType == "mountains")
						{
							if (ocean > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("ocean");
							if (water > 3)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("water");
							if (sand > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("sand");
							if (grass > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("grass");
							if (forest > 3)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("forest");
							if (rock > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("rock");
							if (snow > 3)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("snow");
							if (lava > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("lava");
						}

						if (environmentType == "volcano")
						{
							if (ocean > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("ocean");
							if (water > 5)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("water");
							if (sand > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("sand");
							if (grass > 5)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("grass");
							if (forest > 5)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("forest");
							if (rock > 3)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("rock");
							if (snow > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("snow");
							if (lava > 3)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("lava");
						}

						if (environmentType == "swamp")
						{
							if (ocean > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("ocean");
							if (water > 2)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("water");
							if (sand > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("sand");
							if (grass > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("grass");
							if (forest > 3)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("forest");
							if (rock > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("rock");
							if (snow > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("snow");
							if (lava > 4)
								m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("lava");
						}
					}
				}
			}
		}
	}
}

bool Generator::exit()
{
	return m_bExit;
}

bool Generator::loadFont(std::string sFontPath)
{
	return m_UIManager.loadFont(sFontPath);
}

void Generator::update(float fElapsedTime, sf::Window& window)
{
	m_bOnMenu = m_UIManager.onMenu();
	if (!m_bOnMenu)
	{
		m_UIManager.moveCircle(window);
	}

	if (m_bStart)
	{
		populateMap();
		m_bStart = false;
	}
	//if generate has been clicked, set the type for each element in the map grid
	if (m_bGenerate)
	{
		std::string otherEnvironmentType;
		std::string environmentType;

		for (int i = 0; i < m_iMapSize; i++)
		{
			for (int j = 0; j < m_iMapSize; j++)
			{
				m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType(m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].pickType());

				environmentType = m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].getEnvironmentType();

				for (int k = m_vMapRandomiserOne[i] - 1; k < m_vMapRandomiserOne[i] + 2; k++)
				{
					for (int l = m_vMapRandomiserTwo[j] - 1; l < m_vMapRandomiserTwo[j] + 2; l++)
					{
						if (!(k < 0 || k > m_iMapSize - 1 || l < 0 || l > m_iMapSize - 1))
						{
							otherEnvironmentType = m_vMapGrid[k][l].getEnvironmentType();

							if (otherEnvironmentType != environmentType)
							{
								if (environmentType == "ocean")
									m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("water");

								if (environmentType == "grassland")
								{
									if (otherEnvironmentType == "ocean")
										m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("sand");
								}

								if (environmentType == "forest")
								{
									if (otherEnvironmentType == "ocean")
										m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("sand");
								}

								if (environmentType == "desert")
								{

								}

								if (environmentType == "mountains")
									m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("rock");

								if (environmentType == "volcano")
									m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("rock");

								if (environmentType == "swamp")
									m_vMapGrid[m_vMapRandomiserOne[i]][m_vMapRandomiserTwo[j]].setType("forest");
							}
						}
					}
				}
			}
		}

		for (int i = 0; i < 3; i++)
			smoothMap();

		m_bGenerate = false;
		m_UIManager.setCircle();
	}
}

void Generator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(!m_bOnMenu)
		for (int i = 0; i < m_iMapSize; i++)
		{
			for (int j = 0; j < m_iMapSize; j++)
			{
				target.draw(m_vMapGrid[i][j], states);
			}
		}

	m_UIManager.draw(target, states);
}