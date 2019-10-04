from tilt_shift import TiltShift
import cv2
import numpy as np



def show_image(dtype):
    while "e" != chr(cv2.waitKey(1) & 255):
        output_frame = (tilt_shift.tilt_shift * 255).astype(dtype)
        cv2.imshow("output_fraeme.astype(frame.dtype)", cv2.resize(output_frame, (500, 500)))


def main():
    cap = cv2.VideoCapture("data/ToyStoryScene.mkv")

    frame_width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))

    frame_height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

    fourcc = cv2.VideoWriter_fourcc(*'XVID')
    fourcc_2 = cv2.VideoWriter_fourcc("M", "J", "P", "G")
    out = cv2.VideoWriter("data/Toy_Story_tilted.mkv", fourcc,
                          int(cap.get(cv2.CAP_PROP_FPS)),
                          (frame_width, frame_height))

    tilt_shift = TiltShift(25, 45, 33)


    tilt_shift.show_track_bars("Tilt-Shift")

    if not cap.isOpened():
        print("erro vídeo não encontrado")
        exit(1)
    if not out.isOpened():
        print("erro ao  salvar o vídeo")
        exit(2)
    count = 0
    while "e" != chr(cv2.waitKey(1) & 255):
        ret, frame = cap.read()
        if ret:
            # resized_frame: np.ndarray = cv2.resize(frame, (500, 500))
            tilt_shift.set_image(frame)
            tilt_shift.show_tilt_shift(-1)
            print(cap.get(cv2.CAP_PROP_FRAME_COUNT) - count)
            count += 1

            output_frame = (tilt_shift.tilt_shift * 255).astype(frame.dtype)
            # cv2.imshow("output_fraeme.astype(frame.dtype)", cv2.resize(output_frame, (500, 500)))
            out.write(output_frame)

            # tilt_shift.show_tilt_shift(-1)
            # cv2.imshow("Toy Story", resized_frame)
        else:
            break

    out.release()
    cap.release()


if __name__ == '__main__':

    main()
