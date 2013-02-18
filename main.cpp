#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "segmentTargets.h"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	Mat image;
	
	// load images
	if(argc == 1)
		image = imread("image.png");
	else
	{
		cout << argv[0] << " " << argv[1] << endl; 
		image = imread(argv[1]);
	}
	
	// segment candidate targets
	vector<Mat> targetCandidates;
	vector<Point> candidateLocations;
	
	segmentTargets(image, targetCandidates, candidateLocations, true, false);

	// save candidates to hard disk
	if(false)
	{ 
		for(unsigned int i = 0; i < targetCandidates.size(); i++)
		{
			// save as current date time
			time_t t = time(0);
			stringstream ss;
			ss << "unclassified/" << "image" << "_" << t << i << ".jpg";
			//cout << ss.str() << endl;
			imwrite(ss.str(), targetCandidates[i]);
		}
	}
	
	// Run SVM
	if(argc < 2)
	{
		// classify with SVM
		CvSVM *svmClassifier = new CvSVM();
		svmClassifier->load("svm.xml");
		
		vector<Mat>::iterator it = targetCandidates.begin();
		vector<Point>::iterator loc_it = candidateLocations.begin();
		vector<Mat> targets;
		vector<Point> locations;
		
		while (it!=targetCandidates.end()) 
		{
			Mat sample = Mat(*it);
			Point loc = Point(*loc_it);
			Mat sampleVec = sample.reshape(1,1).clone();
			sampleVec.convertTo(sampleVec,CV_32FC1);
			
			if( (int)svmClassifier->predict(sampleVec) == 0 )
			{
				it = targetCandidates.erase(it);
				loc_it = candidateLocations.erase(loc_it);
			}
			else if ( (int)svmClassifier->predict(sampleVec) == 1 )
			{
				++it;
				++loc_it;
				targets.push_back(sample);
				locations.push_back(loc);
			}
		}	
		
		bool targetFound = locations.size() > 0;
		
		Point bestTarget(image.cols, image.rows);
		for(unsigned int i = 0; i < locations.size(); i++)
		{
			if(locations[i].y < bestTarget.y)
				bestTarget = locations[i];
		}
		
		// save top target to text file
		ofstream f;
		f.open ("target.txt");
		f << targetFound << endl << bestTarget.x << endl << bestTarget.y << endl;
		f.close();
		
		if(bestTarget.y != image.rows)
			return 0;
	}
	return 1;
}