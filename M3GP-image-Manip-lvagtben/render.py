
import cv2
import sys
import copy
# Kaleidoscope requires numpy. Uncomment this line and install it if you need to.
import numpy as np

# Store command line arguments in variables
# TODO: change the next line to store the filename
filename = sys.argv[1]
manip = sys.argv[2]

# Open the image file
img = cv2.imread(filename)
# Get the dimensions (in pixels) of the image
dimensions = img.shape
# Copy the original image into an image for manipulation
img_manip = cv2.resize(img, (dimensions[1], dimensions[0]))
# TODO: Store white in a list, where each of the three parts is on a scale of [0, 255]
white = [255, 255, 255]
def manipulate ( manip ):
    for x in range(dimensions[0]):
        for y in range(dimensions[1]):
            if manip == 'flip':
                img_manip[x, y] = img[dimensions[0]-1-x, y]
            elif manip == 'mirror':
                # TODO: mirror the image and store in img_manip[x, y]
                img_manip[x, y] = img[x, dimensions[1]-1-y]
            elif manip == 'invert':
                # TODO: invert the image and store in img_manip[x, y]
                # Hint: img[x, y] returns the color of the pixel at that coordinate.
                # You can invert by subtracting that color from white.
                img_manip[x, y] = white - img[x, y] 
            elif manip == 'flip and mirror':
                img_manip[x, y] = img[dimensions[0]-1-x, dimensions[1]-1-y]
                

manipulate(manip)

# Displays the original image in the top left corner of the screen.
image = 'Original image'
cv2.namedWindow(image)
cv2.moveWindow(image, 0, 0)
cv2.imshow(image, img)
# TODO: Display the manipulated image alongside the original image.
manipulated_image = "Manipulated image"
cv2.namedWindow(manipulated_image)
cv2.moveWindow(manipulated_image, dimensions[1], 0)
cv2.imshow(manipulated_image, img_manip)



# TODO: Create a kaleidoscope image, display it, and save it to a file.
manipulate('flip')
flipped_img = copy.deepcopy(img_manip)
manipulate('mirror')
kaleidoscope_top = np.concatenate((img, img_manip), axis=1)
manipulate('flip and mirror')
kaleidoscope_bot = np.concatenate((flipped_img, img_manip), axis=1)
kaleidoscope = np.concatenate((kaleidoscope_top, kaleidoscope_bot), axis=0)
cv2.imshow('kaleidoscope', kaleidoscope)
cv2.imwrite('kaleidoscope.png', kaleidoscope)


# This line puts two images side-by-side in one window.
horizontal_concat = np.concatenate((img, img_manip), axis=1)
# TODO: Save the image using the imwrite method from cv2
cv2.imwrite('Horizontal Concatenation.png', horizontal_concat)
# TODO: Show the image
cv2.imshow('Horizontal Concatenation!', horizontal_concat)


# Infinite loop to keep the windows open until the escape key is pressed.
while True:
    k = cv2.waitKey(1)
    if k == 27:
        cv2.destroyAllWindows()
        exit()

