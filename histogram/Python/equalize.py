import cv2
import numpy as np


def main():
    cam = cv2.VideoCapture(0)

    window_name = "frame and equalized frame"
    cv2.namedWindow(window_name, cv2.WINDOW_NORMAL)

    if not cam.isOpened():
        print("não achou a camera !!")
        exit(1)

    while "e" != chr(cv2.waitKey(1) & 255):
        ret, frame = cam.read()
        if ret:
            gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            equalized_frame = cv2.equalizeHist(gray_frame)
            equalized_frame_and_frame = np.hstack((gray_frame, equalized_frame))
            cv2.imshow(window_name, equalized_frame_and_frame)


if __name__ == '__main__':
    main()
