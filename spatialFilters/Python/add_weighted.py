import cv2
import numpy as np


def on_trackbar_blend(value: int):
    alpha = value / slider_max
    blended = cv2.addWeighted(blend_1, alpha, image_top, 1 - alpha, 0)
    cv2.imshow(window_name, blended)


def on_trackbar_line(value: int):
    image_top[:, :] = blend_1.copy()
    limit = int(value * 256 / 100)

    if limit > 0:
        rect = blend_2[0:limit, 0:256]
        image_top[0:limit, 0:256] = rect

    on_trackbar_blend(cv2.getTrackbarPos(alpha_track_bar_name, window_name))


def load_images() -> (np.ndarray, np.ndarray):
    path_file = "data/blend{}.jpg"

    return cv2.imread(path_file.format(1)), cv2.imread(path_file.format(2))


def create_trackbars():
    cv2.namedWindow(window_name)

    cv2.createTrackbar(alpha_track_bar_name, window_name, 0, slider_max, on_trackbar_blend)

    cv2.createTrackbar(scan_line_track_bar_name, window_name, 0, slider_max, on_trackbar_line)


if __name__ == '__main__':
    slider_max = 100
    alpha_track_bar_name = "alpha x"
    scan_line_track_bar_name = "Scan line x"
    window_name = "add weighted"

    blend_1, blend_2 = load_images()
    image_top = blend_1.copy()

    create_trackbars()

    on_trackbar_line(0)

    cv2.waitKey(0)
