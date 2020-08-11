#pragma once
#include "Math/Vector2.h"

namespace nc {
	const float PI      = 3.14159265358979f;
	const float TWO_PI  = PI * 2;
	const float HALF_PI = PI / 0.5f;

	inline float rtod(float radians) {
		return radians * (180.0f / PI);
	}
	inline float dtor(float degrees) {
		return degrees * (PI / 180.0f);
	}

	template <typename T>
	
	inline T Clamp(T v, T min, T max) {
		if (v < min) v = min;
		if (v > max) v = max;
		return v;
	}
	
	template <>
	inline nc::Vector2 Clamp<nc::Vector2>(nc::Vector2 v, nc::Vector2 min, nc::Vector2 max)
	{
		v.x = Clamp(v.x, min.x, max.x);
		v.y = Clamp(v.y, min.y, max.y);

		return v;
	}

	template <typename T>
	inline T Lerp(T a, T b, float t) {
		return (a + ((b - a) * t));
	}

}
