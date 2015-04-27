#include "segmentTargets.h"

using namespace cv;
using namespace std;

void segmentTargets(const Mat &image, vector<Mat> &candidates, vector<Point> &locations, bool log, bool debug)
{
	candidates.clear();
	locations.clear();

	if(log)
	{
		imwrite("logs/0_image.png", image);
	}

	// Convert to CV_8UC1 (8 bit single channel)
	// split channels
	vector<Mat> channels;
	split(image, channels);

	// Blur
	Mat img_gray;
	blur(channels[2], img_gray, Size(5,5));

	if(debug)
	{
		imshow("image", img_gray);
		waitKey();
	}

	if(log)
	{
		imwrite("logs/1_image_gray.png", img_gray);
	}

	// Sobel Filter
	Mat img_sobely;
	Sobel(img_gray, img_sobely, CV_8U, 0, 1, 3, 1, 0, BORDER_DEFAULT);

	Mat img_threshold;
	threshold(img_sobely, img_threshold, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);

	if(debug)
	{
		imshow("image", img_threshold);
		waitKey();
	}

	if(log)
	{
		imwrite("logs/2_sobel.png", img_threshold);
	}

	// Morphological Operator
	Mat img_rectangle;
	Mat element = getStructuringElement(MORPH_RECT, Size(MORPH_RECT_WIDTH, MORPH_RECT_HEIGHT) );
	morphologyEx(img_threshold, img_rectangle, CV_MOP_CLOSE, element);

	Mat img_dilate;
	dilate(img_rectangle, img_dilate, Mat(), Point(-1,-1), 5);

	Mat img_erode;
	erode(img_dilate, img_erode, Mat(), Point(-1,-1), 6);

	if(debug)
	{
		imshow("image", img_erode);
		waitKey();
	}

	if(log)
	{
		imwrite("logs/3_morpho.png", img_erode);
	}

	// findContours
	vector< vector< Point> > contours;
	findContours(img_erode,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);

	vector<vector<Point> >::iterator itc = contours.begin();
	vector<RotatedRect> rects;

	// filter by contour size
	while (itc!=contours.end()) {

		//Create bounding rect of object
		RotatedRect mr = minAreaRect(Mat(*itc));

		if( !verifySizes(mr))
		{
			itc= contours.erase(itc);
		}
		else
		{
			++itc;
			rects.push_back(mr);
		}
	}

	if(debug)
	{
		// Draw blue contours on a black image
		cv::Mat result = cv::Mat::zeros(image.size(),image.type());
		cv::drawContours(result,contours, -1, cv::Scalar(255,0,0),1);

		imshow("image", result);
		waitKey();
	}

	if(log)
	{
		// Draw blue contours on a black image
		cv::Mat result = cv::Mat::zeros(image.size(),image.type());
		cv::drawContours(result,contours, -1, cv::Scalar(255,0,0),1);

		imwrite("logs/4_contours.png", result);
	}

	// transform the segmented regions
	for(unsigned int i = 0; i < rects.size(); i++)
	{
		// rotated rectangle drawing
		Point2f rect_points[4];
		rects[i].points( rect_points );

		if(debug)
		{
			cv::Mat result = cv::Mat::zeros(image.size(),image.type());
			for( int j = 0; j < 4; j++ )
			{
				line( result, rect_points[j], rect_points[(j+1)%4], Scalar(0,0,255), 1, 8 );
			}

			imshow("image", result);
			waitKey();
		}

		// Get rotation matrix
		float r= (float)rects[i].size.width / (float)rects[i].size.height;
		float angle=rects[i].angle;
		if(r<1)
			angle=90+angle;
		Mat rotmat= getRotationMatrix2D(rects[i].center, angle,1);

		// Create and rotate image
		Mat img_rotated;
		warpAffine(image, img_rotated, rotmat, image.size(), CV_INTER_CUBIC);

		// Crop image
		Size rect_size=rects[i].size;
		if(r < 1)
			swap(rect_size.width, rect_size.height);
		Mat img_crop;
		getRectSubPix(img_rotated, rect_size, rects[i].center, img_crop);

		// resize
		Mat resultResized;
		resultResized.create(TARGET_HEIGHT_PIXELS,TARGET_WIDTH_PIXELS, CV_8UC3);
		resize(img_crop, resultResized, resultResized.size(), 0, 0, INTER_CUBIC);

		//Equalize croped image
		resultResized=histeq(resultResized);

		if(debug)
		{
			imshow("image", resultResized);
			waitKey();
		}

		// add target
		candidates.push_back(resultResized.clone());
		locations.push_back(rects[i].center);
	}

	return;
}

bool verifySizes(RotatedRect mr)
{
	//target: 120x40 aspect 3
	float error=0.4;
	float aspect = 3;

	//Set a min and max area. All other patchs are discarded
	int min = 15*aspect*15; // minimum area
	int max = 80*aspect*80; // maximum area

	//Get only patchs that match to a respect ratio.
	float rmin = aspect-aspect*error;
	float rmax = aspect+aspect*error;

	int area= mr.size.height * mr.size.width;
	float r = (float)mr.size.width / (float)mr.size.height;
	if(r<1)
		r= (float)mr.size.height / (float)mr.size.width;

	//cout << "area " << area << " r " << r << endl;

	if(( area < min || area > max ) || ( r < rmin || r > rmax ))
	{
		return false;
	}
	else
	{
		return true;
	}
}

Mat histeq(Mat in)
{
	Mat out(in.size(), in.type());
	if(in.channels()==3)
	{
		Mat hsv;
		vector<Mat> hsvSplit;
		cvtColor(in, hsv, CV_BGR2HSV);
		split(hsv, hsvSplit);
		equalizeHist(hsvSplit[2], hsvSplit[2]);
		merge(hsvSplit, hsv);
		cvtColor(hsv, out, CV_HSV2BGR);
	}
	else if(in.channels()==1)
	{
		equalizeHist(in, out);
	}

		return out;
}
