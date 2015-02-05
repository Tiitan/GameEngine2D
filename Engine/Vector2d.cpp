#include "Vector2d.h"

using namespace Engine;

Vector2d::Vector2d() :
	x(0),
	y(0)
{
}

Vector2d::Vector2d(double x, double y) :
x(x),
y(y)
{
}

Vector2d::Vector2d(Vector2d const& other) :
x(other.x),
y(other.y)
{
}

Vector2d::~Vector2d()
{
}

Vector2d Vector2d::operator+(Vector2d const& other) const
{
	return Vector2d (this->x + other.x, this->y + other.y);
}

Vector2d Vector2d::operator-(Vector2d const& other) const
{
	return Vector2d(this->x - other.x, this->y - other.y);
}

Vector2d Vector2d::operator*(Vector2d const& other) const
{
	return Vector2d(this->x * other.x, this->y * other.y);
}

Vector2d Vector2d::operator/(Vector2d const& other) const
{
	return Vector2d(this->x / other.x, this->y / other.y);
}

Vector2d& Vector2d::operator+=(Vector2d const& other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Vector2d& Vector2d::operator-=(Vector2d const& other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

Vector2d& Vector2d::operator*=(Vector2d const& other)
{
	this->x *= other.x;
	this->y *= other.y;
	return *this;
}

Vector2d& Vector2d::operator/=(Vector2d const& other)
{
	this->x /= other.x;
	this->y /= other.y;
	return *this;
}

Vector2d& Vector2d::operator=(Vector2d const& other)
{
	this->x = other.x;
	this->y = other.y;
	return *this;
}

Vector2d Vector2d::operator+(double value) const
{
	return Vector2d(this->x + value, this->y + value);
}

Vector2d Vector2d::operator-(double value) const
{
	return Vector2d(this->x - value, this->y - value);
}

Vector2d Vector2d::operator*(double value) const
{
	return Vector2d(this->x * value, this->y * value);
}

Vector2d Vector2d::operator/(double value) const
{
	return Vector2d(this->x / value, this->y / value);
}

Vector2d& Vector2d::operator+=(double value)
{
	this->x += value;
	this->y += value;
	return *this;
}

Vector2d& Vector2d::operator-=(double value)
{
	this->x -= value;
	this->y -= value;
	return *this;
}

Vector2d& Vector2d::operator*=(double value)
{
	this->x *= value;
	this->y *= value;
	return *this;
}

Vector2d& Vector2d::operator/=(double value)
{
	this->x /= value;
	this->y /= value;
	return *this;
}

double Vector2d::Distance(Vector2d const &other) const
{
	return (this->x - other.x) * (this->x - other.x) + (this->y - other.y) * (this->y - other.y);
}

void Vector2d::Normalize()
{
	double lengh = Magnitude();
	
	if (lengh != 0)
	{
		x /= lengh;
		y /= lengh;
	}
}

Vector2d Vector2d::Normalized() const
{
	Vector2d out;

	if (x != 0 || y != 0)
	{
		double lengh = Magnitude();
		out.x = x / lengh;
		out.y = y / lengh;
	}

	return out;
}
double Vector2d::Magnitude() const
{
	return sqrt((x * x) + (y * y));
}

double Vector2d::SqrMagnitude() const
{
	return (x * x) + (y * y);
}