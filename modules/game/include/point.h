#pragma once

#include "types.h"

template <typename type>
struct point
{
	type x, y;
	point() = default;
	point(type _x, type _y)
		: x(_x)
		, y(_y)
	{ }
};

using pointf = point<float32>;
using pointi = point<int>;

struct worldPoint
{
	worldPoint() = default;
	worldPoint(float32 x, float32 y)
		: p(x, y)
	{ }

	pointf p;
};

struct screenPoint
{
	screenPoint(int x, int y)
		: p(x, y)
	{ }

	pointi p;
};