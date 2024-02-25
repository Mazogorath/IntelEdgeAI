import numpy as np
import cv2

color = cv2.imread("image.jpg", cv2.IMREAD_COLOR)

print(color.shape)
height, width, channels = color.shape
cv2.imshow("Original Image", color)

b, g, r = cv2.split(color)
rgb_split = np.concatenate((b, g, r), axis=1)
cv2.imshow("BGR_channels", rgb_split)

hsv = cv2.cvtColor(color, cv2.COLOR_BGR2HSV)

h, s, v = cv2.split(hsv)
hsv_split = np.concatenate((h, s, v), axis=1)
cv2.imshow("Split HSV", hsv_split)
print("h, s, v = ", h, s, v)

RGB = cv2.cvtColor(hsv, cv2.COLOR_HSV2RGB)
cv2.imshow("RGB", RGB)

gs = cv2.cvtColor(RGB, cv2.COLOR_RGB2GRAY)
cv2.imshow("gs", gs)
cv2.imwrite("ggs.jpg", gs)

cv2.waitKey()
cv2.destroyAllWindows()