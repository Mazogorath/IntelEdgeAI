import numpy as np
import cv2

cap = cv2.VideoCapture("ronaldinho.mp4")

while (cap.isOpened()):
    ret, frame = cap.read()

    if ret is False:
        print("Can't receive frame")
        break

    cv2.resize(frame, dsize=(640, 320))
    cv2.imshow("Frame", frame)
    key = cv2.waitKey(30)
    if key & 0xFF == ord('q'):
        cap.release()
        break


cv2.destroyAllWindows()
