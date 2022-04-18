"""
Script for splitting skybox images
"""

from PIL import Image
import sys, os

path = os.path.abspath("") + "/";
processed = False
	

def processImage(path, name):
	img = Image.open(os.path.join(path, name))
	w, h = img.size
	splitAndSave(img, w/2, h/3, (3 * w) / 4, (2 * h)/3, addToFilename(name, "_right"))
	splitAndSave(img, w / 4, (2 * h) / 3, w / 2, h,addToFilename(name, "_bottom"))
	splitAndSave(img, 0, h/3, w / 4, (2 * h) / 3, addToFilename(name, "_left"))
	splitAndSave(img, w/4, h/3, w/2, (2*h)/3, addToFilename(name, "_front"))
	splitAndSave(img, (3*w)/4, h/3, w, (2*h)/3, addToFilename(name, "_back"))
	splitAndSave(img, w / 4, 0, w/2, h/3, addToFilename(name, "_top"))

def addToFilename(name, add):
	name = name.split('.')
	return name[0] + add + "." + name[1]

def splitAndSave(img, startX, startY, endX, endY, name):
	area = (startX, startY, endX, endY)
	saveImage(img.crop(area), path, name)

def saveImage(img, path, name):
	try:
		img.save(os.path.join(path, name))
	except:
		print ("*   ERROR: Could not convert image.")
		pass

for arg in sys.argv:
	if ".png" in arg or ".jpg" in arg:
		processImage(path, arg)
		processed = True

if not processed:
	print ("*  ERROR: No Image")
	print ("   usage: 'python script.py image-name.png'")

