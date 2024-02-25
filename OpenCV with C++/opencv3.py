import numpy as np
import cv2

img = cv2.imread("my_input.jpg")

print(img.shape)

cropped = img[21:90, 166:212]

resized = cv2.resize(cropped, (138, 92))

cv2.imshow("Original", img)
cv2.imshow("Cropped image", cropped)
cv2.imshow("Resized image", resized)
rotated = cv2.rotate(resized, cv2.ROTATE_90_CLOCKWISE)
cv2.imshow("Rotated", rotated)

cv2.waitKey()
cv2.destroyAllWindows()