import numpy as np
import cv2

image = cv2.imread("my_input.jpg")

cv2.namedWindow("image", cv2.WINDOW_NORMAL)

print(image.shape)

cv2.imshow("image", image)

key = cv2.waitKey()
if key == ord('s'):
    cv2.imwrite("image.jpg", image)
else:
    print("1")

cv2.destroyAllWindows()
