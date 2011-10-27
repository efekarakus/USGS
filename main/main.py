#!/usr/bin/env python
import os,sys
sys.path.append("view")
sys.path.append("controller")
import wx
from ManagerialWindow import ManagerialWindow
from ManagerialAction import ManagerialAction

app = wx.App(False)
frame = ManagerialWindow(None, wx.ID_ANY, "Manager Window")
frame.Show(True)
frame.Centre()
app.MainLoop()
