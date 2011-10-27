import wx

"""
"""
class ManagerialAction:

	"""
	"""
	def __init__(self, managerUI):
		self.managerUI = managerUI	

	"""
	"""
	def OnTSS(self):
		tssSlider = self.managerUI.getTSSSlider()
		value = tssSlider.GetValue()
		print value
