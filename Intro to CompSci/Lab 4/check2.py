import check2_helper
from PIL import Image


im1 = Image.open('ca.jpg')
im2 = Image.open('im.jpg')
a1 = check2_helper.make_square(im1)
a2 = check2_helper.make_square(im2)
a1 = a1.resize((256,256))
a2 = a2.resize((256,256))

im3 = Image.open('hk.jpg')
im4 = Image.open('bw.jpg')
a3 = check2_helper.make_square(im3)
a4 = check2_helper.make_square(im4)
a3 = a3.resize((256,256))
a4 = a4.resize((256,256))

im = Image.new('RGB', (512, 512),color = 'white')
im.paste(a1, (0,0))
im.paste(a2, (256, 256))
im.paste(a3, (256,0))
im.paste(a4, (0, 256))
im.show()