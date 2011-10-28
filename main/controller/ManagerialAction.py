#!/usr/bin/env python
import os, sys
#sys.path.append("../model")
import wx
from SetupModule import *

"""
ActionListener for the Managerial Window.
"""
class ManagerialAction:

	"""
		Constructor:
		Takes the Managerial Window as a parameter
		@param managerUI the managerial window
	"""
	def __init__(self, managerUI):
		self.managerUI = managerUI	

	"""
		Function that is triggered if the user clicks on the 'GO' button.
		Reads the TSS slider's value and prints it.
	"""
	def OnGo(self, event):
		managerUI = self.managerUI
		tssValue = managerUI.getTSSValue()
		print computeTSS(tssValue)
