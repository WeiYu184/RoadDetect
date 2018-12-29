#include "RoadDetect.h"



RoadDetect::RoadDetect()
{
}


RoadDetect::~RoadDetect()
{
}

void RoadDetect::RoadExtraction(Mat band1, Mat band2, Mat band3, Mat band4, Mat result, Mat result1)
{
	/*定义指针，用来存储各波段影像数据*/
	uchar* pBand1 = band1.data;
	uchar* pBand2 = band2.data;
	uchar* pBand3 = band3.data;
	uchar* pBand4 = band4.data;
	uchar* pImg = result1.data;

	/*获取影像尺寸*/
	int rows = band1.rows;
	int cols = band1.cols;

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	/* Step 1：初步提取道路区域：根据亮度和NDVI值滤除非道路像元*/
	/* 由于遥感影像中道路的亮度值高于植被和水体，可采用低亮度滤除的方法进行预处理，初步筛选出道路的大致范围。
	/*由于道路的NDVI值为0或负数，可根据此条件再作筛选，进一步滤除非道路像元。
	/*最后，使用形态学中的开闭运算对结果图像进行处理。*/
	Mat img_light(rows, cols, CV_8UC1);
	uchar* pImg_light = img_light.data;
	double* NDVI = new double[rows*cols];

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			// 计算EDVI值
			NDVI[i*cols + j] = (pBand1[i*cols + j] - pBand4[i*cols + j]) / (pBand1[i*cols + j] + pBand4[i*cols + j]);

			// 滤除亮度值在49以下的像元
			if (pBand1[i*cols + j] <= 49)
				pImg_light[i*cols + j] = 0;
			// 滤除NDVI大于0且小于-0.1的像元
			else if (NDVI[i*cols + j] > 0 && NDVI[i*cols + j] < -0.1)
				pImg_light[i*cols + j] = 0;
			else
				pImg_light[i*cols + j] = pImg[i*cols + j];
		}
	}

	/*形态学闭运算、腐蚀、膨胀*/
	Mat element1(4, 4, CV_8U, Scalar(1));
	//dilate(img_light, img_light, Mat());
	morphologyEx(img_light, img_light, MORPH_CLOSE, element1);

	Mat element2(2, 2, CV_8U, Scalar(1));
	dilate(img_light, img_light, element2);

	Mat element3(6, 6, CV_8U, Scalar(1));
	morphologyEx(img_light, img_light, MORPH_OPEN, element3);




    //////////////////////////////////////////////////////////////////////////////////////////////////////
	/* Step 2：道路区域提取：提取轮廓并计算形状指数*/
	/* 本算法采用的形状指数为面积S和形状指数C。*/
	/* 根据道路的形状指数和面积特征，设置阈值，可对刚才得到的道路区域进行更精确地筛选。*/

	// 对图像进行二值化，阈值为49
	Mat img_bin, img_gray;
	threshold(img_light, img_gray, 49.0, 200.0, THRESH_OTSU);
	namedWindow("二值化", 0);
	imshow("二值化", img_gray);

	//轮廓提取
	vector<vector<cv::Point>> contours;
	findContours(img_gray, contours, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	for (int i = 0; i < (int)contours.size(); i++)
	{
		// 计算面积S
		double S = contourArea((Mat)contours[i]);
		if (S > 0 && S < 417728)
		{
			//计算形状指数C
			double C = contours[i].size() * contours[i].size() / (4 * 3.1415*S);
			if (C > 4)
			{
				drawContours(result, contours, i, Scalar(255), 5);
			}
		}
	}


	namedWindow("pImg_light2", 0);
	imshow("pImg_light2", result);
	imwrite("result.jpg", result);
	waitKey(0);
}
