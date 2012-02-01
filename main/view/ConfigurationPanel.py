from Tkinter import *

class ConfigurationPanel:
    def __init__(self,parent):
        self.container = Frame(parent)
        self.container.pack()

        # widgets
        self._init_days_to_run()
        self._init_tss()
        self._init_macro_base_temp()
        self._init_resp_macro_coef()
        self._init_sen_macro_coef()
        self._init_macro_mass_max()
        self._init_macro_vel_max()
        self._init_k_phyto()
        self._init_k_macro()
        self._init_fixed_temp()
        self._init_fixed_par()


    """ Components Declaration """
    def _init_days_to_run(self):
        label = Label(self.container,text="Days to run: ").grid(row=0)
        self.days_to_run = Entry(self.container,width=5)
        self.days_to_run.grid(row=0,column=1)
        
    def _init_tss(self):
        label = Label(self.container,text="TSS: ").grid(row=1)
        self.tss_slider = Scale(self.container,from_=0,to=20,orient=HORIZONTAL,resolution=1,tickinterval=10)
        self.tss_slider.grid(row=1,column=1)

    def _init_macro_base_temp(self):
        return

    def _init_resp_macro_coef(self):
        return

    def _init_sen_macro_coef(self):
        return

    def _init_macro_mass_max(self):
        return

    def _init_macro_vel_max(self):
        return

    def _init_k_phyto(self):
        return

    def _init_k_macro(self):
        return

    def _init_fixed_temp(self):
        return

    def _init_fixed_par(self):
        return
    
    """ Getters """
    def get_days_to_run(self):
        return self.days_to_run.get()

    def get_tss_value(self):
        return self.tss_slider.get()
