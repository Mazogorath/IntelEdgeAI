import numpy as np
import cv2

src = cv2.imread("my_input.jpg", cv2.IMREAD_COLOR)
src2 = cv2.imread("ggs.jpg", cv2.IMREAD_COLOR)
dst = cv2.bitwise_not(src)
dst2 = cv2.bitwise_and(src, src2)
dst3 = cv2.bitwise_or(src, src2)
dst4 = cv2.bitwise_xor(src, src2)

cv2.imshow("src", src)
cv2.imshow("not", dst)
cv2.imshow("and", dst2)
cv2.imshow("or", dst3)
cv2.imshow("xor", dst4)
cv2.waitKey()
cv2.destroyAllWindows()