from PIL import Image
import numpy as np


im = Image.open('lion.jpeg')
# im.show()

def export_image_to_array_txt():
	l = list(im.getdata())
	# arr.flatten()
	# print(arr.shape)
	l2 = list()
	file1 = open("pixels1.txt", "a")
	for item in l:
		for i in item:
			file1.write(str(i) + '\n')

	file1.close()

def import_image_from_txt():
	file1 = open("pixels2.txt", "r")
	lines = file1.readlines()
	l2 = list()
	for l in range(0, len(lines), 3):
		pixel_tuple = (lines[l], lines[l+1], lines[l+2])
		l2.append(pixel_tuple)
		"""
	l3 = list()
	for pixel in l2:
		avg = (int(pixel[0]) + int(pixel[1]) + int(pixel[2])) / 3
		avg_pixel = (avg, avg, avg)
		l3.append(avg_pixel)
		"""

	arr = np.array(l2)
	arr.resize(im.height, im.width, 3)
	im2 = Image.fromarray(arr.astype('uint8'), 'RGB')
	im2.show()

import_image_from_txt()