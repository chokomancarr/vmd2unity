#include "stdafx.h"
#include "vmdparse.h"
#include <iostream>
#include <fstream>

#define err(msg) { std::cout << msg << std::endl; \
	return data; }
#define RD(tar, sz) strm.read((char*)&tar, sz);

void VMD_MOTION_DATA::Rename(std::string path) {

}

void VMD_MOTION_DATA::DumpNames(std::string path) {
	std::ofstream strm(path);
	strm << "&[name = newname]\n\
&[name = <] means use original name\n\
&[name = ] means do not use name" << std::endl;
	std::vector<std::string> names;
	for (auto& a : keyframes) {
		if (std::find(names.begin(), names.end(), a.name) == names.end()) {
			names.push_back(a.name);
			strm << a.name << " = " << std::endl;
		}
	}
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

	std::cout << "Parse VMD OK" << std::endl;
	return data;
}


#undef RD
#undef err