#include "stdafx.h"
#include <vector>
#include "vmdparse.h"
#include "bones.h"

//https://www55.atwiki.jp/kumiho_k/pages/15.html

int main()
{
	auto data = VMD_MOTION_DATA::FromFile("C:\\Users\\Pua Kai\\Desktop\\shake it\\shakeit_miku.vmd");
	//data.Rename("C:\\Users\\Pua Kai\\Desktop\\shake it\\shakeit_names.txt");
	//auto bones = Armature::FromFile("C:\\Users\\Pua Kai\\Desktop\\bones.txt");


    return 0;
}