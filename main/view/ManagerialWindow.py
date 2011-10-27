#!/usr/bin/env python
import os,sys
sys.path.append("../controller")
import wx
from ManagerialAction import ManagerialAction

"""
"""
class ManagerialWindow(wx.Frame):

	GO_BUTTON_ID = 10
	VBOX_HBOX_ID = 0
	VBOX_TSS_SLIDER_ID = 1
	HBOX_GO_BUTTON_ID = 2
	

	"""
	"""
	def __init__(self, parent, id, title):
		wx.Frame.__init__(self, parent, id, title, wx.DefaultPosition, (300, 150))
		
		# Action Objects
		action = ManagerialAction(self)

		# Main Panel
		self.MainPanel = wx.Panel(self, -1)
	
		# sliders box
		self.vbox = wx.BoxSizer(wx.VERTICAL)
		self.tssSlider = \
		wx.Slider(self.MainPanel, -1, 0, 0, 20, wx.DefaultPosition, (250, -1),
					wx.SL_AUTOTICKS | wx.SL_HORIZONTAL | wx.SL_LABELS, wx.DefaultValidator, "TSS")

		# buttons box
		self.hbox = wx.BoxSizer(wx.HORIZONTAL)
		self.goButton = wx.Button(self.MainPanel, self.GO_BUTTON_ID, 'GO')
		

		# add actions
		wx.EVT_BUTTON(self, self.GO_BUTTON_ID, action.OnGo)


		# add the boxes to the MainPanel
		self.vbox.Add(self.tssSlider, self.VBOX_TSS_SLIDER_ID, wx.ALIGN_CENTRE)		# add the slider to the sliders box
		self.hbox.Add(self.goButton, self.HBOX_GO_BUTTON_ID, wx.ALIGN_CENTRE)		# add the go button to the buttons box
		self.vbox.Add(self.hbox, self.VBOX_HBOX_ID, wx.ALIGN_CENTRE | wx.ALL)		# add the buttons box to the sliders box		

		self.MainPanel.SetSizer(self.vbox)

	def getTSSValue(self):
		return self.tssSlider.GetValue()
