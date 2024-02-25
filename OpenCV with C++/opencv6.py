import numpy as np
import cv2

src = cv2.imread("my_input.jpg", cv2.IMREAD_COLOR)
dst = cv2.blur(src, (9, 9), anchor=(-1, 1), borderType=cv2.BORDER_REFLECT)
cv2.imshow("src", src)
cv2.imshow("dst", dst)
key = cv2.waitKey()
if key == 's' or 'S':
    cv2.imwrite("dst1", dst)
cv2.destroyAllWindows()