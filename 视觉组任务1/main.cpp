#include "VideoProcessor.h"
#include "ArmorDetector.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main() {
    VideoProcessor
    video("zhuangjiabanTEST.mp4");
    ArmorDetector armorDetect;
    if (!video.openVideo()) {
        cout<< "failed" << endl;
        return -1;}
    Mat frame;
    while (true) {
        if (!video.readFrame(frame))
            break;
        if (frame.empty()) break;
        armorDetect.processFrame(frame);
        imshow ("Frame", frame);
        if (waitKey(10) == 27)break;

    }
    destroyAllWindows();
    return 0;
}















