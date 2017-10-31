#include "stdafx.h"
#include <vector>
#include "vmdparse.h"
#include "bones.h"

//https://www55.atwiki.jp/kumiho_k/pages/15.html

int main()
{
	auto data = VMD_MOTION_DATA::FromFile("D:\\shake it\\shakeit_miku.vmd");
	//data.SortFrames();
	//data.DumpData("D:\\aa.txt");
	//data.Rename("D:\\shake it\\shakeit_names.txt");
	//auto bones = Armature::FromFile("D:\\bones.txt");


    return 0;
}