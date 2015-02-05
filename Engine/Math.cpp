#include "MathUtils.h"

using namespace Engine;

double MathUtils::clip(double n, double lower, double upper)
{
	return std::max(lower, std::min(n, upper));
}
