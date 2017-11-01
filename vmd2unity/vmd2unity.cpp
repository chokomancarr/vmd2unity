#include "stdafx.h"
#include <vector>
#include "vmdparse.h"
#include "bones.h"
#include "unityexport.h"

//https://www55.atwiki.jp/kumiho_k/pages/15.html

int main()
{
	auto data = VMD_MOTION_DATA::FromFile("D:\\shake it\\shakeit_miku.vmd");
	//data.DumpNames("D:\\ab.txt");
	data.Rename("D:\\shake it\\shakeit_names.txt");
	auto bones = Armature::FromFile("D:\\bones.txt");
	data.AttachBones(bones);
	//data.DumpData("D:\\aa.txt");
	UnityExporter::Export(data, "D:", "meow");
    return 0;
}