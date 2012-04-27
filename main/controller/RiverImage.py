import os, sys
sys.path.append("/Library/Python/2.7/site-packages/")
from PIL import Image
import numpy as np
import colorsys
from time import strftime as date

hsv_to_rgb = np.vectorize(colorsys.hsv_to_rgb)

timestamp = ""
image_title = "results\pic"
extension = ".png"
image_type = "PNG"
image = None

def output_image(colors_list):
  """
  Creates an image in the current directory of the result of the modeling
  @param colors_list: array of colors representing the Mississippi river
  """
  # find the image size
  size = len(colors_list) - 1
  width = colors_list[0]
  height = size/width
  size = (width, height)

  
  image = Image.new("RGBA", size)
  hue_value = colors_list[1]
  hue = []
  saturation = []
  value = []
  #Get Hue and Value
  for y in range(height):
    hue.append([])
    saturation.append([])
    value.append([])
    for x in range(width):
      hue[y].append(hue_value)
      value[y].append(255)
  
  for index in range(2, len(colors_list)):
    x = (index - 2)%width
    y = (index - 2)/width
	#If the patch is ground
    if(colors_list[index] == -1):
      hue[y][x] = 11.31 / 360.0
      value[y][x] = 0.59*255
      saturation[y].append(0.67)
    else:
      saturation[y].append(colors_list[index])

  r, g, b = hsv_to_rgb(hue, saturation, value)
  arr = np.dstack((r, g, b))
  new_img = Image.fromarray(arr.astype('uint8'), "RGB")	
  for index in range(2, len(colors_list)):
    x = (index - 2)%width
    y = (index - 2)/width
    pixel = new_img.getpixel( (x,y))
	# the order is inverted in the y-axis
    image.putpixel( (x, height-y-1), pixel)
  #endfor
  timestamp = date('%d-%m-%Y %H_%M_%S')
  image.save(image_title + timestamp + extension, image_type)
  return
