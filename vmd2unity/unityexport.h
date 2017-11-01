#pragma once
#include "vmdparse.h"

struct UnityExporter {
	static void Export(VMD_MOTION_DATA& data, std::string path, std::string name, int fps = 24);
};