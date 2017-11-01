#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Math.h"
#include "bones.h"

struct VMD_MOTION_KEYFRAME {
	std::string name, path;
	Bone* bone;
	unsigned int frame;
	Vec3 position;
	Quat rotation;
};

struct VMD_MOTION_DATA {
	std::string signature, modelName;
	unsigned int frameCount;
	std::vector<VMD_MOTION_KEYFRAME> keyframes;
	std::unordered_map<std::string, std::vector<VMD_MOTION_KEYFRAME*>> keyframes_n;
	Armature* armature;

	void Rename(std::string bonedatapath);
	void DumpNames(std::string path), DumpData(std::string path);
	void SortFrames();
	void AttachBones(Armature& arm);
	static VMD_MOTION_DATA FromFile(const std::string& path);
};