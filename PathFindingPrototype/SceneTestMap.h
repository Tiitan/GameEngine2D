#pragma once

#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "Engine/ASceneBase.h"
#include "Engine/AObject.h"
#include "MapHexa.h"
#include "Camera.h"

class SceneTestMap : public Engine::ASceneBase
{
	MapHexa		map;
	Camera		camera;

public:
	sf::Font	debugFont;
	sf::Text	debugText;

	SceneTestMap();
	~SceneTestMap();

	virtual void Init();
	virtual void Update(double deltaTime);
	virtual void Draw();

};

