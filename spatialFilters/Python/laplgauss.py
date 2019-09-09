import numpy as np
import cv2


class Menu:
    __options = dict()
    __absolute = True

    def __init__(self):
        scale = 1 / 9
        self.__mean_kernel = scale * np.array([[1, 1, 1],
                                               [1, 1, 1],
                                               [1, 1, 1]]).reshape((3, 3))

        self.__gauss_kernel = scale * np.array([[1, 2, 1],
                                                [2, 4, 2],
                                                [1, 2, 1]]).reshape((3, 3))

        self.__horizontal_kernel = scale * np.array([[-1, 0, 1],
                                                     [-2, 0, 2],
                                                     [-1, 0, 1]]).reshape((3, 3))

        self.__vertical_kernel = scale * np.array([[-1, -2, -1],
                                                   [0, 0, 0],
                                                   [1, 2, 1]]).reshape((3, 3))

        self.__laplacian_kernel = scale * np.array([[0, -1, 0],
                                                    [-1, 4, -1],
                                                    [0, -1, 0]]).reshape((3, 3))

        self.__options["m"] = self.__mean
        self.__options["g"] = self.__gauss
        self.__options["h"] = self.__horizontal
        self.__options["v"] = self.__vertical
        self.__options["l"] = self.__laplacian
        self.__options["j"] = self.__laplace_over_gauss

        self.__filter = self.__mean

    def print_menu(self):
        menu_options = "\npressione a tecla para ativar o filtro: \n" \
                       "a - calcular modulo\n" \
                       "m - media\n" \
                       "g - gauss\n" \
                       "v - vertical\n" \
                       "h - horizontal\n" \
                       "l - laplaciano\n" \
                       "j - laplaciano do gaussiano" \
                       "e - sair\n"

        print(menu_options)

    def set_option(self, option: str):

        if option == "a":
            self.__absolute = not self.__absolute
        else:
            self.__filter = self.__options.get(option, self.__filter)

    def get_filtered_image(self, frame: np.ndarray) -> np.ndarray:

        filtered = self.__filter(frame)

        if self.__absolute:
            filtered = np.abs(filtered)

        return filtered

    def __laplace_over_gauss(self, frame: np.ndarray) -> np.ndarray:

        filtered = cv2.filter2D(frame, cv2.CV_32F, self.__gauss_kernel)

        filtered = cv2.filter2D(filtered, cv2.CV_32F, self.__laplacian_kernel)
        return filtered

    def __mean(self, frame: np.ndarray) -> np.ndarray:
        return cv2.filter2D(frame, cv2.CV_32F, self.__mean_kernel)

    def __gauss(self, frame: np.ndarray) -> np.ndarray:
        return cv2.filter2D(frame, cv2.CV_32F, self.__gauss_kernel)

    def __horizontal(self, frame: np.ndarray) -> np.ndarray:
        return cv2.filter2D(frame, cv2.CV_32F, self.__horizontal_kernel)

    def __vertical(self, frame: np.ndarray) -> np.ndarray:
        return cv2.filter2D(frame, cv2.CV_32F, self.__vertical_kernel)

    def __laplacian(self, frame: np.ndarray) -> np.ndarray:
        return cv2.filter2D(frame, cv2.CV_32F, self.__laplacian_kernel)


def main():
    cam = cv2.VideoCapture(0)
    window_name_cam = "Cam"
    window_name_filter = "filtered"
    cv2.namedWindow(window_name_cam)
    cv2.namedWindow(window_name_filter)
    menu = Menu()

    if not cam.isOpened():
        print("não achou a camera !!")
        exit(1)

    option = "m"

    while "e" != option:
        ret, frame = cam.read()
        if ret:
            gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

            menu.set_option(option)

            filtered = menu.get_filtered_image(gray_frame)

            cv2.imshow(window_name_cam, frame)
            cv2.imshow(window_name_filter, filtered)

            option = chr(cv2.waitKey(1) & 255)


if __name__ == '__main__':
    main()
