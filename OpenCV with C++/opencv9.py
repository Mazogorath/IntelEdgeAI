import numpy as np
import cv2
src = cv2.imread("tomato.jpg", cv2.IMREAD_COLOR)
#b, g, r = cv2.split(src)
b = src[:, :, 0]
g = src[:, :, 1]
r = src[:, :, 2]
inverse = cv2.merge((r, g, b))

height, width, channel = src.shape
zero = np.zeros((height, width, 1), dtype=np.uint8)
bgz = cv2.merge((b, g, zero))

cv2.imshow("b", b)
cv2.imshow("g", g)
cv2.imshow("r", r)
cv2.imshow("bgz", bgz)
cv2.imshow("inverse", inverse)
cv2.waitKey()
cv2.destroyAllWindows()