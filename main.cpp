// RoadDetect.cpp: �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\highgui.hpp>
#include<vector>
#include<opencv2\core.hpp>
#include"LoadImage.h"
#include"RoadDetect.h"

using namespace cv;
using namespace std;

int main()
{
	/*�򿪽������·ң��Ӱ�񣬲�ת��Ϊ�Ҷ�ͼ*/
	Mat band1, band2, band3, band4, result, result1;
	LoadImage::ReadImage(band1,band2,band3,band4,result,result1);
	/*���е�·���*/
	RoadDetect::RoadExtraction(band1, band2, band3, band4, result, result1);

	return 0;
}

