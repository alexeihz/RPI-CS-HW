import check2_helper
from PIL import Image


im1 = Image.open('1.jpg')
im2 = Image.open('2.jpg')

#a1 = check2_helper.make_square(im1)
#a2 = check2_helper.make_square(im2)
a1 = im1.resize((int(im1.size[0]/(im1.size[1]/256)),256))
a2 = im2.resize((int(im2.size[0]/(im2.size[1]/256)),256))

im3 = Image.open('3.jpg')
im4 = Image.open('4.jpg')

#a3 = check2_helper.make_square(im3)
#a4 = check2_helper.make_square(im4)
a3 = im3.resize((int(im3.size[0]/(im3.size[1]/256)),256))
a4 = im4.resize((int(im4.size[0]/(im4.size[1]/256)),256))

im5 = Image.open('5.jpg')
im6 = Image.open('6.jpg')

#a1 = check2_helper.make_square(im1)
#a2 = check2_helper.make_square(im2)
a5 = im5.resize((int(im5.size[0]/(im5.size[1]/256)),256))
a6 = im6.resize((int(im6.size[0]/(im6.size[1]/256)),256))


im = Image.new('RGB', (1000, 360),color = 'white')
im.paste(a1, (31,20))
im.paste(a2, (a2.size[0]+41, 60))
im.paste(a3, (a3.size[0]+a2.size[0]+51,20))
im.paste(a4, (a4.size[0]+a3.size[0]+a2.size[0]+61, 60))
im.paste(a5, (a5.size[0]+a4.size[0]+a3.size[0]+a2.size[0]+71, 20))
im.paste(a6, (a6.size[0]+a5.size[0]+a4.size[0]+a3.size[0]+a2.size[0]+91, 60))
im.show()