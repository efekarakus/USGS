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
		gross_macro_coef_value = UI.get_gross_macro_coef()
		print gross_macro_coef_value
		resp_macro_coef_value = UI.get_resp_macro_coef()
		sen_macro_coef_value = UI.get_sen_macro_coef()
		macro_mass_max_value = UI.get_macro_mass_max()
		macro_vel_max_value = UI.get_macro_vel_max()
		k_phyto_value = UI.get_k_phyto()
		k_macro_value = UI.get_k_macro()
		fixed_temperature_value = UI.get_fixed_temp()
		fixed_photo_radiation_value = UI.get_fixed_par()
		extract_TSS_Command(tss_value)
		extract_macro_base_temp_Command(macro_base_temp_value)
		extract_gross_macro_coef_Command(gross_macro_coef_value)
		extract_resp_macro_coef_Command(resp_macro_coef_value)
		extract_sen_macro_coef_Command(sen_macro_coef_value)
		extract_macro_mass_max_Command(macro_mass_max_value)
		extract_macro_vel_max_Command(macro_vel_max_value)
		extract_k_phyto_Command(k_phyto_value)
		extract_k_macro_Command(k_macro_value)
		extract_fixed_temperature_Command(fixed_temperature_value)
		extract_fixed_photo_radiation_Command(fixed_photo_radiation_value)
		colorsList = goCommand(tss_value)
		outputImage(colorsList)
