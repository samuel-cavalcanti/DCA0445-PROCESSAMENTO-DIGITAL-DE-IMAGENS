import cv2
import numpy as np
import sys


def shift_dft(image: np.ndarray) -> np.ndarray:
    rows = image.shape[0]
    cols = image.shape[1]

    regions = [
        image[int(rows / 2):rows, int(cols / 2):cols],
        image[int(rows / 2):rows, 0:int(cols / 2)],
        image[0:int(rows / 2), int(cols / 2):cols],
        image[0:int(rows / 2), 0:int(cols / 2)]]

    a = np.hstack(np.array(regions[0:2]))

    b = np.hstack(np.array(regions[2:4]))

    return np.vstack((a, b))


def define_homomorphic_filter(rows: int, cols: int, d_0: float,
                              c: float, gamma_high: float, gamma_low: float) -> np.ndarray:
    homomorphic = np.zeros((rows, cols))

    for i in range(rows):
        for j in range(cols):
            d_2 = (i - rows / 2) ** 2 + (j - cols / 2) ** 2
            exp_value = np.exp(-c * d_2 / (d_0 ** 2))
            homomorphic[i, j] = (gamma_high - gamma_low) * (1 - exp_value) + gamma_low

    return cv2.merge([homomorphic, homomorphic])


def show_images(windows_name: list, images: list, time: int) -> str:
    for image, window_name in zip(images, windows_name):
        cv2.imshow(window_name, image)

    return chr(cv2.waitKey(time) & 255)


def options(key: str, c: float, gamma_high: float, gamma_low: float, d0: float) -> object:
    if key == "C":
        c += 0.5

    elif key == "c":
        c -= 0.5

        if c < 0:
            c = 0

    elif key == "G":
        gamma_low += 0.5

    elif key == "g":
        gamma_low -= 0.5
        if gamma_low < gamma_low + 1:
            gamma_low = gamma_low + 1

    elif key == "D":
        d0 += 0.5

    elif key == "d":
        d0 -= 0.5

    return c, gamma_high, gamma_low, d0


def main():
    original_image: np.ndarray = cv2.imread(sys.argv[1], cv2.IMREAD_GRAYSCALE)

    original_image = cv2.resize(original_image, (1280, 720))

    dft_rows = cv2.getOptimalDFTSize(original_image.shape[0])

    dft_cols = cv2.getOptimalDFTSize(original_image.shape[1])

    padded_rows = dft_rows - original_image.shape[0]

    padded_cols = dft_cols - original_image.shape[1]

    original_window_name = "original image"

    filtered_window_name = "Homomorphic filter"

    c = 1

    gamma_high = 2

    gamma_low = 0.5

    d0 = 8

    homomorphic = define_homomorphic_filter(dft_rows, dft_cols, d0, c, gamma_high, gamma_low)

    padded: np.ndarray = cv2.copyMakeBorder(original_image, 0, padded_rows, 0, padded_cols, cv2.BORDER_CONSTANT,
                                            value=[0, 0, 0])

    key = "não"

    while "\x1b" != key:  # esc

        planes = cv2.merge([np.log(padded + 1, dtype=np.float64), np.zeros(padded.shape, np.float64)])

        dft_image: np.ndarray = cv2.dft(planes)

        shifted_image = shift_dft(dft_image)

        # filtered_image: np.ndarray = cv2.mulSpectrums(shifted_image, homomorphic, 0)

        # dft_image = shift_dft(filtered_image)

        image = cv2.idft(dft_image)

        real, imaginary = cv2.split(image)

        # real = np.exp(real)

        cv2.normalize(real, real, alpha=0, beta=1, norm_type=cv2.NORM_MINMAX, dtype=cv2.CV_64F)

        key = show_images([original_window_name, filtered_window_name], [original_image, real], 0)

        c, gamma_high, gamma_low, d0 = options(key, c, gamma_high, gamma_low, d0)

        print("c {}, gamma high {} gamma low {} d_0 {}".format(c, gamma_high, gamma_low, d0))

        homomorphic = define_homomorphic_filter(dft_rows, dft_cols, d0, c, gamma_high, gamma_low)

        pass


if __name__ == '__main__':
    main()
