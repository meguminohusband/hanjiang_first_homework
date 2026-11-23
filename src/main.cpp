#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
void task1() {
    cv::Mat img = cv::imread("2.png");

    cv::Mat hsv;
    cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);

    cv::Mat blueMask, redMask1, redMask2, redMask;
    cv::inRange(hsv, cv::Scalar(90, 120, 120),cv::Scalar(130, 255, 255),blueMask);

    cv::inRange(hsv, cv::Scalar(0, 120, 80), cv::Scalar(15, 255, 255), redMask1);
    cv::inRange(hsv, cv::Scalar(165, 120, 80), cv::Scalar(179, 255, 255),redMask2);
    cv::bitwise_or(redMask1, redMask2, redMask);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(blueMask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    for(std::size_t i = 0;i < contours.size();i++) {
        if(cv::contourArea(contours[i]) < 100) continue;
        cv::RotatedRect rect = cv::minAreaRect(contours[i]);
        cv::Point2f p[4];
        rect.points(p);
        for(int j = 0;j < 4;j++) {
            cv::line(img, p[j], p[(j + 1) % 4], cv::Scalar(0, 255, 255), 2);
        }
    }

    contours.clear();
    cv::findContours(redMask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    for(std::size_t i = 0;i < contours.size();i++) {
        if(cv::contourArea(contours[i]) < 100) continue;
        cv::RotatedRect rect = cv::minAreaRect(contours[i]);
        cv::Point2f p[4];
        rect.points(p);
        for(int j = 0;j < 4;j++) {
            cv::line(img, p[j], p[(j + 1) % 4], cv::Scalar(0, 255, 0), 2);
        }
    }

    cv::imwrite("result1.png", img);
}

void task2() {
    cv::Mat img = cv::imread("3.jpg");

    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    cv::Mat mask;
    cv::threshold(gray, mask, 160, 255, cv::THRESH_BINARY);
    
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for(std::size_t i = 0;i < contours.size();i++) {
        cv::RotatedRect rect2 = cv::minAreaRect(contours[i]);
        cv::Rect r = cv::boundingRect(contours[i]);
        double aspect = (double)r.width / r.height;
        cv::Point2f p[4];
        rect2.points(p);
        if (r.height > 30 && aspect < 0.6) {
            for(int j = 0;j < 4;j++) {
                cv::line(img, p[j], p[(j + 1) % 4], cv::Scalar(0, 255, 0), 2);
            }
        }
    }

    cv::imwrite("result2.png", img);
}

int main() {
    task1();
    task2();
    return 0;
}
