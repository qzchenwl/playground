#!/usr/bin/python
from PIL import Image

im = Image.open('./2.JPG')
pix = im.load()
ref = (232,68,59)

for i in range(im.size[0]):
    for j in range(im.size[1]):
        if ref[0]*0.8 < pix[i,j][0] < ref[0]*1.2 and \
           ref[1]*0.8 < pix[i,j][1] < ref[1]*1.2 and \
           ref[2]*0.8 < pix[i,j][2] < ref[2]*1.2:
            pix[i,j] = (255,255,255)
        else:
            pix[i,j] = (0,0,0)
im.show()
