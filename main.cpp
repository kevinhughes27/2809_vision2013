#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main()
{
	// File IO test
	ofstream myfile;
	myfile.open ("example.txt");
	myfile << "Writing this to a file.\n";
	myfile.close();
	
	// OpenCV test
	Mat image = imread("../image.png");
	imshow("image", image);
	waitKey();
	
	return 0;
}