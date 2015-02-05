#pragma once

#include "AObject.h"

namespace Engine
{
	class ACameraBase : public AObject
	{
	protected:
		double	zoom;

	public:
		ACameraBase();
		virtual ~ACameraBase();

		double GetZoom() const;
	};
}