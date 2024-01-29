from PIL import Image
def make_square(image):
    if(image.size[0] > image.size[1]):
        image = image.crop((0,0,image.size[1],image.size[1]))
    if(image.size[0] < image.size[1]):
        image = image.crop((0,0,image.size[0],image.size[0]))
    return image

#im = Image.open('1.jpg')
#imsquare = make_square(im)
#imsquare.show()