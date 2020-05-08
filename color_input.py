from PIL import Image
import csv

csv_columns = ['X,Y coords','RGB val']
def openFile(filename):
    pillow_Im = Image.open(filename)
    width, height = pillow_Im.size
    image = pillow_Im.load()
    return image, width, height

def RGBAtoRGB(pixel):
    red, green, blue, alpha = pixel
    return (red,green,blue)

def write_to_file(pixel_dictionary):
    out_file = "pixelOutput.csv"
    try: 
        w = open(out_file, "w")
        
        for key, val in pixel_dictionary.items():
            w.write(key)
            w.write(":")
            w.write(val)
            w.write("~")
    except IOError:
        print("I/O error")

image, width, height = openFile('test.png')
pixel_dictionary = dict()
for x in range(1,width):
    for y in range(1,height):
        location = str(x)+","+str(y)
        pixel_dictionary[location] = str(RGBAtoRGB(image[x,y]))

write_to_file(pixel_dictionary)
print("Execution complete")