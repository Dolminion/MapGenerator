#include "tileType.h"

TileType::TileType()
{

}

//set initial parameters for cellular automaton based on terrain type
void TileType::typeParameters(std::string typeName)
{
	if (typeName == "ocean")
	{
		m_afParams[ocean] = 100.f;
		m_afParams[water] = 0.f;
		m_afParams[sand] = 0.f;
		m_afParams[grass] = 0.f;
		m_afParams[forest] = 0.f;
		m_afParams[rock] = 0.f;
		m_afParams[snow] = 0.f;
		m_afParams[lava] = 0.f;
	}

	if (typeName == "grassland")
	{
		m_afParams[ocean] = 0.f;
		m_afParams[water] = 15.f;
		m_afParams[sand] = 0.f;
		m_afParams[grass] = 65.f;
		m_afParams[forest] = 15.f;
		m_afParams[rock] = 5.f;
		m_afParams[snow] = 0.f;
		m_afParams[lava] = 0.f;
	}

	if (typeName == "forest")
	{
		m_afParams[ocean] = 0.f;
		m_afParams[water] = 10.f;
		m_afParams[sand] = 0.f;
		m_afParams[grass] = 10.f;
		m_afParams[forest] = 80.f;
		m_afParams[rock] = 0.f;
		m_afParams[snow] = 0.f;
		m_afParams[lava] = 0.f;
	}

	if (typeName == "desert")
	{
		m_afParams[ocean] = 0.f;
		m_afParams[water] = 20.f;
		m_afParams[sand] = 70.f;
		m_afParams[grass] = 0.f;
		m_afParams[forest] = 10.f;
		m_afParams[rock] = 0.f;
		m_afParams[snow] = 0.f;
		m_afParams[lava] = 0.f;
	}

	if (typeName == "mountains")
	{
		m_afParams[ocean] = 0.f;
		m_afParams[water] = 15.f;
		m_afParams[sand] = 0.f;
		m_afParams[grass] = 0.f;
		m_afParams[forest] = 15.f;
		m_afParams[rock] = 50.f;
		m_afParams[snow] = 20.f;
		m_afParams[lava] = 0.f;
	}

	if (typeName == "volcano")
	{
		m_afParams[ocean] = 0.f;
		m_afParams[water] = 0.f;
		m_afParams[sand] = 0.f;
		m_afParams[grass] = 0.f;
		m_afParams[forest] = 0.f;
		m_afParams[rock] = 50.f;
		m_afParams[snow] = 0.f;
		m_afParams[lava] = 50.f;
	}

	if (typeName == "swamp")
	{
		m_afParams[ocean] = 0.f;
		m_afParams[water] = 50.f;
		m_afParams[sand] = 0.f;
		m_afParams[grass] = 0.f;
		m_afParams[forest] = 50.f;
		m_afParams[rock] = 0.f;
		m_afParams[snow] = 0.f;
		m_afParams[lava] = 0.f;
	}
}
/*
//typeName is next to current tile, thus edit type
void TileType::editParameters(std::string typeName)
{
	if (typeName == "ocean")
		m_afParams[ocean] += 10.f;

	if (typeName == "water")
		m_afParams[water] += 10.f;

	if (typeName == "sand")
		m_afParams[sand] += 10.f;

	if (typeName == "grass")
		m_afParams[grass] += 10.f;

	if (typeName == "forest")
		m_afParams[forest] += 10.f;

	if (typeName == "rock")
		m_afParams[rock] += 10.f;

	if (typeName == "snow")
		m_afParams[snow] += 10.f;

	if (typeName == "lava")
		m_afParams[lava] += 10.f;
}

//make all the parameters add up to 100
void TileType::normaliseParameters()
{
	float paramTotal = 0;
	float scalar;

	for (int i = 0; i < s_kiNumParams; i++)
	{
		paramTotal += m_afParams[i];
	}

	scalar = 100 / paramTotal;

	for (int i = 0; i < s_kiNumParams; i++)
	{
		m_afParams[i] = m_afParams[i] * scalar;
	}
}
*/
std::string TileType::pickType()
{

	int randomNum;
	int chanceCounter = 0;
	bool typePicked = false;

	randomNum = rand() % 100;

	for (int i = 0; i < s_kiNumParams; i++)
	{
		if (m_afParams[i] != 0)
		{
			chanceCounter += m_afParams[i];

			if (randomNum < chanceCounter)
			{
				switch (i)
				{
				case ocean:
					m_sPickedType = "ocean";
					typePicked = true;
					break;
				case water:
					m_sPickedType = "water";
					typePicked = true;
					break;
				case sand:
					m_sPickedType = "sand";
					typePicked = true; 
					break;
				case grass:
					m_sPickedType = "grass";
					typePicked = true; 
					break;
				case forest:
					m_sPickedType = "forest";
					typePicked = true; 
					break;
				case rock:
					m_sPickedType = "rock";
					typePicked = true; 
					break;
				case snow:
					m_sPickedType = "snow";
					typePicked = true; 
					break;
				case lava:
					m_sPickedType = "lava";
					typePicked = true; 
					break;
				}
			}
		}
		if (typePicked)
			i = s_kiNumParams;
	}
	return m_sPickedType;
}