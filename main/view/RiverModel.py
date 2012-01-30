from Tkinter import *
from RiverModelAction import RiverModelAction

class RiverModel:
    def __init__(self, parent):
        self.container = Frame(parent)
        self.container.pack()
        
        action = RiverModelAction(self)

        # widgets
        self._init_tss_slider()
        self._init_go_button()

        # actions
        self.go_button.bind("<Button-1>", action.OnGo)

    def _init_go_button(self):
        self.go_button = Button(self.container)
        self.go_button.configure(text="GO")
        self.go_button.pack(side=BOTTOM)
        self.go_button.focus_force()

    def _init_tss_slider(self):
        self.tss_slider = Scale(self.container,from_=0,to=100,orient=HORIZONTAL,resolution=10,label="TSS",tickinterval=1)
        self.tss_slider.pack(side=TOP)

    def get_tss_value(self):
        return self.tss_slider.get()

