import cv2
import numpy as np


class TiltShift:
    __slider_max = 100
    __track_bars = False
    __d_window_name = "força de decaimento"
    __l1_window_name = "deslocamento 1"
    __l2_window_name = "deslocamento 2"
    __window_name = "Tilt-Shift"
    __original_image: np.ndarray = None
    __blurred_image: np.ndarray = None
    __ones: np.ndarray = None
    tilt_shift: np.ndarray = None
    __delay = -1

    def __init__(self, l1=30, l2=60, d=30):
        self.__d = d
        self.__l1 = l1
        self.__l2_len = l2
        self.__mean_kernel = np.ones((9, 9), np.float32) / 81

    def __create_track_bars(self, window_name: str):
        try:
            cv2.getWindowProperty(window_name, 0)
        except:
            cv2.namedWindow(window_name)

        self.__window_name = window_name

        cv2.createTrackbar(self.__d_window_name, window_name, self.__d, self.__slider_max, self.__change)

        cv2.createTrackbar(self.__l1_window_name, window_name, self.__l1, self.__slider_max, self.__change)

        cv2.createTrackbar(self.__l2_window_name, window_name, self.__l2_len, self.__slider_max, self.__change)

        self.__track_bars = True

    def __alpha_f(self, x) -> float:
        l2 = self.__l1 + self.__l2_len
        return 0.5 * (np.tanh((x - self.__l1) / self.__d) - np.tanh((x - l2) / self.__d))

    def __change(self, value: int):
        self.__update_parameters()

        original_weight = np.zeros(self.__original_image.shape)
        blurred_weight = np.zeros(self.__blurred_image.shape)

        for x in range(int(original_weight.shape[0])):
            alpha = self.__alpha_f(x)

            blurred_weight[x, :] += 1 - alpha
            original_weight[x, :, :] += alpha

        tilt = np.multiply(original_weight, self.__original_image) / 255
        shift = np.multiply(blurred_weight, self.__blurred_image) / 255

        self.tilt_shift = tilt + shift
        if self.__delay > -1:
            cv2.imshow(self.__window_name, self.tilt_shift)

    @staticmethod
    def __normalize(x: int, t: int) -> float:
        return x * t / 100

    def __update_parameters(self):

        if self.__track_bars:
            self.__l1 = cv2.getTrackbarPos(self.__l1_window_name, self.__window_name) - 1
            self.__l2_len = cv2.getTrackbarPos(self.__l2_window_name, self.__window_name)
            self.__d = 0.5 * cv2.getTrackbarPos(self.__d_window_name, self.__window_name) + 1

            self.__l1 = self.__normalize(self.__l1, self.__original_image.shape[0])
            self.__l2_len = self.__normalize(self.__l2_len, self.__original_image.shape[1] / 2)


    def show_track_bars(self, window_name: str):
        if not self.__track_bars:
            self.__create_track_bars(window_name)

    def show_tilt_shift(self, delay: int):
        self.__delay = delay
        self.__change(0)

        if delay > -1:
            cv2.imshow("original image", self.__original_image)
            cv2.waitKey(delay)

    def __blurring_image(self):
        self.__blurred_image = cv2.filter2D(self.__original_image, cv2.CV_32F, self.__mean_kernel)

        for i in range(5):
            self.__blurred_image = cv2.filter2D(self.__blurred_image, cv2.CV_32F, self.__mean_kernel)

    def load_image(self, image_path: str):
        self.__original_image = cv2.imread(image_path)
        if self.__original_image is None:
            print("Imagem não encontrada !!")
            exit(1)
        self.__blurring_image()

    def set_image(self, image: np.ndarray):
        self.__original_image = image
        self.__blurring_image()

    def test_function_alpha(self):
        from matplotlib import pyplot

        x = np.array([i for i in range(129)])
        y = self.__alpha_f(x)

        pyplot.plot(x, 1 - y)
        pyplot.show()

    def save_image(self, path: str):
        cv2.imwrite(path, cv2.UMat(self.tilt_shift * 255))


if __name__ == '__main__':
    tilt_shift = TiltShift()

    tilt_shift.load_image("data/blend2.jpg")
    tilt_shift.show_track_bars("Tilt-Shift")
    tilt_shift.show_tilt_shift(0)

    tilt_shift.save_image("data/tiltShift_blend2.jpg")
