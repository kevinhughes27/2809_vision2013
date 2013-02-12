#include <string>
#include <vector>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


#define MORPH_RECT_WIDTH 5
#define MORPH_RECT_HEIGHT 40
#define TARGET_WIDTH_PIXELS 144
#define TARGET_HEIGHT_PIXELS 33

void segmentTargets(const cv::Mat &image, std::vector<cv::Mat> &candidates, std::vector<cv::Point> &locations, bool debug=false);
bool verifySizes(cv::RotatedRect mr);
cv::Mat histeq(cv::Mat in);