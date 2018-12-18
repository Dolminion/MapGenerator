#pragma once
#include <string>
#include <math.h>
#include <time.h>

class TileType
{
private:
	static const int s_kiNumParams = 8;
	float m_afParams[s_kiNumParams];
	enum m_Types 
	{
		ocean,
		water,
		sand,
		grass,
		forest,
		rock,
		snow,
		lava
	};

	std::string m_sPickedType;

public:
	TileType();
	void typeParameters(std::string typeName);
	/*void editParameters(std::string typeName);
	void normaliseParameters();*/
	std::string pickType();
};