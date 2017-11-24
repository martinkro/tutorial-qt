# -*- coding:utf-8 -*-

import sys
import os

def scan_dir(target_dir,prefix="/",cb=None):
    names = os.listdir(target_dir)
    for name in names:
        if name.endswith(".py") or name.endswith(".qss"):
            continue
        full_dir = os.path.join(target_dir,name)
        if os.path.isdir(full_dir):
            scan_dir(full_dir,prefix+name+"/")
        else:
            print("<file>" + prefix+name + "</file>")

if __name__ == "__main__":
    target_dir = "."
    f = open("test.qss","w")
    scan_dir(target_dir,"html/")
    f.close()