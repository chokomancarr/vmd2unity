#pragma once
#include <string>
#include <vector>
#include "Math.h"

struct VMD_MOTION_KEYFRAME {
	std::string name, path;
	unsigned int frame;
	Vec3 position;
	Quat rotation;
};

struct VMD_MOTION_DATA {

	std::string signature, modelName;
	unsigned int frameCount;
	std::vector<VMD_MOTION_KEYFRAME> keyframes;

	void Rename(std::string bonedatapath);
	void DumpNames(std::string path), DumpData(std::string path);
	void SortFrames();
	static VMD_MOTION_DATA FromFile(const std::string& path);
};