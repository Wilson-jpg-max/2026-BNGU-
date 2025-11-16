//
// Created by wilson on 2025/11/15.
//

#ifndef VIDEOPROCESSOR_H//防止头文件被重复包含
#define VIDEOPROCESSOR_H

#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;
using namespace std;
class VideoProcessor {
private:
    VideoCapture cap;
    string VideoPath;//存储要读取的视频路径的字符串
public:
    VideoProcessor(const string&path)://创建对象时传入视频路径并初始化
    VideoPath(path){}//将传入的path赋值给Videopath
    bool openVideo() {//创建视频打开函数，同时输出bool型来判断是否打开成功
        cap.open(VideoPath);
        return cap.isOpened();
    }
    bool readFrame(Mat&Frame) {//Frame to Mat
        return cap.read(Frame);
    }

};

#endif
