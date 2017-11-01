#pragma once
#include <vector>
#include <string>

extern char bcname[100];
extern std::string bname;

struct Bone {
	Bone(std::string nm, std::string fnm) : name(nm), fullName(fnm) {}

	std::string name, fullName;
	std::vector<Bone> children;
};

struct Armature {
	std::string name;
	std::vector<Bone> bones;

	static Armature FromFile(std::string path);
};