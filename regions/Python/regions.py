import cv2
import sys


def main():
    image = cv2.imread(sys.argv[1], cv2.IMREAD_GRAYSCALE)

    r = cv2.selectROI("ROI", image)

    image[int(r[1]):int(r[1] + r[3]), int(r[0]):int(r[0] + r[2])] = 255 - image[int(r[1]):int(r[1] + r[3]),
                                                                          int(r[0]):int(r[0] + r[2])]

    cv2.imshow("region", image)
    cv2.waitKey(0)


if __name__ == '__main__':
    main()
