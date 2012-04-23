#!/usr/bin/env python
import os, sys
from MainModule import *
from RiverImage import *

class RiverModelAction:
    """
    ActionListener for the RiverModel GUI.
    """

    def __init__(self, UI):
        """
        Constructs the actions for the User Interface.
        @param UI: the river model user interface
        """
        self.UI = UI	

    def OnMBInterface(self,event):
        """
        Display the Interface Panel instead of any other panels.
        """
        self.UI.interface_panel.display()
        self.UI.configuration_panel.forget()

    def OnMBConfig(self,event):
        """
        Display the Configuration Panel instead of any other panels.
        """
        self.UI.interface_panel.forget()
        self.UI.configuration_panel.display()

    def setupFilenames(self):
        """
        Function that will create the string of selected models and days to run
        """

        filenames = self.UI.get_filenames()
        daystorunarray = self.UI.get_daystorunarray() 
        hydromapFile = ""
        hydromapFile += str(len(filenames)) + "?"
        for index in range(0, len(filenames)):
          hydromapFile += filenames[index] + "?" + daystorunarray[index] + "?"
        return hydromapFile

	def errorCheck(self):
		"""
		Checks whether every value in the GUI is reasonable
		"""

		returnValue = True
		
		tss_v = UI.get_tss_value()
		macro_base_temp_v = UI.get_macro_base_temp()
		gross_macro_coef_v = UI.get_gross_macro_coef()
		resp_macro_coef_v = UI.get_resp_macro_coef()
		sen_macro_coef_v = UI.get_sen_macro_coef()
		macro_mass_max_v = UI.get_macro_mass_max()
		macro_vel_max_v = UI.get_macro_vel_max()
		k_phyto_v = UI.get_k_phyto()
		k_macro_v = UI.get_k_macro()
		fixed_temperature_v = UI.get_fixed_temp()
		fixed_photo_radiation_v = UI.get_fixed_par()

		if (tss_v == "" and not tss_v.isdigit() and float(tss_v) < 0):
			returnValue = False
		if (macro_base_temp_v == "" and not macro_base_temp_v.isdigit() and float(macro_base_temp_v) < 0):
			returnValue = False
		if (gross_macro_coef_v == "" and not gross_macro_coef_v.isdigit() and float(gross_macro_coef_v) < 0):
			returnValue = False
		if (resp_macro_coef_v == "" and not resp_macro_coef_v.isdigit() and float(resp_macro_coef_v) < 0):
			returnValue = False
		if (sen_macro_coef_v == "" and not sen_macro_coef_v.isdigit() and float(sen_macro_coef_v) < 0):
			returnValue = False
		if (macro_mass_max_v == "" and not macro_mass_max_v.isdigit() and float(macro_mass_max_v) < 0):
			returnValue = False
		if (macro_vel_max_v == "" and not macro_vel_max_v.isdigit() and float(macro_vel_max_v) < 0):
			returnValue = False
		if (k_phyto_v == "" and not k_phyto_v.isdigit() and float(k_phyto_v) < 0):
			returnValue = False
		if (fixed_temperature_v == "" and not fixed_temperature_v.isdigit()):
			returnValue = False
		if (fixed_photo_radiation_v == "" and not fixed_photo_radiation_v.isdigit() and float(fixed_photo_radiation_v) < 0):
			returnValue = False

		return returnValue


    def OnGo(self, event):
        """
        Function that is triggered if the user clicks on the 'GO' button.
        """
        UI = self.UI
        
        hydromapFile = self.setupFilenames();
        
        print hydromapFile
        
        days_to_run_value = UI.get_days_to_run()
        which_stock = UI.get_which_stock()
        tss_value = UI.get_tss_value()
        macro_base_temp_value = UI.get_macro_base_temp()
        gross_macro_coef_value = UI.get_gross_macro_coef()
        resp_macro_coef_value = UI.get_resp_macro_coef()
        sen_macro_coef_value = UI.get_sen_macro_coef()
        macro_mass_max_value = UI.get_macro_mass_max()
        macro_vel_max_value = UI.get_macro_vel_max()
        k_phyto_value = UI.get_k_phyto()
        k_macro_value = UI.get_k_macro()
        fixed_temperature_value = UI.get_fixed_temp()
        fixed_photo_radiation_value = UI.get_fixed_par()
        flow_corners = UI.get_flow_corners()

		if (errorCheck() == True):
			extract_whichstock_Command(which_stock)
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
			extract_filenames_Command(hydromapFile)
			extract_flowcorners_Command(flow_corners)
			colors_list = goCommand()
			output_image(colors_list)

		else:
			print("error checking gives false")
