#!/usr/bin/env python
import os,sys
sys.path.append("view")
sys.path.append("controller")
import wx
from RiverModel import RiverModel

app = wx.App(False)
frame = RiverModel(None, wx.ID_ANY, "River Model")
frame.Show(True)
frame.Centre()
app.MainLoop()
