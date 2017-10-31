import bpy
import os
import sys
import struct

class Exporter():
    scene = bpy.context.scene

    def execute(self):
        path = "D:\\testbones.txt"
        print ("!writing to: " + path)
        
        file = open(path, "wb")
        for obj in self.scene.objects:
            if obj.type == "ARMATURE":
                self.export_arm(file, obj)
        file.close()
    
    def export_arm(self, file, obj):
        self.write(file, obj.name + "\n")
        self.write_bone(file, obj.data.bones)
        self.write(file, "-");
    
    def write_bone(self, file, bones):
        for bone in bones:
            if not bone.parent:
                self.do_write_bone(file, bone, 0)
    
    def do_write_bone(self, file, bone, off):
        self.write(file, " "*off + ">" + bone.name + "\n")
        for chd in bone.children:
            self.do_write_bone(file, chd, off+1)
    
    def write (self, file, _str):
        file.write(_str.encode())

if __name__ == "__main__":
    Exporter().execute()