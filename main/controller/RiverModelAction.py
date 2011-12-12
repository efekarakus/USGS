#!/usr/bin/env python
import os, sys
import wx
from MainModule import *

"""
ActionListener for the RiverModel GUI.
"""
class RiverModelAction:

    """
    Constructor:
    Takes the Managerial Window as a parameter
    @param managerUI the managerial window
    """
    def __init__(self, UI):
        self.UI = UI	

	"""
	Function that is triggered if the user clicks on the 'GO' button.
	Reads the TSS slider's value and prints it.
	"""
    def OnGo(self, event):
        UI = self.UI
        tssValue = UI.getTSSValue()
        test = goCommand(tssValue)
