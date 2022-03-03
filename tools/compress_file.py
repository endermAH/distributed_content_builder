#!/usr/local/opt/python/libexec/bin/python

from PIL import Image
import sys
import random
import time

time.sleep(random.randint(10,100))

args = sys.argv
path_original = args[1]
path_compressed = args[2]

image_original = Image.open(path_original)
image_size = image_original.size
new_size = (int(image_size[0]/2), int(image_size[1]/2))

image_compressed = image_original.resize(new_size, Image.ANTIALIAS)
image_compressed.save(path_compressed, optimize=True, quality=95)