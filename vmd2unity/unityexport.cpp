#include "stdafx.h"
#include "unityexport.h"
#include <iostream>
#include <fstream>

void UnityExporter::Export(std::string path, std::string name) {
	std::ofstream strm(path + "\\" + name + ".anim", std::ios::out | std::ios::binary);
	std::string ss = R"(%YAML 1.1
%TAG !u!tag:unity3d.com, 2011 :
	-- - !u!74 & 7400000
	AnimationClip :
	m_ObjectHideFlags : 0
	m_PrefabParentObject : {fileID: 0}
m_PrefabInternal: {fileID: 0}
m_Name: )";
	std::string ss2 = R"(
	serializedVersion : 6
	m_Legacy : 0
	m_Compressed : 0
	m_UseHighQualityCurve : 1
	m_RotationCurves : )";
	strm << ss << name << ss2;

}