#include "Camera.h"

Camera::Camera() :
	ACameraBase(),
	zoomSpeed(30),
	maxZoom(50),
	minZoom(10),
	moveSpeed(500)
{
}


Camera::~Camera()
{
}

void Camera::Init()
{

}

void Camera::Update(double deltaTime)
{
	Engine::Vector2d translation;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		translation.x--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		translation.x++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		translation.y--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		translation.y++;
	
	if (translation.SqrMagnitude() > 1)
		translation.Normalize();
	position += translation * deltaTime * moveSpeed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		zoom -= deltaTime * zoomSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		zoom += deltaTime * zoomSpeed;
	zoom = Engine::MathUtils::clip(zoom, minZoom, maxZoom);
}

void Camera::Draw()
{

}
