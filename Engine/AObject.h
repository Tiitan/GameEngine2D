#pragma once

#include "Vector2d.h"

namespace Engine
{
	class AObject
	{
	protected:
		Vector2d position;

	public:
		AObject();
		virtual ~AObject();

		virtual void Init() = 0;
		virtual void Update(double deltaTime) = 0;
		virtual void Draw() = 0;

		Vector2d const& GetPosition() const;
	};
}