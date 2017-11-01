#include "stdafx.h"
#include "bones.h"
#include <iostream>
#include <fstream>

/* bone structure file
----------------------
	armaturename
	>bone1
	>bone2
	 >childbone1
	  >childchildbone1
	-
----------------------
*/

char bcname[100];
std::string bname;
#define GN auto pos = strm.tellg(); strm.getline(bcname, 100); bname = std::string(bcname);

bool _readbones(std::ifstream& strm, std::vector<Bone>& bones, unsigned int off, std::string pn) {
	std::string ln;
	while (1) {
		GN;
		if (strm.eof()) return false;
		if (bname == "-") return false;
		else if (bname.empty()) continue;
		else {
			auto i = bname.find_first_of('>');
			if (i == std::string::npos) {
				std::cout << "Bone entry not found!" << std::endl;
				return false;
			}
			if (i == off) {
				ln = bname.substr(i + 1);
				bones.push_back(Bone(ln, pn + ln));
			}
			else if (i > off) {
				strm.seekg(pos);
				if (!_readbones(strm, bones.back().children, i, pn + ln + "/")) return false;
			}
			else {
				strm.seekg(pos);
				return true;
			}
		}
	}
}

Armature Armature::FromFile(std::string path) {
	std::cout << "Reading bone structure... ";
	Armature arm = {};
	std::ifstream strm(path, std::ios::binary);
	strm >> arm.name;
	_readbones(strm, arm.bones, 0, arm.name + "/");
	std::cout << "done" << std::endl;
	return arm;
}

#undef GN