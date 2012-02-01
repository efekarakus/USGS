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
		macro_base_temp_value = UI.get_macro_base_temp()
		gross_base_temp_value = UI.get_gross_base_temp()
		resp_macro_coef_value = UI.get_resp_macro_coef()
		extract_TSS_Command(tss_value)
		extract_macro_base_temp_Command(macro_base_temp_value)
		extract_gross_base_temp_Command(gross_base_temp_value)
		extract_resp_macro_coef_Command(resp_macro_coef_value)
		colorsList = goCommand(tss_value)
		outputImage(colorsList)
