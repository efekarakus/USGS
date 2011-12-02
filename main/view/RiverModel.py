#!/usr/bin/env python
import os,sys
sys.path.append("../controller")
import wx
from RiverModelAction import RiverModelAction
from ParametersPanel import ParametersPanel

"""
"""
class RiverModel(wx.Frame):

    GO_BUTTON_ID = 10

    """
    Constructor for the Managerial Window.
	@param parent the wxFrame that the window is heriting from
	@param id the id of the ManagerialWindow
	@param title the title of of window
    """
    def __init__(self, parent, id, title):
        wx.Frame.__init__(self, parent, id, title, wx.DefaultPosition, (500,500))
        
        # panel
        self.MainPanel = wx.Panel(self, -1)
        self.MainPanel.SetBackgroundColour("white")
	self.parametersPanel = ParametersPanel(self.MainPanel)
    	vbox = wx.BoxSizer(wx.VERTICAL)

        # buttons box
        self.goButton = wx.Button(self.MainPanel, self.GO_BUTTON_ID, 'GO')
        
        # add the boxes to the MainPanel
	vbox.Add(self.parametersPanel, wx.ID_ANY, wx.ALIGN_LEFT)
        vbox.Add(self.goButton, wx.ID_ANY, wx.ALIGN_CENTER)  
        self.MainPanel.SetSizer(vbox)

        # add actions
	action = RiverModelAction(self)
        wx.EVT_BUTTON(self, self.GO_BUTTON_ID, action.OnGo)

    """
    """
    def getTSSValue(self):
        return self.parametersPanel.getTSSValue()
