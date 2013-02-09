#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "segmentTargets.h"

using namespace cv;
using namespace std;

int main()
{
	// load images
	Mat image = imread("image.png");

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
	
	// classify with SVM
	CvSVM *svmClassifier = new CvSVM();
	svmClassifier->load("svm.xml");
	
	vector<Mat>::iterator it = targetCandidates.begin();
    vector<Mat> targets;
	
	while (it!=targetCandidates.end()) 
	{
		Mat sample = Mat(*it);
		Mat sampleVec = sample.reshape(1,1).clone();
		sampleVec.convertTo(sampleVec,CV_32FC1);
		
		if( (int)svmClassifier->predict(sample) == 0 )
		{
            it = targetCandidates.erase(it);
        }
		else if ( (int)svmClassifier->predict(sample) == 1 )
		{
            ++it;
            targets.push_back(sample);
        }
    }	
		
	// save top target to text file
	// whoa I need to go back and return the locations from segment
	
	return 0;
}