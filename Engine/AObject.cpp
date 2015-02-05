#include "AObject.h"

using namespace Engine;

AObject::AObject() :
	position()
{
}


AObject::~AObject()
{
}

Vector2d const& Engine::AObject::GetPosition() const
{
	return position;
}
