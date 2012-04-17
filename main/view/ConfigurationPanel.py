from Tkinter import *
from tkFileDialog import *
from ToolTip import *

# Default Values for Sliders
		
DEFAULT_TSS = 10
DEFAULT_MACRO = 19.7
DEFAULT_GROSS_MACRO = 0.08
DEFAULT_RESP_MACRO_COEF = 0.04
DEFAULT_SEN_MACRO_COEF = 0.08
DEFAULT_MACRO_MASS_MAX = 1000
DEFAULT_MACRO_VEL_MAX = 1.0
DEFAULT_K_PHYTO = 0.01
DEFAULT_K_MACRO = 0.01
DEFAULT_TEMP = 20
DEFAULT_PAR = 2000



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
        
        self.stockVal = StringVar(self.container)
        self.stockVal.set("consum")
        # widgets

        self.file_opt = options = {}
        options['defaultextension'] = ''
        options['filetypes'] = [('all files','.*'), ('text files', '.txt')]
        options['initialdir'] = 'C:\\'
        options['initialfile'] = 'myfile.txt'
        options['parent'] = parent
        options['title'] = 'This is a title'

        self._init_days_to_run()
        self._init_which_stock()
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
        self._init_remove_map()
        self._init_selected_maps()
        self._init_hydro_map_label()
        self._init_reset_values()
        self._init_flow_corners()

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

    def reset(self):
        """Resets the values of sliders to default values""" 
        self.tss_slider.delete(0,END)
        self.tss_slider.insert(0,DEFAULT_TSS)
        self.macro_base_temp.delete(0,END)
        self.macro_base_temp.insert(0,DEFAULT_MACRO)
        self.gross_macro_coef.delete(0,END)
        self.gross_macro_coef.insert(0,DEFAULT_GROSS_MACRO)
        self.resp_macro_coef.delete(0,END)
        self.resp_macro_coef.insert(0,DEFAULT_RESP_MACRO_COEF)
        self.sen_macro_coef.delete(0,END)
        self.sen_macro_coef.insert(0,DEFAULT_SEN_MACRO_COEF)
        self.macro_mass_max.delete(0,END)
        self.macro_mass_max.insert(0,DEFAULT_MACRO_MASS_MAX)
        self.macro_vel_max.delete(0,END)
        self.macro_vel_max.insert(0,DEFAULT_MACRO_VEL_MAX)
        self.k_phyto.delete(0,END)
        self.k_phyto.insert(0,DEFAULT_K_PHYTO)
        self.k_macro.delete(0,END)
        self.k_macro.insert(0,DEFAULT_K_MACRO)
        self.fixed_temp.delete(0,END)
        self.fixed_temp.insert(0,DEFAULT_TEMP)
        self.fixed_par.delete(0,END)
        self.fixed_par.insert(0,DEFAULT_PAR)
        self.flow_corners.deselect()

    def removemap(self):
        try:
            self.index = self.selected_maps.curselection()[0]
            self.selected_maps.delete(self.index)
            self.filenames.pop(int(self.index))
            self.daystorunarray.pop(int(self.index))
        except IndexError:
            pass

    def _init_flow_corners(self):
        """Creates a check button to see if we only want to flow carbon to the corners."""
        row,column = (6,4)
        v = IntVar()
        self.flow_corners = Checkbutton(self.container,text="Adjacent cells only?",variable=v)
        self.flow_corners.var = v
        self.flow_corners.grid(row=row,column=column)
        createToolTip(self.flow_corners, "If checked flows carbon only to adjacent cells, \
         if unchecked flows carbon to according cell based on x-vector and y-vector")

    def _init_remove_map(self):
        row,column=(5,3)
        self.remove_map = Button(self.container, text="Remove Selected Map", command=self.removemap)
        self.remove_map.focus_force()
        self.remove_map.grid(row=row, column=column+1)

    def _init_selected_maps(self):
        """Creates a text box that shows user selected maps"""
        row,column = (4,3)
        self.scrollbar = Scrollbar(self.container)
        self.selected_maps = Listbox(self.container,width=20,height=10,yscrollcommand=self.scrollbar.set)
        self.selected_maps.grid(row=row,column=column+1)
        self.scrollbar.config(command=self.selected_maps.yview)

    def addmap(self):
        """Add hydro map and days to the arrays"""
        if(self.get_days_to_run() != "" and self.filename != "" and self.get_days_to_run().isdigit() and int(self.get_days_to_run()) > 0):
          self.filenames.append(self.filename)
          self.daystorunarray.append(self.get_days_to_run())
          self.selected_maps.insert(END, self.filename + " : " + str(self.get_days_to_run()) + " Days")

    def _init_add_map(self):
        """Creates a button to add a hydro map and selected days to the model"""
        row,column = (3,3)
        self.add_map = Button(self.container, text="Add Hydraulic Map to Model", command = self.addmap)
        self.add_map.focus_force()
        self.add_map.grid(row=row,column=column+1)
        
    def _init_days_to_run(self):
        """Creates a text box to simulate the number of days that we want our model to run."""
        row,column = (2,3)
        label = Label(self.container,text="Days to run:                                ").grid(row=row,column=column+1)
        self.days_to_run = Entry(self.container,width=5)
        self.days_to_run.grid(row=row,column=column+1)
        
    def _init_which_stock(self):
        """Creates an option box for which stock to choose"""
        row,column = (0,1)
        label = Label(self.container, text="Which Stock: ").grid(row=row)
        self.which_stock = OptionMenu(self.container, self.stockVal, "consum", "detritus", "DOC", "herbivore", "macro", "POC", "phyto", "sedconsumer", "seddecomp", "waterdecomp")
        self.which_stock.grid(row=row, column=column)
        createToolTip(self.which_stock, "stock value used for the image")

    def _init_tss(self):
        """Creates a slider for the TSS value."""
        row,column = (1,1)
        label = Label(self.container,text="TSS: ").grid(row=row)
        self.tss_slider = Entry(self.container,width=5)
        self.tss_slider.insert(0, DEFAULT_TSS)
        self.tss_slider.grid(row=row,column=column)
        createToolTip(self.tss_slider, "range between 0.0 and 20.0")

    def _init_macro_base_temp(self):
        """Creates a slider for the macro_base_temp."""
        row,column = (2,1) 
        label = Label(self.container,text="Macro Temperature: ").grid(row=row)
        self.macro_base_temp = Entry(self.container,width=5)
        self.macro_base_temp.insert(0,DEFAULT_MACRO)
        self.macro_base_temp.grid(row=row,column=column)
        createToolTip(self.macro_base_temp,"range between 11.7 and 27.7")

    def _init_gross_macro_coef(self):
        """Creates a slider for gross_macro_coef."""
        row,column = (3,1)
        label = Label(self.container,text="Gross Macro Coef: ").grid(row=row)
        self.gross_macro_coef = Entry(self.container,width=5)
        self.gross_macro_coef.insert(0,DEFAULT_GROSS_MACRO)
        self.gross_macro_coef.grid(row=row,column=column)
        createToolTip(self.gross_macro_coef,"range between 0.0 and 1.0")

    def _init_resp_macro_coef(self):
        """Creates a slider for resp_macro_coef."""
        row,column = (4,1)
        label = Label(self.container,text="Respiration Macro Coef: ").grid(row=row)
        self.resp_macro_coef = Entry(self.container,width=5)
        self.resp_macro_coef.insert(0,DEFAULT_RESP_MACRO_COEF)
        self.resp_macro_coef.grid(row=row,column=column)
        createToolTip(self.resp_macro_coef,"range between 0.0 and 1.0")

    def _init_sen_macro_coef(self):
        """Creates a slider for sen_macro_coef."""
        row,column = (5,1)
        label = Label(self.container,text="Senescence Macro Coef: ").grid(row=row)
        self.sen_macro_coef = Entry(self.container,width=5)
        self.sen_macro_coef.insert(0,DEFAULT_SEN_MACRO_COEF)
        self.sen_macro_coef.grid(row=row,column=column)
        createToolTip(self.sen_macro_coef, "range between 0.0 and 1.0")

    def _init_macro_mass_max(self):
        """Creates a slider for macro_mass_max."""
        row,column = (6,1)
        label = Label(self.container,text="Macro Mass Max: ").grid(row=row)
        self.macro_mass_max = Entry(self.container,width=5)
        self.macro_mass_max.insert(0,DEFAULT_MACRO_MASS_MAX)
        self.macro_mass_max.grid(row=row,column=column)
        createToolTip(self.macro_mass_max, "range between 500.0 and 1500.0")

    def _init_macro_vel_max(self):
        """Creates a slider for macro_vel_max."""
        row,column = (7,1)
        label = Label(self.container,text="Macro Velocity Max: ").grid(row=row)
        self.macro_vel_max = Entry(self.container,width=5)
        self.macro_vel_max.insert(0,DEFAULT_MACRO_VEL_MAX)
        self.macro_vel_max.grid(row=row,column=column)
        createToolTip(self.macro_vel_max, "range between 0.2 and 1.6")

    def _init_k_phyto(self):
        """Creates a slider for k_phyto."""
        row,column = (8,1)
        label = Label(self.container,text="K-Phyto: ").grid(row=row)
        self.k_phyto = Entry(self.container,width=5)
        self.k_phyto.insert(0,DEFAULT_K_PHYTO)
        self.k_phyto.grid(row=row,column=column)
        createToolTip(self.k_phyto, "range between 0.0 and 1.0")

    def _init_k_macro(self):
        """Creates a slider for k_macro."""
        row,column = (9,1)
        label = Label(self.container,text="K-Macro: ").grid(row=row)
        self.k_macro = Entry(self.container,width=5)
        self.k_macro.insert(0,DEFAULT_K_MACRO)
        self.k_macro.grid(row=row,column=column)
        createToolTip(self.k_macro, "range between 0.0 and 1.0")

    def _init_fixed_temp(self):
        """Creates a slider for the temperature."""
        row,column = (10,1)
        label = Label(self.container,text="Temperature: ").grid(row=row)
        self.fixed_temp = Entry(self.container,width=5)
        self.fixed_temp.insert(0,DEFAULT_TEMP)
        self.fixed_temp.grid(row=row,column=column)
        createToolTip(self.fixed_temp, "range between 0.0 and 30.0")

    def _init_fixed_par(self):
        """Creates a slider for the PAR."""
        row,column=(11,1)
        label = Label(self.container,text="Photosynthetic Radiation: ").grid(row=row)
        self.fixed_par = Entry(self.container,width=5)
        self.fixed_par.insert(0,DEFAULT_PAR)
        self.fixed_par.grid(row=row,column=column)
        createToolTip(self.fixed_par, "range between 0.0 and 2000.0")

        
    def _init_reset_values(self):
        """Creates a button to reset the values of the sliders to their default values"""
        row,column = (12,1)
        self.reset_values = Button(self.container, text="Reset To Default Values", command=self.reset)
        self.reset_values.grid(row=row, column=column)

    def askname(self):
        self.filename = askopenfilename(**self.file_opt)
        ar = self.filename.split('/')
        fn = ar[len(ar)-1]
        self.hydrolabel = Label(self.container,text="Selected Map: " + fn).grid(row=1,column=4)

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

    def get_which_stock(self):
		return self.stockVal.get()

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

    def get_fixed_corners(self):
        return self.flow_corners.var.get()

