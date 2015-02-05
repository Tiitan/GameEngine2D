#pragma once

#include <SFML/Graphics.hpp>
#include "Engine/Game.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include "Engine/ACameraBase.h"
#include "Engine/MathUtils.h"
#include "Engine/Vector2i.h"
#include "MapHexa.h"

#define SQRT3_2 0.86602540378 // sqrt(3) / 2

enum HexaType
{
	normal = 0,
	blocking,
	start,
	end,
};

sf::Color const colorArray[] =	
{
	sf::Color::Green,			// 0 normal
	sf::Color::Red,				// 1 blocking
	sf::Color::Blue,			// 2 start
	sf::Color::Cyan,			// 3 end
};

class MapHexa;
class Hexa : private sf::ConvexShape
{
	MapHexa*		 map;

	Engine::Vector2d position;
	Engine::Vector2i coordinate;
	HexaType		 type;

	void SetColor(sf::Color const& color);

public:
	// pathfinding data
	Hexa*			 cameFrom;
	double			 gScore;
	double			 hScore;
	bool			 isPath;

	sf::Text		 text;

	Hexa();
	Hexa(HexaType type);
	~Hexa();

	Engine::Vector2d const& GetPosition() const;

	void init(MapHexa&, Engine::Vector2i&);
	void Draw(sf::RenderWindow& window, Engine::ACameraBase const& camera, MapHexa const& map);

	void OnMouseEnterOver();
	void OnMouseLeaveOver();
		
	HexaType GetType() const;
	void SetType(HexaType val);
	Engine::Vector2i const& GetCoordinate() const;

	double GetFScore() const;
	double GetGScore() const;
	double GetHScore() const;
};

