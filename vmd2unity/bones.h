#pragma once
#include <vector>
#include <string>

struct Bone {
	Bone(std::string nm) : name(nm) {}

	std::string name;
	std::vector<Bone> children;
};

struct Armature {
	std::string name;
	std::vector<Bone> bones;

	static Armature FromFile(std::string path);
};