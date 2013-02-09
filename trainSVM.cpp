#include <iostream>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main()
{
    cout << "KBotics Vision System 2013 - SVM Training" << endl;

	const string trainFilePath = "trainFile.txt";
	
    int imageWidth=144;
    int imageHeight=33;     

	Mat trainingData;
    vector<int> trainingLabels;
	
	ifstream trainFile;
    trainFile.open(trainFilePath.c_str(), ifstream::in);
    if(trainFile.is_open())
    {
        string line;
        while(getline(trainFile, line))
        {    
            string t(line.begin(), line.begin() + 1);
            string d(line.begin() + 2,line.end());
            
            trainingLabels.push_back(atoi(t.c_str()));
            
			Mat image = imread(d,0); // load as grayscale
			
			//imshow("image", image);
			//waitKey();
			
			// reshape
			image = image.reshape(1,1);
			
			// convert to CV_32FC1
			image.convertTo(image,CV_32FC1);
			
			trainingData.push_back(image);
        }
    }
    else
    {
        cout << "unable to open file: " << trainFilePath << endl;
    }
    trainFile.close();

	//cout << trainingData.rows << " " << trainingData.cols << endl;
	//cout << trainingLabels.size() << endl;
	
	//Set SVM params
    CvSVMParams SVM_params;
    SVM_params.svm_type = CvSVM::C_SVC;
    SVM_params.kernel_type = CvSVM::LINEAR; //CvSVM::LINEAR;
    SVM_params.degree = 0;
    SVM_params.gamma = 1;
    SVM_params.coef0 = 0;
    SVM_params.C = 1;
    SVM_params.nu = 0;
    SVM_params.p = 0;
    SVM_params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 1000, 0.01);
    
	//Train SVM
    CvSVM svmClassifier(trainingData, Mat(trainingLabels), Mat(), Mat(), SVM_params);
	
	//Save the SVM
	svmClassifier.save("svm.xml");
	
	return 0;
}