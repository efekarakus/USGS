from Tkinter import *
from PIL import Image, ImageTk
from RiverModelAction import RiverModelAction

class InterfacePanel:
    def __init__(self,parent):
        self.container = Frame(parent)
        self.container.pack()
        
        # widges
        self._init_go_button()

        # actions
        action = RiverModelAction(self)
        self.go_button.bind("<Button-1>", action.OnGo)

    def forget(self):
        """Hides the frame in parent."""
        self.container.pack_forget()

    def display(self):
        """Displays the frame in parent."""
        self.container.pack()

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

