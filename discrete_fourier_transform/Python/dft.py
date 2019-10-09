import numpy as np
import cv2


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


def show_images(windows_name: list, images: list, time: int) -> str:
    for image, window_name in zip(images, windows_name):
        cv2.imshow(window_name, image)

    return chr(cv2.waitKey(time) & 255)


def define_low_pass_filter(rows: int, cols: int, radius: int) -> np.ndarray:
    low_pass = np.zeros((rows, cols))

    for i in range(rows):
        for j in range(cols):
            if (i - rows / 2) ** 2 + (j - cols / 2) ** 2 < radius ** 2:
                low_pass[i, j] = 1.

    return cv2.merge([low_pass, low_pass])


def apply_noise(image: np.ndarray, gain: int, freq: int):
    center = [image.shape[0] // 2, image.shape[1] // 2]

    mean = np.abs(image[center[0], center[1], 0])

    image[center[0] + freq, center[1] + freq, 0] += gain * mean

    image[center[0] + freq, center[1] + freq, 1] += gain * mean

    image[center[0] - freq, center[1] - freq, 0] = image[center[0] + freq, center[1] + freq, 0]

    image[center[0] - freq, center[1] - freq, 1] = - image[center[0] + freq, center[1] + freq, 1]


def options(key: str, freq: int, gain: int, noise: bool, dft_rows: int) -> (int, int, bool):
    if key == "q":
        freq += 1

        if freq > dft_rows / 2 - 1:
            freq = dft_rows / 2 - 1

    elif key == "a":
        freq -= 1

        if freq < 1:
            freq = 1

    elif key == "x":
        gain += 0.1

    elif key == "z":
        gain -= 0.1
        if gain < 0:
            gain = 0

    elif key == "e":
        noise = not noise

    return freq, gain, noise


def main():
    cap = cv2.VideoCapture(0)

    if not cap.isOpened():
        print("erro ao abrir a câmera")
        exit(1)

    rows = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

    cols = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))

    dft_rows = cv2.getOptimalDFTSize(rows)

    dft_cols = cv2.getOptimalDFTSize(cols)

    padded_rows = dft_rows - rows

    padded_cols = dft_cols - cols

    low_pass_filter = define_low_pass_filter(dft_rows, dft_cols, 20)

    key = "não"

    freq = 10
    gain = 0

    noise = False

    while "\x1b" != key:  # esc
        ret, frame = cap.read()
        if not ret:
            break

        gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        padded = cv2.copyMakeBorder(gray_frame, 0, padded_rows, 0, padded_cols, cv2.BORDER_CONSTANT, value=[0, 0, 0])

        planes = cv2.merge([np.float64(padded), np.zeros(padded.shape, np.float64)])

        dft_image: np.ndarray = cv2.dft(planes)

        shifted_image = shift_dft(dft_image)

        filtered_image: np.ndarray = cv2.mulSpectrums(shifted_image, low_pass_filter, 0)

        if noise:
            apply_noise(filtered_image, gain, freq)

        dft_image = shift_dft(filtered_image)

        cv2.idft(dft_image, dft_image)

        real, imaginary = cv2.split(dft_image)

        cv2.normalize(real, real, alpha=0, beta=1, norm_type=cv2.NORM_MINMAX, dtype=cv2.CV_64F)

        key = show_images(["gray_Frame", "dft"], [gray_frame, real], 1)

        freq, gain, noise = options(key, freq, gain, noise, dft_rows)


if __name__ == '__main__':
    main()
