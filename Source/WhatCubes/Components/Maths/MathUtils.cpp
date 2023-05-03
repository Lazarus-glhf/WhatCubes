#include "MathUtils.h"
#include <cmath>

Double MathUtils::Clamp(Double A, Double Min, Double Max)
{
	return std::clamp(A, Min, Max);
}

Double MathUtils::Square(Double A)
{
	return A * A;
}

Double MathUtils::Cube(Double A)
{
	return A * A * A;
}

Double MathUtils::Hypot(Double X, Double Y)
{
	return std::hypot(X, Y);
}

Double MathUtils::Hypot(Double X, Double Y, Double Z)
{
	return std::hypot(X, Y, Z);
}

Double MathUtils::Floor(Double A)
{
	return std::floor(A);
}

Double MathUtils::Ceil(Double A)
{
	return std::ceil(A);
}

Double MathUtils::FloorMod(Long A, Long B)
{
	const Long R = A % B;
	if ((A ^ B) < 0 && R != 0) {
		return R + B;
	}
	return R;
}
