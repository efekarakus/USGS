from Tkinter import *

class ConfigurationPanel:
    def __init__(self,parent):
        self.container = Frame(parent)
        self.container.pack()

        # widgets
        self._init_days_to_run()
        self._init_tss()
        self._init_macro_base_temp()
        self._init_gross_macro_coef()
        self._init_resp_macro_coef()
        self._init_sen_macro_coef()
        self._init_macro_mass_max()
        self._init_macro_vel_max()
        self._init_k_phyto()
        self._init_k_macro()
        self._init_fixed_temp()
        self._init_fixed_par()


    #######################################
    #       Components Declaration        #
    #######################################
    def _init_days_to_run(self):
        row,column = (0,1)
        label = Label(self.container,text="Days to run: ").grid(row=row)
        self.days_to_run = Entry(self.container,width=5)
        self.days_to_run.grid(row=row,column=column)
        
    def _init_tss(self):
        row,column = (1,1)
        label = Label(self.container,text="TSS: ").grid(row=row)
        self.tss_slider = Scale(self.container,from_=0,to=20,orient=HORIZONTAL,resolution=1,tickinterval=10)
        self.tss_slider.grid(row=row,column=column)

    def _init_macro_base_temp(self):
        row,column = (2,1) 
        label = Label(self.container,text="Macro Temperature: ").grid(row=row)
        self.macro_base_temp = Scale(self.container,from_=11.7,to=27.7,orient=HORIZONTAL,resolution=1, tickinterval=10)
        self.macro_base_temp.grid(row=row,column=column)

    def _init_gross_macro_coef(self):
        row,column = (3,1)
        label = Label(self.container,text="Gross Macro Coef: ").grid(row=row)
        self.gross_macro_coef = Scale(self.container,from_=0.00,to=1.00,orient=HORIZONTAL,resolution=0.01,tickinterval=0.5)
        self.gross_macro_coef.grid(row=row,column=column)

    def _init_resp_macro_coef(self):
        row,column = (4,1)
        label = Label(self.container,text="Resp Macro Coef: ").grid(row=row)
        self.resp_macro_coef = Scale(self.container,from_=0.00,to=1.00,orient=HORIZONTAL,resolution=0.01,tickinterval=0.5)
        self.resp_macro_coef.grid(row=row,column=column)

    def _init_sen_macro_coef(self):
        row,column = (5,1)
        label = Label(self.container,text="Sen Macro Coef: ").grid(row=row)
        self.sen_macro_coef = Scale(self.container,from_=0.00,to=1.00,orient=HORIZONTAL,resolution=0.01,tickinterval=0.5)
        self.sen_macro_coef.grid(row=row,column=column)

    def _init_macro_mass_max(self):
        row,column = (6,1)
        label = Label(self.container,text="Macro Mass Max: ").grid(row=row)
        self.macro_mass_max = Scale(self.container,from_=500,to=1500,orient=HORIZONTAL,resolution=25,tickinterval=500)
        self.macro_mass_max.grid(row=row,column=column)

    def _init_macro_vel_max(self):
        row,column = (7,1)
        label = Label(self.container,text="Macro Vel Max: ").grid(row=row)
        self.macro_vel_max = Scale(self.container,from_=0.2,to=1.6,orient=HORIZONTAL,resolution=0.1,tickinterval=0.7)
        self.macro_vel_max.grid(row=row,column=column)

    def _init_k_phyto(self):
        row,column = (8,1)
        label = Label(self.container,text="K-Phyto: ").grid(row=row)
        self.k_phyto = Scale(self.container,from_=0.00,to=1.00,orient=HORIZONTAL,resolution=0.10,tickinterval=0.50)
        self.k_phyto.grid(row=row,column=column)

    def _init_k_macro(self):
        row,column = (9,1)
        label = Label(self.container,text="K-Macro: ").grid(row=row)
        self.k_macro = Scale(self.container,from_=0.00,to=1.00,orient=HORIZONTAL,resolution=0.10,tickinterval=0.50)
        self.k_macro.grid(row=row,column=column)

    def _init_fixed_temp(self):
        row,column = (0,3)
        label = Label(self.container,text="Temperature: ").grid(row=row,column=column)
        self.fixed_temp = Scale(self.container,from_=0,to=30,orient=HORIZONTAL,resolution=1,tickinterval=15)
        self.fixed_temp.grid(row=row,column=column+1)

    def _init_fixed_par(self):
        row,column=(1,3)
        label = Label(self.container,text="PAR: ").grid(row=row,column=column)
        self.fixed_par = Scale(self.container,from_=0,to=2000,orient=HORIZONTAL,resolution=100,tickinterval=1000)
        self.fixed_par.grid(row=row,column=column+1)
    
    #######################################
    #       Getters                       #
    #######################################
    def get_days_to_run(self):
        return self.days_to_run.get()

    def get_tss_value(self):
        return self.tss_slider.get()

    def get_macro_base_temp(self):
        return self.macro_base_temp.get()

    def get_gross_macro_coef(self):
        return self.gross_macro_coef.get()

    def get_resp_macro_coef(self):
        return self.resp_macro_coef.get()

    def get_sen_macro_coef(self):
        return self.sen_macro_coef.get()

    def get_macro_mass_max(self):
        return self.macro_mass_max.get()

    def get_macro_vel_max(self):
        return self.macro_vel_max.get()

    def get_k_phyto(self):
        return self.k_phyto.get()

    def get_k_macro(self):
        return self.k_macro.get()

    def get_fixed_temp(self):
        return self.fixed_temp.get()

    def get_fixed_par(self):
        return self.fixed_par.get()
