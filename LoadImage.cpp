#include "LoadImage.h"
#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\highgui.hpp>
#include<vector>
#include<opencv2\core.hpp>



LoadImage::LoadImage()
{
}


LoadImage::~LoadImage()
{
}

int LoadImage::ReadImage(Mat &band1, Mat &band2, Mat &band3, Mat &band4, Mat &result, Mat &result1)
{
	/*打开建筑物道路遥感影像*/
	band1 = imread("zy3-1.tif", 0);
	band2 = imread("zy3-2.tif", 0);
	band3 = imread("zy3-3.tif", 0);
	band4 = imread("zy3-4.tif", 0);
	result = imread("zy3.bmp");
	result1;

	/*将影像转为灰度图*/
	cvtColor(result, result1, COLOR_RGB2GRAY);
	return 1;
}