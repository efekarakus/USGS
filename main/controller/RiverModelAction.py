#!/usr/bin/env python
import os, sys
from MainModule import *
from RiverImage import *

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
        tss_value = UI.get_tss_value()
        colorsList = goCommand(tss_value)
        outputImage(colorsList)
