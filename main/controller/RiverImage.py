from PIL import Image

imageTitle = "river.png"
imageType = "PNG"
image = None


"""
@param colorsList
"""
def outputImage(colorsList):

  # find the image size
  size = len(colorsList) - 1
  width = colorsList[0]
  height = size/width
  size = (width, height)

  image = Image.new("RGBA", size)
  for index in range(1, len(colorsList)):
    x = (index - 1)%width
    y = (index - 1)/width

    r = colorsList[index] >> 16
    g = (colorsList[index] << 16) >> 24
    b = (colorsList[index] << 24) >> 24
    image.putpixel( (x, y), (r, g, b))
  #endfor
  image.save(imageTitle, imageType)
