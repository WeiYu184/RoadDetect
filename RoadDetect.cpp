#include "RoadDetect.h"



RoadDetect::RoadDetect()
{
}


RoadDetect::~RoadDetect()
{
}

void RoadDetect::RoadExtraction(Mat band1, Mat band2, Mat band3, Mat band4, Mat result, Mat result1)
{
	/*����ָ�룬�����洢������Ӱ������*/
	uchar* pBand1 = band1.data;
	uchar* pBand2 = band2.data;
	uchar* pBand3 = band3.data;
	uchar* pBand4 = band4.data;
	uchar* pImg = result1.data;

	/*��ȡӰ��ߴ�*/
	int rows = band1.rows;
	int cols = band1.cols;

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	/* Step 1��������ȡ��·���򣺸������Ⱥ�NDVIֵ�˳��ǵ�·��Ԫ*/
	/* ����ң��Ӱ���е�·������ֵ����ֲ����ˮ�壬�ɲ��õ������˳��ķ�������Ԥ��������ɸѡ����·�Ĵ��·�Χ��
	/*���ڵ�·��NDVIֵΪ0�������ɸ��ݴ���������ɸѡ����һ���˳��ǵ�·��Ԫ��
	/*���ʹ����̬ѧ�еĿ�������Խ��ͼ����д���*/
	Mat img_light(rows, cols, CV_8UC1);
	uchar* pImg_light = img_light.data;
	double* NDVI = new double[rows*cols];

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			// ����EDVIֵ
			NDVI[i*cols + j] = (pBand1[i*cols + j] - pBand4[i*cols + j]) / (pBand1[i*cols + j] + pBand4[i*cols + j]);

			// �˳�����ֵ��49���µ���Ԫ
			if (pBand1[i*cols + j] <= 49)
				pImg_light[i*cols + j] = 0;
			// �˳�NDVI����0��С��-0.1����Ԫ
			else if (NDVI[i*cols + j] > 0 && NDVI[i*cols + j] < -0.1)
				pImg_light[i*cols + j] = 0;
			else
				pImg_light[i*cols + j] = pImg[i*cols + j];
		}
	}

	/*��̬ѧ�����㡢��ʴ������*/
	Mat element1(4, 4, CV_8U, Scalar(1));
	//dilate(img_light, img_light, Mat());
	morphologyEx(img_light, img_light, MORPH_CLOSE, element1);

	Mat element2(2, 2, CV_8U, Scalar(1));
	dilate(img_light, img_light, element2);

	Mat element3(6, 6, CV_8U, Scalar(1));
	morphologyEx(img_light, img_light, MORPH_OPEN, element3);




    //////////////////////////////////////////////////////////////////////////////////////////////////////
	/* Step 2����·������ȡ����ȡ������������״ָ��*/
	/* ���㷨���õ���״ָ��Ϊ���S����״ָ��C��*/
	/* ���ݵ�·����״ָ�������������������ֵ���ɶԸղŵõ��ĵ�·������и���ȷ��ɸѡ��*/

	// ��ͼ����ж�ֵ������ֵΪ49
	Mat img_bin, img_gray;
	threshold(img_light, img_gray, 49.0, 200.0, THRESH_OTSU);
	namedWindow("��ֵ��", 0);
	imshow("��ֵ��", img_gray);

	//������ȡ
	vector<vector<cv::Point>> contours;
	findContours(img_gray, contours, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	for (int i = 0; i < (int)contours.size(); i++)
	{
		// �������S
		double S = contourArea((Mat)contours[i]);
		if (S > 0 && S < 417728)
		{
			//������״ָ��C
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
