#include <string>
#include <vector>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

std::vector<cv::Mat> segmentTargets(const cv::Mat &image, bool debug=false);
bool verifySizes(cv::RotatedRect mr);
cv::Mat histeq(cv::Mat in);