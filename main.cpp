// RoadDetect.cpp: 定义控制台应用程序的入口点。
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
	/*打开建筑物道路遥感影像，并转化为灰度图*/
	Mat band1, band2, band3, band4, result, result1;
	LoadImage::ReadImage(band1,band2,band3,band4,result,result1);
	/*进行道路检测*/
	RoadDetect::RoadExtraction(band1, band2, band3, band4, result, result1);

	return 0;
}

