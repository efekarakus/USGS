from Tkinter import *
from tkFileDialog import *

"""
ConfigurationPanel.py:
All the widgets necessary for globals.h, assigns the values for patches.
"""
class ConfigurationPanel:
    def __init__(self,parent):
        """ 
        Constructs a Configuration Panel
        """
        self.container = Frame(parent)
        self.container.pack()

        self.filenames = []
        self.daystorunarray = []
        self.filename = ""
        # widgets

        self.file_opt = options = {}
        options['defaultextension'] = ''
        options['filetypes'] = [('all files','.*'), ('text files', '.txt')]
        options['initialdir'] = 'C:\\'
        options['initialfile'] = 'myfile.txt'
        options['parent'] = parent
        options['title'] = 'This is a title'

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
        self._init_hydro_map()
        self._init_add_map()
        self._init_selected_maps()
        self._init_hydro_map_label()

    def forget(self):
        """Hides the frame in parent."""
        self.container.pack_forget()

    def display(self):
        """Displays the frame in parent."""
        self.container.pack()

    #######################################
    #       Components Declaration        #
    #######################################
    def _init_hydro_map_label(self):
        """Shows what hydro map is currently selected"""
        row,column = (1,3)
        hydrolabel = Label(self.container, text="Selected Map: " + self.filename).grid(row=row,column=column+1)

    def _init_selected_maps(self):
        """Creates a text box that shows user selected maps"""
        row,column = (4,3)
        self.selected_maps = Listbox(self.container,width=20,height=10)
        self.selected_maps.grid(row=row,column=column+1)

    def addmap(self):
        """Add hydro map and days to the arrays"""
        if(self.get_days_to_run() != "" and self.filename != ""):
          self.filenames.append(self.filename)
          self.daystorunarray.append(self.get_days_to_run())
          self.selected_maps.insert(END, self.filename + " : " + str(self.get_days_to_run()) + " Days")

    def _init_add_map(self):
        """Creates a button to add a hydro map and selected days to the model"""
        row,column = (3,3)
        self.add_map = Button(self.container, text="Add Map to Model", command = self.addmap)
        self.add_map.focus_force()
        self.add_map.grid(row=row,column=column+1)
        

    def _init_days_to_run(self):
        """Creates a text box to simulate the number of days that we want our model to run."""
        row,column = (2,3)
        label = Label(self.container,text="Days to run:                                ").grid(row=row,column=column+1)
        self.days_to_run = Entry(self.container,width=5)
        self.days_to_run.grid(row=row,column=column+1)
        
    def _init_tss(self):
        """Creates a slider for the TSS value."""
        row,column = (0,1)
        label = Label(self.container,text="TSS: ").grid(row=row)
        self.tss_slider = Scale(self.container,from_=0,to=20,orient=HORIZONTAL,resolution=1,tickinterval=10,length=200)
        self.tss_slider.set(10)
        self.tss_slider.grid(row=row,column=column)

    def _init_macro_base_temp(self):
        """Creates a slider for the macro_base_temp."""
        row,column = (1,1) 
        label = Label(self.container,text="Macro Temperature: ").grid(row=row)
        self.macro_base_temp = Scale(self.container,from_=11.70,to=27.70,orient=HORIZONTAL,resolution=0.01,tickinterval=8.00,length=200)
        self.macro_base_temp.set(19.7)
        self.macro_base_temp.grid(row=row,column=column)

    def _init_gross_macro_coef(self):
        """Creates a slider for gross_macro_coef."""
        row,column = (2,1)
        label = Label(self.container,text="Gross Macro Coef: ").grid(row=row)
        self.gross_macro_coef = Scale(self.container,from_=0.00,to=1.00,orient=HORIZONTAL,resolution=0.01,tickinterval=0.5,length=200)
        self.gross_macro_coef.set(0.08)
        self.gross_macro_coef.grid(row=row,column=column)

    def _init_resp_macro_coef(self):
        """Creates a slider for resp_macro_coef."""
        row,column = (3,1)
        label = Label(self.container,text="Resp Macro Coef: ").grid(row=row)
        self.resp_macro_coef = Scale(self.container,from_=0.00,to=1.00,orient=HORIZONTAL,resolution=0.01,tickinterval=0.5,length=200)
        self.resp_macro_coef.set(0.04)
        self.resp_macro_coef.grid(row=row,column=column)

    def _init_sen_macro_coef(self):
        """Creates a slider for sen_macro_coef."""
        row,column = (4,1)
        label = Label(self.container,text="Sen Macro Coef: ").grid(row=row)
        self.sen_macro_coef = Scale(self.container,from_=0.00,to=1.00,orient=HORIZONTAL,resolution=0.01,tickinterval=0.5,length=200)
        self.sen_macro_coef.set(0.08)
        self.sen_macro_coef.grid(row=row,column=column)

    def _init_macro_mass_max(self):
        """Creates a slider for macro_mass_max."""
        row,column = (5,1)
        label = Label(self.container,text="Macro Mass Max: ").grid(row=row)
        self.macro_mass_max = Scale(self.container,from_=500,to=1500,orient=HORIZONTAL,resolution=25,tickinterval=500,length=200)
        self.macro_mass_max.set(1000)
        self.macro_mass_max.grid(row=row,column=column)

    def _init_macro_vel_max(self):
        """Creates a slider for macro_vel_max."""
        row,column = (6,1)
        label = Label(self.container,text="Macro Velocity Max: ").grid(row=row)
        self.macro_vel_max = Scale(self.container,from_=0.2,to=1.6,orient=HORIZONTAL,resolution=0.1,tickinterval=0.7,length=200)
        self.macro_vel_max.set(1.0)
        self.macro_vel_max.grid(row=row,column=column)

    def _init_k_phyto(self):
        """Creates a slider for k_phyto."""
        row,column = (7,1)
        label = Label(self.container,text="K-Phyto: ").grid(row=row)
        self.k_phyto = Scale(self.container,from_=0.00,to=1.00,orient=HORIZONTAL,resolution=0.01,tickinterval=0.50,length=200)
        self.k_phyto.set(0.01)
        self.k_phyto.grid(row=row,column=column)

    def _init_k_macro(self):
        """Creates a slider for k_macro."""
        row,column = (8,1)
        label = Label(self.container,text="K-Macro: ").grid(row=row)
        self.k_macro = Scale(self.container,from_=0.00,to=1.00,orient=HORIZONTAL,resolution=0.01,tickinterval=0.50,length=200)
        self.k_macro.set(0.01)
        self.k_macro.grid(row=row,column=column)

    def _init_fixed_temp(self):
        """Creates a slider for the temperature."""
        row,column = (9,1)
        label = Label(self.container,text="Temperature: ").grid(row=row)
        self.fixed_temp = Scale(self.container,from_=0,to=30,orient=HORIZONTAL,resolution=1,tickinterval=15,length=200)
        self.fixed_temp.set(20)
        self.fixed_temp.grid(row=row,column=column)

    def _init_fixed_par(self):
        """Creates a slider for the PAR."""
        row,column=(10,1)
        label = Label(self.container,text="Photosynthetic Radiation: ").grid(row=row)
        self.fixed_par = Scale(self.container,from_=0,to=2000,orient=HORIZONTAL,resolution=100,tickinterval=1000,length=200)
        self.fixed_par.set(2000)
        self.fixed_par.grid(row=row,column=column)
        
    def askname(self):
        fn = askopenfilename(**self.file_opt)
        ar = fn.split('/')
        self.filename = ar[len(ar)-1]
        self.hydrolabel = Label(self.container,text="Selected Map: " + self.filename).grid(row=1,column=4)

    def _init_hydro_map(self):
        """Creates a button for the hydro maps."""
        row,column=(0,3)
        self.hydro_map = Button(self.container, text='Open Hydro Map',\
        command = self.askname)
        self.hydro_map.grid(row=row,column=column+1)

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

    def get_hydro_map(self):
        return self.hydro_map.get()

