from Tkinter import *
from ConfigurationPanel import ConfigurationPanel
from InterfacePanel import InterfacePanel
from RiverModelAction import RiverModelAction

#TODO: handle days_to_run error cases
#TODO: menu bar to change between interfaces
#TODO: fix fractional representation for macro_base_temp
class RiverModel:
    def __init__(self, parent):
        self.container = Frame(parent)
        self.container.pack()

        # widgets
        self._init_menubar()
        self.interface_panel = InterfacePanel(self.container)
        self.configuration_panel = ConfigurationPanel(self.container)

        # visualization
        self.interface_panel.display()
        self.configuration_panel.forget()

        # actions
        action = RiverModelAction(self)
        # actions for current panel
        self.mb_interface.bind("<Button-1>",action.OnMBInterface)
        self.mb_configuration.bind("<Button-1>",action.OnMBConfig)

        # actions for interface panel
        self.interface_panel.go_button.bind("<Button-1>", action.OnGo)

        # actions for configuration panel


    #######################################
    #       Components Declaration        #
    #######################################
    def _init_menubar(self):
        self.menubar = Frame(self.container,relief=RAISED,borderwidth=1)
        self.menubar.pack()

        self.mb_interface = Button(self.menubar,text='Interface')
        self.mb_interface.pack(side=LEFT)

        self.mb_configuration = Button(self.menubar,text='Configuration')
        self.mb_configuration.pack(side=LEFT)


    #######################################
    #       Getters                       #
    #######################################
    def get_output_frequency(self):
        return self.configuration_panel.get_output_frequency()
    
    def get_days_to_run(self):
        return self.configuration_panel.get_days_to_run()

    def get_which_stock(self):
        return self.configuration_panel.get_which_stock()

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

    def get_flow_corners(self):
        return self.configuration_panel.get_fixed_corners()

    def get_filenames(self):
        return self.configuration_panel.filenames

    def get_parfile(self):
        return self.configuration_panel.parfile

    def get_tempfile(self):
        return self.configuration_panel.tempfile

    def get_daystorunarray(self):
        return self.configuration_panel.daystorunarray

    def get_timestep(self):
        return self.configuration_panel.get_timestep()
