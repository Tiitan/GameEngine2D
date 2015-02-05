#pragma once

#include "MathUtils.h"

namespace Engine
{
	class Vector2d
	{
	public:
		double x;
		double y;
		
		Vector2d();
		Vector2d(double x, double y);
		Vector2d(Vector2d const& other);
		~Vector2d();

		Vector2d operator+(Vector2d const& other) const;
		Vector2d operator-(Vector2d const& other) const;
		Vector2d operator*(Vector2d const& other) const;
		Vector2d operator/(Vector2d const& other) const;

		Vector2d& operator+=(Vector2d const& other);
		Vector2d& operator-=(Vector2d const& other);
		Vector2d& operator*=(Vector2d const& other);
		Vector2d& operator/=(Vector2d const& other);
		Vector2d& operator=(Vector2d const& other);

		Vector2d operator+(double value) const;
		Vector2d operator-(double value) const;
		Vector2d operator*(double value) const;
		Vector2d operator/(double value) const;

		Vector2d& operator+=(double value);
		Vector2d& operator-=(double value);
		Vector2d& operator*=(double value);
		Vector2d& operator/=(double value);

		double Distance(Vector2d const &other) const;
		void Normalize();
		Vector2d Normalized() const;
		double Magnitude() const;
		double SqrMagnitude() const;
	};
}