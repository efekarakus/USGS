#!/usr/bin/env python
import os,sys
sys.path.append("view")
sys.path.append("controller")
from Tkinter import *
from RiverModel import RiverModel

VERSION = 'v1.0'


if __name__=="__main__":
  root = Tk()
  rivermodel_app = RiverModel(root)
  root.title('RiverModel '+VERSION)
  root.mainloop()
