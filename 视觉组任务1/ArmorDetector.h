//
// Created by wilson on 2025/11/15.
//

#ifndef ARMORDETECTOR_H
#define ARMORDETECTOR_H

#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;
class ArmorDetector {
    private:
    double epsilonRatio=0.02;
    public:
    void processFrame(cv::Mat&frame)
    {
        Mat gray,blurred,binary;
        vector<vector<Point>> contours;//存储所有检测到的轮廓
        vector<Vec4i> hierarchy;//储存轮廓的层级关系
        vector<Point2f> allpoints ;
        cvtColor(frame,gray,COLOR_BGR2GRAY);//将彩色帧转化为灰度帧
        GaussianBlur(gray,blurred,Size(5,5),0,0);
        threshold(blurred,binary,127,255,THRESH_BINARY);//像素值>127的设为255（白），否则设为0（黑）
        findContours(binary,contours,RETR_LIST,CHAIN_APPROX_NONE);//RETR_LIST表示提取所有轮廓且不建立层级关系，CHAIN_APPROX_NONE表示存储轮廓的所有像素点
        for (int i = 0; i < contours.size(); i++) {
            double perimeter = arcLength (contours[i],true);
            double epsilon = epsilonRatio * perimeter;
            double area = contourArea(contours[i]);
            vector<Point> approx;
            approxPolyDP(contours[i],approx,epsilon,true);//多边形逼近



            if(area<1800&&area>150) {
            RotatedRect rotated_rect=minAreaRect(contours[i]);//计算轮廓的最小包围矩形
                Point2f rectPts[4];
                rotated_rect.points(rectPts);//绘制每一条边
                float w=rotated_rect.size.width;
                float h=rotated_rect.size.height;
                float r=max(w,h)/min(w,h);
                cout<<"r="<<r<<endl;
                if (3>r||r>7) continue;//跳过循环的后续代码

                for (int k=0;k<4;k++) {
                allpoints.push_back(rectPts[k]);
            };
            RotatedRect TotalRect=minAreaRect(allpoints);
                Point2f TotalPts[4];
                TotalRect.points(TotalPts);



                for (int j=0;j<4;j++) {
                    line(frame,
                    TotalPts[j],//起点
                    TotalPts[(j+1)%4],//终点
                    Scalar(0, 255, 0), 2);
                }


                // Rect bound = boundingRect(approx);//绘制边界框
                // rectangle(frame,bound,Scalar(0,255,255),2);
            }
        }
    void showResult(); {
            imshow ("Frame",frame);
            imshow ("Binary",binary);
        }
    }
};
#endif
