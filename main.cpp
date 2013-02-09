#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "segmentTargets.h"

using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("image2.png");
	
	vector<Mat> targetCandidates = segmentTargets(image, true);
	
	if(false)
	{ 
		for(unsigned int i = 0; i < targetCandidates.size(); i++)
		{
			stringstream ss(stringstream::in | stringstream::out);
			ss << "tmp/" << image << "_" << i << ".jpg";
			imwrite(ss.str(), targetCandidates[i]);
		}
	}

	return 0;
}