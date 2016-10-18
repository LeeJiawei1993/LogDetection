#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

#define pi 3.1415926

double Gaus(float x,float y,float sigma=1){
	double e=exp((-(x*x+y*y)/(2*sigma*sigma)));
	return e;
}

Mat_<float> GaussianKerGenerate(){
	Mat_<float> ker=Mat::zeros(5,5,CV_32FC1);
	int j,k;
	for(j=0;j<5;j++){
		for(k=0;k<5;k++){
			ker.at<float>(j,k)=Gaus(j-2,k-2,1);
		}
	}
	return ker;
} 

Mat_<float> getLOG(int i,float sigma=1){
	Mat_<float> LOG=Mat::zeros(i,i,CV_32FC1);
	int j,k;
	int l=i/2;
	for (j=0;j<i;j++){
		for(k=0;k<i;k++){
			LOG.at<float>(j,k)=Gaus(j-l,k-l,1)*(((j-l)*(j-l)+(k-l)*(k-l))/(sigma*sigma)-2)/(2*pi*sigma*sigma*sigma*sigma);
		}
	}
	return LOG;
}


void darw(Mat& src,Mat& ssrc){
	int nr=src.rows;
	int nc=src.cols;
	int i=0,j=0;
	for(i=0;i<nr;i++){
		for (j=0;j<nc;j++){
			if(src.at<uchar>(i,j)>0)
				circle(ssrc,Point(i,j),5,255);
		}
	}
}

int main(){
	Mat img=imread("lena.jpg",0);
	Mat img1,img2,img3;
//	Mat ker=GaussianKerGenerate();
	Mat ker=getLOG(5);
	GaussianBlur(img,img1,Size(3,3),1);
//	Laplacian(img,img1,CV_8UC1,3,1,0);
	filter2D(img1,img2,-1,ker);
	threshold(img2,img2,5,255,0);
	//cout<<img2<<endl;
	darw(img2,img);
	imshow("1",img);
	imshow("2",img2);
	waitKey(0);
	return 0;
}
