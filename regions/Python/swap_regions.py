import cv2
import sys
import numpy as np


def show_image(title: str, image: np.ndarray):
    cv2.namedWindow(title, cv2.WINDOW_NORMAL)
    cv2.imshow(title, image)
    cv2.waitKey(0)


def get_regions(image: np.ndarray) -> list:
    rows = image.shape[0]
    cols = image.shape[1]

    return [
        image[int(rows / 2):rows, int(cols / 2):cols],
        image[int(rows / 2):rows, 0:int(cols / 2)],
        image[0:int(rows / 2), int(cols / 2):cols],
        image[0:int(rows / 2), 0:int(cols / 2)]

    ]


def make_new_image(regions: list) -> np.ndarray:
    a = np.hstack(np.array(regions[0:2]))

    b = np.hstack(np.array(regions[2:4]))

    return np.vstack((a, b))


def main():
    image = cv2.imread(sys.argv[1], cv2.IMREAD_GRAYSCALE)

    regions = get_regions(image)

    new_image = make_new_image(regions)

    show_image("puzzle image", new_image)


if __name__ == '__main__':
    main()
