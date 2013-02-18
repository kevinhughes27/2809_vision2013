#include <string>
#include <vector>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define MORPH_RECT_WIDTH 5
#define MORPH_RECT_HEIGHT 50
#define TARGET_WIDTH_PIXELS 120
#define TARGET_HEIGHT_PIXELS 40

void segmentTargets(const cv::Mat &image, std::vector<cv::Mat> &candidates, std::vector<cv::Point> &locations, bool log=false, bool debug=false);
bool verifySizes(cv::RotatedRect mr);
cv::Mat histeq(cv::Mat in);