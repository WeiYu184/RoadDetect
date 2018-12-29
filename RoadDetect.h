#pragma once
#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\highgui.hpp>
#include<vector>
#include<opencv2\core.hpp>
#include"LoadImage.h"

using namespace cv;
using namespace std;

class RoadDetect
{
public:
	RoadDetect();
	~RoadDetect();

	static void RoadExtraction(Mat band1, Mat band2, Mat band3, Mat band4, Mat result, Mat result1);
};

