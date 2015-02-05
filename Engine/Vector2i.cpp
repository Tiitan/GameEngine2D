#include "Vector2i.h"

using namespace Engine;

Vector2i::Vector2i() :
x(0),
y(0)
{
}

Vector2i::Vector2i(int x, int y) :
x(x),
y(y)
{
}

Vector2i::Vector2i(Vector2i const& other) :
x(other.x),
y(other.y)
{
}

Vector2i::~Vector2i()
{
}

Vector2i Vector2i::operator+(Vector2i const& other) const
{
	return Vector2i(this->x + other.x, this->y + other.y);
}

Vector2i Vector2i::operator-(Vector2i const& other) const
{
	return Vector2i(this->x - other.x, this->y - other.y);
}

Vector2i Vector2i::operator*(Vector2i const& other) const
{
	return Vector2i(this->x * other.x, this->y * other.y);
}

Vector2i Vector2i::operator/(Vector2i const& other) const
{
	return Vector2i(this->x / other.x, this->y / other.y);
}

Vector2i& Vector2i::operator+=(Vector2i const& other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Vector2i& Vector2i::operator-=(Vector2i const& other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

Vector2i& Vector2i::operator*=(Vector2i const& other)
{
	this->x *= other.x;
	this->y *= other.y;
	return *this;
}

Vector2i& Vector2i::operator/=(Vector2i const& other)
{
	this->x /= other.x;
	this->y /= other.y;
	return *this;
}

Vector2i& Vector2i::operator=(Vector2i const& other)
{
	this->x = other.x;
	this->y = other.y;
	return *this;
}

Vector2i Vector2i::operator+(int value) const
{
	return Vector2i(this->x + value, this->y + value);
}

Vector2i Vector2i::operator-(int value) const
{
	return Vector2i(this->x - value, this->y - value);
}

Vector2i Vector2i::operator*(int value) const
{
	return Vector2i(this->x * value, this->y * value);
}

Vector2i Vector2i::operator/(int value) const
{
	return Vector2i(this->x / value, this->y / value);
}

Vector2i& Vector2i::operator+=(int value)
{
	this->x += value;
	this->y += value;
	return *this;
}

Vector2i& Vector2i::operator-=(int value)
{
	this->x -= value;
	this->y -= value;
	return *this;
}

Vector2i& Vector2i::operator*=(int value)
{
	this->x *= value;
	this->y *= value;
	return *this;
}

Vector2i& Vector2i::operator/=(int value)
{
	this->x /= value;
	this->y /= value;
	return *this;
}