#pragma once
#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\highgui.hpp>
#include<vector>
#include<opencv2\core.hpp>

using namespace cv;
using namespace std;

class LoadImage
{
public:
	LoadImage();
	~LoadImage();


	static int ReadImage(Mat &band1, Mat &band2, Mat &band3, Mat &band4, Mat &result, Mat &result1);

};

