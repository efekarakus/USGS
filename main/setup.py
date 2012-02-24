from distutils.core import setup, Extension
import os, subprocess

#build the code
module1 = Extension('MainModule', sources = ['model/main.c'])
 
setup (name = 'PackageName',
        version = '1.0',
        description = 'This is a demo package',
        ext_modules = [module1])
#move the executable
src = "./build/lib.win32-2.6/MainModule.pyd"
dst = "./dist/controller/"

#subprocess.Popen("mv" + " " + src + " " + dst, shell = True)
