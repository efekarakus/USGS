#!/usr/bin/env python
import os,sys
sys.path.append("../controller")
import wx

"""
"""
class ParametersPanel(wx.Panel):
	
    """
    """
    def __init__(self, parent):
        wx.Panel.__init__(self, parent)
        self.SetBackgroundColour("white")
		
        vbox = wx.BoxSizer(wx.VERTICAL)
		
	# sliders
        tssLabel = wx.StaticText(self, -1, 'TSS', (-1, -1))
	self.tssSlider = \
        wx.Slider(self, -1, 0, 0, 20, wx.DefaultPosition, (-1, -1),
                    wx.SL_AUTOTICKS | wx.SL_HORIZONTAL | wx.SL_LABELS, wx.DefaultValidator, "TSS")

        macroBasedTempLabel = wx.StaticText(self, -1, 'Macro Based Temperature', (-1,-1))
        self.macroBasedTempSlider = \
        wx.Slider(self, -1, 0, 0, 20, wx.DefaultPosition, (-1, -1),
                    wx.SL_AUTOTICKS | wx.SL_HORIZONTAL | wx.SL_LABELS, wx.DefaultValidator, "Macro Based Temperature")

                
	# add components to panel
        vbox.Add(tssLabel, wx.ID_ANY, wx.ALIGN_CENTER)
        vbox.Add(self.tssSlider, wx.ID_ANY, wx.ALIGN_LEFT)
        vbox.Add(macroBasedTempLabel, wx.ID_ANY, wx.ALIGN_CENTER)
        vbox.Add(self.macroBasedTempSlider, wx.ID_ANY, wx.ALIGN_LEFT)
	self.SetSizer(vbox)
	
    """
    @return the value chosen by the user for the TSS
    """
    def getTSSValue(self):
	return self.tssSlider.GetValue()
		
		
		
		
