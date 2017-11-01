#include "stdafx.h"
#include "vmdparse.h"
#include "bones.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>

#define err(msg) { std::cout << msg << std::endl; \
	return data; }
#define RD(tar, sz) strm.read((char*)&tar, sz);

#define GN auto pos = strm.tellg(); strm.getline(bcname, 100); bname = std::string(bcname);

void VMD_MOTION_DATA::Rename(std::string path) {
	std::cout << "Reading map... ";
	std::unordered_map<std::string, std::string> map;
	unsigned int c = 0; //dummy0, dummy1, ...
	std::ifstream strm(path);
	GN; //Armature name
	while (true) {
		GN;
		if (bcname[0] == '&') continue;
		if (bname == "-") break;
		auto eq = bname.find('=');
		if (eq == std::string::npos || (bname.length() < (eq + 2))) continue;
		std::string nm1 = bname.substr(0, eq - 1);
		if (bname.length() == (eq + 2)) {
			map.emplace(nm1, "dummy" + std::to_string(c++));
		}
		std::string nm2 = bname.substr(eq + 2);
		map.emplace(nm1, (nm2=="<") ? nm1 : nm2);
	}
	std::cout << "done" << std::endl << "remapping names... ";
	for (auto& a : keyframes) {
		a.name = map[a.name];
	}
	std::cout << "done" << std::endl;
}

void VMD_MOTION_DATA::DumpNames(std::string path) {
	std::cout << "Dumping names... ";
	std::ofstream strm(path);
	strm << R"(&[name = newname]
&[name = <] means use original name
&[name = ] means do not use name)" << std::endl;
	for (auto& a : keyframes_n) {
		strm << a.first << " = " << std::endl;
	}
	strm << "-";
	std::cout << "done" << std::endl;
}

void VMD_MOTION_DATA::DumpData(std::string path) {
	std::cout << "Dumping data... ";
	std::ofstream strm(path);
	for (auto& a : keyframes)
		strm << std::to_string(a.frame) + " " + a.name + " " + a.position.string() + " " + a.rotation.string() << std::string(a.bone? (" [" + a.bone->fullName + "]") : "") << std::endl;
	std::cout << "done" << std::endl;
}

void VMD_MOTION_DATA::SortFrames() {
	std::cout << "Sorting..." << std::endl;
	std::sort(keyframes.begin(), keyframes.end(), [](VMD_MOTION_KEYFRAME a, VMD_MOTION_KEYFRAME b) {
		return a.frame < b.frame;
	});
}

void _doattachbones(VMD_MOTION_DATA* md, std::vector<Bone>& bn) {
	for (auto& a : bn) {
		for (auto& b : md->keyframes) {
			if (b.name == a.name) b.bone = &a;
		}
		_doattachbones(md, a.children);
	}
}

void VMD_MOTION_DATA::AttachBones(Armature& arm) {
	std::cout << "Attaching bones... ";
	armature = &arm;
	_doattachbones(this, arm.bones);
	std::cout << "done" << std::endl;
}

VMD_MOTION_DATA VMD_MOTION_DATA::FromFile(const std::string& path) {
	VMD_MOTION_DATA data = {};
	char b[50];
	std::ifstream strm(path, std::ios::in | std::ios::binary);
	if (!strm.is_open()) err("File not found.");
	
	//header
	RD(b, 30);
	data.signature = std::string(b);
	if (data.signature != "Vocaloid Motion Data 0002") err("Wrong signature.");
	RD(b, 20);
	data.modelName = std::string(b);
	std::cout << "Reading model: " << data.modelName << std::endl;
	RD(data.frameCount, 4);
	std::cout << "Number of frames: " << std::to_string(data.frameCount) << std::endl;

	//frames
	data.keyframes.reserve(data.frameCount);
	for (unsigned int i = 0; i < data.frameCount; i++) {
		data.keyframes.push_back(VMD_MOTION_KEYFRAME());
		auto& frm = data.keyframes[i];
		RD(b, 15);
		frm.name = std::string(b);
		RD(frm.frame, 4);
		RD(frm.position.x, 4);
		RD(frm.position.y, 4);
		RD(frm.position.z, 4);
		RD(frm.rotation.x, 4);
		RD(frm.rotation.y, 4);
		RD(frm.rotation.z, 4);
		RD(frm.rotation.w, 4);
		strm.seekg((unsigned int)strm.tellg() + 64U); //bezier params
		//std::cout << std::to_string(frm.frame) + " " + frm.name + " " + frm.position.string() + " " + frm.rotation.string() << std::endl;
	}

	std::cout << "Parse VMD OK" << std::endl << "Grouping by name... ";
	for (auto& a : data.keyframes) {
		data.keyframes_n[a.name].push_back(&a);
	}
	std::cout << "done" << std::endl;
	return data;
}

#undef GN
#undef RD
#undef err