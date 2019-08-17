import cv2
import numpy as np


def show_image(title: str, image: np.ndarray):
    cv2.namedWindow(title, cv2.WINDOW_NORMAL)
    cv2.imshow(title, image)
    cv2.waitKey()


def count_objects(image: np.ndarray, gray_scale_color=255, show=False) -> (int, np.ndarray):
    n_objects = 1
    flood_fill_image = image.copy()

    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            if flood_fill_image[i, j] == gray_scale_color:
                if n_objects >= 255:
                    cv2.floodFill(flood_fill_image, None, (j, i), 100)
                else:
                    cv2.floodFill(flood_fill_image, None, (j, i), n_objects)

                n_objects += 1

    if show:
        print(n_objects - 1)
        show_image("floodFill", flood_fill_image)

    return n_objects - 1, flood_fill_image


def removing_objects_on_limits(image: np.ndarray):
    white = 255
    black = 0

    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            if (j == 0 or j == image.shape[1] - 1) and image[i, j] == white:
                cv2.floodFill(image, None, (j, i), black)

            if (i == 0 or i == image.shape[0] - 1) and image[i, j] == white:
                cv2.floodFill(image, None, (j, i), black)


def counting_holes(image: np.ndarray) -> int:
    white = 255
    black = 0
    holes = 0

    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            if image[i, j] == black and (black < image[i, j - 1] < white):
                cv2.floodFill(image, None, (j - 1, i), black)
                cv2.floodFill(image, None, (j, i), white)
                holes += 1

    return holes


def count_objects_and_holes(image: np.ndarray) -> (int, int, int):
    hole_counter_image = image.copy()

    removing_objects_on_limits(hole_counter_image)

    all_objects, hole_counter_image = count_objects(hole_counter_image)

    holes = counting_holes(hole_counter_image)

    return all_objects, holes, all_objects - holes


def main():
    image = cv2.imread("images/bolhas.png", cv2.IMREAD_GRAYSCALE)

    print("counting objects_and_holes")

    all_objects, holes, no_holes = count_objects_and_holes(image)

    print("all objects {} \nobjects with hole {} \nobjects with no hole {}".format(all_objects, holes, no_holes))

    print("just counting objects")

    objects, _ = count_objects(image)

    print("objects {}".format(objects))


if __name__ == '__main__':
    main()
