import os, sys
sys.path.append("/Library/Python/2.7/site-packages/")
from PIL import Image

image_title = "river.png"
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
  for index in range(1, len(colors_list)):
    x = (index - 1)%width
    y = (index - 1)/width

    r = colors_list[index] >> 16
    g = (colors_list[index] >> 8) & 0xff
    b = colors_list[index] & 0xff
    image.putpixel( (x, y), (r, g, b))
  #endfor
  image.save(image_title, image_type)
