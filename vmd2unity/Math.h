#pragma once

#include <string>

struct Vec3 {
	Vec3(float x=0, float y=0, float z=0) : x(x), y(y), z(z) {}

	float x, y, z;

	std::string string();
};

struct Quat {
	Quat(float x = 0, float y = 0, float z = 0, float w = 0) : x(x), y(y), z(z), w(w) {}

	float x, y, z, w;

	std::string string();
};