#pragma once

namespace Engine
{
	class Vector2i
	{
	public:
		int x;
		int y;

		Vector2i();
		Vector2i(int x, int y);
		Vector2i(Vector2i const& other);
		~Vector2i();

		Vector2i operator+(Vector2i const& other) const;
		Vector2i operator-(Vector2i const& other) const;
		Vector2i operator*(Vector2i const& other) const;
		Vector2i operator/(Vector2i const& other) const;

		Vector2i& operator+=(Vector2i const& other);
		Vector2i& operator-=(Vector2i const& other);
		Vector2i& operator*=(Vector2i const& other);
		Vector2i& operator/=(Vector2i const& other);
		Vector2i& operator=(Vector2i const& other);

		Vector2i operator+(int value) const;
		Vector2i operator-(int value) const;
		Vector2i operator*(int value) const;
		Vector2i operator/(int value) const;

		Vector2i& operator+=(int value);
		Vector2i& operator-=(int value);
		Vector2i& operator*=(int value);
		Vector2i& operator/=(int value);
	};
}