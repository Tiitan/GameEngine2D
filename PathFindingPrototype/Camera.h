#pragma once

#include <SFML/Graphics.hpp>
#include "Engine/MathUtils.h"
#include "Engine/ACameraBase.h"

class Camera : public Engine::ACameraBase
{
	double			zoomSpeed;
	double			maxZoom;
	double			minZoom;
	double			moveSpeed;

public:

	Camera();
	~Camera();

	virtual void Init();
	virtual void Update(double deltaTime);
	virtual void Draw();

	double getZoom() const;
};