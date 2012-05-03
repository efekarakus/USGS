#!/usr/bin/env python
import os,sys, errno
sys.path.append("view")
sys.path.append("controller")
from Tkinter import *
from RiverModel import RiverModel

VERSION = 'v1.0'

def ensure_dir(f):
  try:
    os.makedirs(f)
  except OSError, e:
    if e.errno != errno.EEXIST:
      raise

ensure_dir("results")
ensure_dir("results/images")
ensure_dir("results/data")

if __name__=="__main__":
  root = Tk()
  rivermodel_app = RiverModel(root)
  root.title('RiverModel '+VERSION)
  root.mainloop()
