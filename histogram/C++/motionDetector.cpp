/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   motionDetector.cpp
 * Author: samuel
 *
 * Created on August 25, 2019, 3:55 PM
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <vlc/vlc.h>

using namespace std;


bool motionDetector(std::vector<cv::Mat> *&oldChannels, cv::Mat &frame);

double getDist(cv::Mat &oldChannel, cv::Mat &newChannel);

int main(int argc, char **argv) {
    cv::VideoCapture cam = cv::VideoCapture(0);
    std::string windowName = "Cam";
    std::string exitKey = "e";
    cv::Mat frame;
    std::vector<cv::Mat> *oldChannels = NULL;
    libvlc_instance_t *inst;
    libvlc_media_player_t *mediaPlayer;
    libvlc_media_t *media;
    inst = libvlc_new(0, NULL);

    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);

    if (not cam.isOpened()) {
        std::cout << "Camera não encontrada" << std::endl;
        std::exit(1);
    }

    if (argc < 2) {
        std::cout << " passe como parametro o caminho da musica!" << std::endl;
        std::exit(-1);
    }

    media = libvlc_media_new_path(inst, argv[1]);
    mediaPlayer = libvlc_media_player_new_from_media(media);

    // não precisa mais da midia
    libvlc_media_release(media);


    while (exitKey != std::string(1, (char) (cv::waitKey(1) & 255))) {
        if (cam.read(frame)) {
            cv::imshow(windowName, frame);

            if (motionDetector(oldChannels, frame))
                if (not libvlc_media_player_is_playing(mediaPlayer))
                    libvlc_media_player_play(mediaPlayer);
        }

    }

    return 0;
}


bool motionDetector(std::vector<cv::Mat> *&oldChannels, cv::Mat &frame) {
    auto equalizedChannels = new std::vector<cv::Mat>(3);
    bool detected = false;
    double bodyMoved = 0.2;
    cv::Mat equalizedHist;
    cv::split(frame, *equalizedChannels);

    if (oldChannels) {
        for (int i = 0; i < equalizedChannels->size(); i++) {
            cv::equalizeHist(equalizedChannels->at(i), equalizedHist);

            if (getDist(equalizedHist, oldChannels->at(i)) > bodyMoved)
                detected = true;
        }
    } else
        for (auto &equalizedChannel : *equalizedChannels)
            cv::equalizeHist(equalizedChannel, equalizedChannel);

    oldChannels = equalizedChannels;

    return detected;
}

double getDist(cv::Mat &oldChannel, cv::Mat &newChannel) {
    int cv_32f = 5;
    cv::Mat oldChannelFloat;
    cv::Mat newChannelFloat;

    oldChannel.convertTo(oldChannelFloat, cv_32f);
    newChannel.convertTo(newChannelFloat, cv_32f);
    cv::normalize(oldChannelFloat, oldChannelFloat);
    cv::normalize(newChannelFloat, newChannelFloat);

    return cv::norm(oldChannelFloat, newChannelFloat);

}