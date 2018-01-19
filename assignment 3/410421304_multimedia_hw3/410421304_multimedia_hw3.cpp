// 410421304_multimedia_hw3.cpp: 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv\cxcore.h>
#include <opencv\highgui.h>
#include "math.h"


using namespace cv;
using namespace std;


int main()
{
	Mat i1img = imread("i1.pgm");
	Mat i2img = imread("i2.pgm");

	int imgcols = i1img.cols;
	int imgrows = i1img.rows;
	
	printf("cols:%d\n", imgcols);
	printf("rows:%d\n", imgrows);
	
	float difference = 256 * 16 * 16;
	float smallestdifference = 256 * 16 * 16;

	float tempd = 0;

	int currentisearch;
	int currentjsearch;

	int z = 0;
	float temp;

	//sequntial search

	Mat i2p;
	i2p.create(imgrows,imgcols, CV_8UC1);

	//search window:31*31, macroblock:16*16 => 31-16 = 15, 15/2 = 7
	for (int i = 0; i < imgrows/16; i++)
	{
		for (int j = 0; j < imgcols/16; j++)
		{
			smallestdifference = 256 * 16 * 16;
			for (int isearch = 0; isearch < 31; isearch++)
			{
				for (int jsearch = 0; jsearch < 31; jsearch++)
				{
					difference = 0;
					for (int i2 = 16 * i; i2 <= (16 * (i + 1)); i2++)
					{
						for (int j2 = 16 * j; j2 <= (16 * (j + 1)); j2++)
						{
							if ((((isearch - 7) < 0) || ((jsearch - 7) < 0)) || (((isearch - 7) > imgcols) || ((jsearch - 7) > imgcols)))
								tempd = i2img.at<uchar>(i2, j2);
							else
								tempd = i2img.at<uchar>(i2, j2) - i1img.at<uchar>((i2 + isearch - 7), (j2 + jsearch - 7));
							if (tempd < 0)
								tempd = tempd*(-1);
							difference += tempd;
						}
					}
					if (smallestdifference > difference)
					{
						smallestdifference = difference;
						currentisearch = isearch;
						currentjsearch = jsearch;
					}
				}
			}

			for (int i2 = 16 * i; i2 <= (16 * (i + 1)); i2++)
			{
				for (int j2 = 16 * j; j2 <= (16 * (j + 1)); j2++)
				{
					i2p.at<uchar>(i2, j2) = (i2img.at<uchar>(i2, j2)
						+ i1img.at<uchar>((i2 + currentisearch - 7), (j2 + currentjsearch - 7))) / 2;
					//temp = i2p.at<uchar>(i2, j2);
					//printf("%f ",temp);
				}
			}
			imshow("i2p by sequntial search", i2p);
		}
	}

	cvWaitKey(1000);

	//show image

	//imshow("target", i1img);
	//imshow("reference", i2img);
	//imshow("i2p by sequntial search", i2p);
	
	cvWaitKey();
}

