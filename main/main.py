#!/usr/bin/env python
import os,sys
import wx
from ManagerialWindow import ManagerialWindow

app = wx.App(False)
frame = ManagerialWindow(None, wx.ID_ANY, "Manager Window")
frame.Show(True)
frame.Centre()
app.MainLoop()
