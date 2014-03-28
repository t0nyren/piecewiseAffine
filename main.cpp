#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
#include "imgwarp_piecewiseaffine.h"
using namespace std;
using namespace cv;

#define numLandmarks 83

int main(){
	ifstream finSrc, finDst;
	//read in dst img
	Mat src = imread("pitch.jpg", 1);
	Rect rect(0, 0, src.cols, src.rows);
    Subdiv2D subdiv(rect);	
	
	//parse landmarks
	finSrc.open("pitchLandmarks.txt");
	finDst.open("baseLandmarks.txt");
	if (finSrc.fail() || finDst.fail()){
		cout<<"Couldn't open landmarks files"<<endl;
	}
	vector<Point_<int> > srcPoints;
	vector<Point_<int> > dstPoints;
	for (int i = 0; i < numLandmarks; i++){
		float x,y;
		finSrc>>x;
		finSrc>>y;
		srcPoints.push_back(Point_<int>( cvRound(x/100*src.cols),cvRound(y/100*src.rows) ));
		finDst>>x;
		finDst>>y;
		dstPoints.push_back(Point_<int>( cvRound(x/100*src.cols),cvRound(y/100*src.rows) ));
	}
	
	//piecewise affine
	ImgWarp_PieceWiseAffine warpper;
	warpper.backGroundFillAlg = ImgWarp_PieceWiseAffine::BGMLS;
	Mat warpDst = warpper.setAllAndGenerate(src, srcPoints, dstPoints, src.cols, src.rows, 1);
	imwrite("affine.jpg", warpDst);
	return 0;
}