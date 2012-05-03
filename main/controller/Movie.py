import sys, os
import Tkinter, Image, ImageTk
from time import sleep

#Example code for how Tkinter could create a movie out of multiple images

def display_movie(images, fps=10):
	"""
	Display a movie of PIL Images.
	"""

	# Set up the root frame
	root = Tkinter.Tk()
	root.title("Info 103 Movie Viewer")

	# Set the size to the largest frame
	max_h = max([x.size[0] for x in images])
	max_w = max([x.size[1] for x in images])
	root.geometry('%dx%d' % (max_h, max_w))
	
	# frame iteration index
	index = 0
	
	# List of Tkinter PhotoImages from the PIL images
	tkimgs = [ImageTk.PhotoImage(x) for x in images]

	# Create a label in the root frame with the first image
	label_image = Tkinter.Label(root)
	label_image.pack()

	# Loop until exit
	while 1:
		# When pressing the exit button, root ceases to exist, and
		# throws an exception. Catch it and break the loop.
		try:
			# Replace the image.
			label_image.config(image=tkimgs[index])

			# Need to use update() instead of mainloop(). mainloop()
			# fights with IDLE's mainloop(), which isn't cool.
			# This works in and out of IDLE.
			root.update()
			
		except Exception, e:
			print "Closing the movie viewer."
			break

		# Sleep for the time specified by the framerate, fps.
		sleep(1./fps)
		
		# Move to the next frame, looping around.
		index += 1
		index %= len(images)
		
class movie:

   def __init__(self):
      # collection of images
      self.imgList = []
      return

   ''' addImage takes an image and simply 
   appends it to the list of images.       '''
   def addImage(self, newImage):
      self.imgList.append(newImage)

   ''' play takes an display rate and shows 
   the movie by making a call to the display
   function we've used before              '''
   def play(self, rate):
      image_display.display_movie(self.imgList,rate)
      return