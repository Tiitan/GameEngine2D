#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <algorithm>
#include "Engine/Game.h"
#include "Engine/AObject.h"
#include "Engine/Vector2d.h"
#include "Engine/Vector2i.h"
#include "Engine/ASceneBase.h"
#include "Engine/ACameraBase.h"
#include "Hexa.h"

class Hexa;
enum HexaType;
class MapHexa : public Engine::AObject
{
	const int				mapLengh;
	const int				mapHeight;

	Engine::ASceneBase&		scene;

	Hexa*				hexas;
	Hexa*				lastOverHexa;

	double				hexaHeigth;
	double				hexaWidth;

	HexaType			selectedType;
	Hexa*				hexaStart;
	Hexa*				hexaEnd;

	std::list<Hexa*>	lastPath;

	bool				DoesHexaExist(int x, int y) const;

public:
	MapHexa(Engine::ASceneBase& scene);
	~MapHexa();
	sf::Font			debugFont;

	void Init();
	void Update(double deltaTime);
	void Draw();

	Engine::Vector2i	GetMouseGridCoordinate() const;
	double				GetHexaHeight() const;
	double				GetHexaWidth() const;

	std::list<Hexa*>	CalculatePath();
	Hexa*				PopLowestFScore(std::list<Hexa*>& openlist);
	Hexa**				GetNeighbor(Hexa* currentHex) const;
	std::list<Hexa*>	ReconstructPath();
	double				HeuristicCostEstimate(Hexa* hexa) const;
};