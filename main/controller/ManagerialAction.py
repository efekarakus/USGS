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
	def OnGo(self):
		managerUI = self.managerUI
		tssValue = managerUI.GetValue()
		print tssValue
