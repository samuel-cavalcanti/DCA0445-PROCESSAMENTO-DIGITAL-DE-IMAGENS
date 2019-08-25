import cv2
import numpy as np
import vlc


def equalized_bgr_frame(frame: np.ndarray) -> list:
    equalized_channels = list()

    for channel in cv2.split(frame):
        equalized_channels.append(cv2.equalizeHist(channel))

    return equalized_channels


def stack_to_show(frame: np.ndarray, channels: list) -> np.ndarray:
    hs_stacking = list()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    for channel in channels:
        hs_stacking.append(np.hstack((gray, channel)))

    return np.vstack(tuple(hs_stacking))

    # exit(1)


def motion_detector(old_equalized_channels: list, new_equalized_channels: list) -> bool:
    all_dis = list()
    if old_equalized_channels:
        for old_channel, new_channel in zip(old_equalized_channels, new_equalized_channels):
            dist = np.linalg.norm((old_channel.flatten() / 255) - (new_channel.flatten() / 255))
            all_dis.append(dist)

        if np.max(all_dis) > 50:
            return True
        else:
            return False

    else:
        return False


def main():
    cam = cv2.VideoCapture(0)

    window_name = "frame"
    cv2.namedWindow(window_name, cv2.WINDOW_NORMAL)

    player = vlc.MediaPlayer("music/babyshark.mp3")

    old_equalized_channels = list()

    if not cam.isOpened():
        print("não achou a camera !!")
        exit(1)

    while "e" != chr(cv2.waitKey(1) & 255):
        ret, frame = cam.read()
        if ret:
            new_equalized_channels = equalized_bgr_frame(frame)
            if motion_detector(old_equalized_channels, new_equalized_channels):
                if not player.get_state():
                    player.play()

            old_equalized_channels = new_equalized_channels
            cv2.imshow(window_name, frame)
    pass


if __name__ == '__main__':
    main()
