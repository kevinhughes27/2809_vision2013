#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "segmentTargets.h"

using namespace cv;
using namespace std;

int main()
{
	// load images
	Mat image = imread("image2.png");

	// segment candidate targets
	vector<Mat> targetCandidates = segmentTargets(image, true);

	// save candidates to hard disk
	if(false)
	{ 
		for(unsigned int i = 0; i < targetCandidates.size(); i++)
		{
			// save as current date time
			stringstream ss(stringstream::in | stringstream::out);
			ss << "unclassified/" << image << "_" << i << ".jpg";
			imwrite(ss.str(), targetCandidates[i]);
		}
	}
	
	// run candidates through the svm
		// requries reshape
		
	// save top target to text file

	return 0;
}