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

    def OnGo(self, event):
        """
        Function that is triggered if the user clicks on the 'GO' button.
        """
        UI = self.UI

        #TODO: days_to_run needs to be implemented in the GUI

		days_to_run_value = UI.get_days_to_run()
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

		extract_days_to_run_Command(days_to_run_value)
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

        colors_list = goCommand(tss_value)
        output_image(colors_list)
