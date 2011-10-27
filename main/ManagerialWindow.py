#!/usr/bin/env python
import os,sys
import wx

"""
"""
class ManagerialWindow(wx.Frame):

	def __init__(self, parent, id, title):
		wx.Frame.__init__(self, parent, id, title, wx.DefaultPosition, (300, 150))
		self.MainPanel = wx.Panel(self, -1)

		self.vbox = wx.BoxSizer(wx.VERTICAL)
		self.tssSlider = \
		wx.Slider(self.MainPanel, -1, 0, 0, 20, wx.DefaultPosition, (250, -1), wx.SL_AUTOTICKS | wx.SL_HORIZONTAL | wx.SL_LABELS)

		self.vbox.Add(self.tssSlider, 1, wx.ALIGN_CENTRE)
		self.MainPanel.SetSizer(self.vbox)

	def getTSSValue(self):
		return self.tssSlider.GetValue()
