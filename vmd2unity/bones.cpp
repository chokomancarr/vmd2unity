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

bool _readbones(std::ifstream& strm, std::vector<Bone>& bones, unsigned int off) {
	while (1) {
		GN;
		if (bname == "-") return false;
		else if (bname.empty()) continue;
		else {
			auto i = bname.find_first_of('>');
			if (i == std::string::npos) {
				std::cout << "Bone entry not found!" << std::endl;
				return false;
			}
			if (i == off) {
				bones.push_back(Bone(bname.substr(i + 1)));
			}
			else if (i > off) {
				strm.seekg(pos);
				if (!_readbones(strm, bones.back().children, i)) return false;
			}
			else {
				strm.seekg(pos);
				return true;
			}
		}
	}
}

Armature Armature::FromFile(std::string path) {
	Armature arm = {};
	std::ifstream strm(path);
	strm >> arm.name;
	_readbones(strm, arm.bones, 0);
	return arm;
}

#undef GN