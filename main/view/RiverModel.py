from Tkinter import *
from ConfigurationPanel import ConfigurationPanel
from RiverModelAction import RiverModelAction

class RiverModel:
    def __init__(self, parent):
        self.container = Frame(parent)
        self.container.pack()
        
        action = RiverModelAction(self)

        # widgets
        self.configuration_panel = ConfigurationPanel(self.container)
        self._init_go_button()

        # actions
        self.go_button.bind("<Button-1>", action.OnGo)


    #######################################
    #       Components Declaration        #
    #######################################
    def _init_go_button(self):
        self.go_button = Button(self.container)
        self.go_button.configure(text="GO")
        self.go_button.pack(side=BOTTOM)
        self.go_button.focus_force()

    #######################################
    #       Getters                       #
    #######################################
    def get_days_to_run(self):
        return self.configuration_panel.get_days_to_run()

    def get_tss_value(self):
        return self.configuration_panel.get_tss_value()

    def get_macro_base_temp(self):
        return self.configuration_panel.get_macro_base_temp()

    def get_gross_macro_coef(self):
        return self.configuration_panel.get_gross_macro_coef()

    def get_resp_macro_coef(self):
        return self.configuration_panel.get_resp_macro_coef()

    def get_sen_macro_coef(self):
        return self.configuration_panel.get_sen_macro_coef()

    def get_macro_mass_max(self):
        return self.configuration_panel.get_macro_mass_max()
    
    def get_macro_vel_max(self):
        return self.configuration_panel.get_macro_vel_max()

    def get_k_phyto(self):
        return self.configuration_panel.get_k_phyto()

    def get_k_macro(self):
        return self.configuration_panel.get_k_macro()

    def get_fixed_temp(self):
        return self.configuration_panel.get_fixed_temp()

    def get_fixed_par(self):
        return self.configuration_panel.get_fixed_par()
