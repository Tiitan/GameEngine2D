#include "ACameraBase.h"

using namespace Engine;

ACameraBase::ACameraBase() :
	AObject(),
	zoom(64)
{
}


ACameraBase::~ACameraBase()
{
}

double ACameraBase::GetZoom() const
{
	return zoom;
}