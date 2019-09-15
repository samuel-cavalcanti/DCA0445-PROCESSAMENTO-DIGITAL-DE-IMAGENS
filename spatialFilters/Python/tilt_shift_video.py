from tilt_shift import TiltShift
import cv2
import numpy as np


def main():
    cap = cv2.VideoCapture("data/ToyStoryScene.mkv")
    frame_size = 500
    out = cv2.VideoWriter("data/Toy_Story_tilted.avi", cv2.VideoWriter_fourcc("M", "J", "P", "G"),
                          int(cap.get(cv2.CAP_PROP_FPS)),
                          (frame_size, frame_size))

    tilt_shift = TiltShift(60, 100, 33)
    tilt_shift.show_track_bars("Tilt-Shift")

    if not cap.isOpened():
        print("erro vídeo não encontrado")
        exit(1)

    while "e" != chr(cv2.waitKey(1) & 255):
        ret, frame = cap.read()
        if ret:
            # resized_frame: np.ndarray = cv2.resize(frame, (500, 500))
            tilt_shift.set_image(frame)
            tilt_shift.show_tilt_shift(-1)
            output_frame = (tilt_shift.tilt_shift * 255).astype(frame.dtype)
            cv2.imshow("output_frame.astype(frame.dtype)", output_frame)
            out.write(output_frame)

            # tilt_shift.show_tilt_shift(-1)
            # cv2.imshow("Toy Story", resized_frame)

    out.release()
    cap.release()


if __name__ == '__main__':
    main()
