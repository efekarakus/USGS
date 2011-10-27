#!/usr/bin/env python
import os,sys
import wx


if __name__ == "__main__":
	app = wx.App(False)
	frame = wx.Frame(None, wx.ID_ANY, "Hello World")
	panel = wx.Panel(frame, -1)
	vbox = wx.BoxSizer(wx.VERTICAL)
	slider = wx.Slider(frame, -1, 0, 0, 20, wx.DefaultPosition, (250, -1), wx.SL_AUTOTICKS | wx.SL_HORIZONTAL | wx.SL_LABELS)
	vbox.Add(slider, 1, wx.ALIGN_CENTRE)
	panel.SetSizer(vbox)
	frame.Show(True)
	app.MainLoop()
