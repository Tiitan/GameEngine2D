#include "Hexa.h"

Hexa::Hexa() :
	sf::ConvexShape(),
	type(HexaType::normal)
{
}

Hexa::Hexa(HexaType type) :
	sf::ConvexShape(),
	type(type)
{
}

void Hexa::init(MapHexa& map, Engine::Vector2i& coord)
{
	this->map = &map;
	coordinate = coord;
	gScore = -1;
	hScore = -1;
	isPath = false;
	cameFrom = NULL;

	setPointCount(6);
	for (int i = 0; i < 6; i++)
	{
		double angle = 2 * M_PI / 6 * (i + 0.5);
		setPoint(i, sf::Vector2f((float)cos(angle), (float)sin(angle)));
	}
	setFillColor(sf::Color::Green);
	setOutlineColor(sf::Color::Yellow);

	text.setFont(map.debugFont);
	text.setCharacterSize(14);
	text.setColor(sf::Color::Color(255, 128, 0, 255));
}

Hexa::~Hexa()
{
}

void Hexa::Draw(sf::RenderWindow& window, Engine::ACameraBase const& camera, MapHexa const& map)
{
	setScale((float)camera.GetZoom(), (float)camera.GetZoom());
	setPosition((float)((coordinate.x * map.GetHexaWidth() + coordinate.y * 0.5 * map.GetHexaWidth()) - camera.GetPosition().x),
				(float)(coordinate.y * 0.75 * map.GetHexaHeight() - camera.GetPosition().y));
	SetColor(isPath ? sf::Color::Yellow : colorArray[(int)type]);
	window.draw(*this);


	std::stringstream ss;
	ss << std::setprecision(2) << hScore << std::endl << gScore;
	text.setString(ss.str());
	text.setPosition(sf::Vector2f(getPosition().x - getLocalBounds().width * 5, 
								  getPosition().y - getLocalBounds().height * 10));
	Engine::Game::Singleton->GetWindow().draw(text);
}

void Hexa::OnMouseEnterOver()
{
	setOutlineThickness(-0.03f);
}

void Hexa::OnMouseLeaveOver()
{
	setOutlineThickness(0);
}

void Hexa::SetColor(sf::Color const& color)
{
	setFillColor(color);
}

Engine::Vector2d const& Hexa::GetPosition() const
{
	return position;
}

HexaType Hexa::GetType() const 
{ 
	return type; 
}

void Hexa::SetType(HexaType val) 
{ 
	type = val; 
}

Engine::Vector2i const& Hexa::GetCoordinate() const
{
	return coordinate;
}

double Hexa::GetFScore() const
{
	return gScore + hScore;
}

double Hexa::GetGScore() const
{
	return gScore;
}

double Hexa::GetHScore() const
{
	return hScore;
}