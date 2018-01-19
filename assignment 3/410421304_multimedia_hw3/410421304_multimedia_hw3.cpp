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
	Mat i1in = imread("i1.pgm");
	Mat i2in = imread("i2.pgm");

	Mat i1img,i2img;

	cvtColor(i1in, i1img, CV_BGR2GRAY);
	cvtColor(i2in, i2img, CV_BGR2GRAY);

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
	i2p.create(imgrows,imgcols, CV_8UC3);

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
								tempd = i2img.at<uchar>(j2, i2);
							else
								tempd = i2img.at<uchar>(j2, i2) - i1img.at<uchar>((j2 + jsearch - 7), (i2 + isearch - 7));
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

			for (int i2 = 16 * i; i2 < (16 * (i + 1)); i2++)
			{
				for (int j2 = 16 * j; j2 < (16 * (j + 1)); j2++)
				{
					/*
					Vec3b pix = i2in.at<Vec3b>(Point(j2, i2));
					Vec3b pix2 = i2p.at<Vec3b>(Point(j2, i2));
					pix2 = pix;
					i2p.at<Vec3b>(Point(j2, i2)) = pix;
					*/
					Vec3b pix = i2in.at<Vec3b>(Point(j2, i2));
					Vec3b pix2 = i2in.at<Vec3b>(Point(j2 + currentisearch - 7, i2 + currentisearch - 7));
					Vec3b pix3 = i2p.at<Vec3b>(Point(j2, i2));
					pix3[0] = (pix2[0] + pix[0]) / 2;
					pix3[1] = (pix2[1] + pix[1]) / 2;
					pix3[2] = (pix2[2] + pix[2]) / 2;
					i2p.at<Vec3b>(Point(j2, i2)) = pix3;
					//i2p.at<uchar>(i2, j2) = (i2img.at<uchar>(i2, j2)
					//+ i1img.at<uchar>((i2 + currentisearch - 7), (j2 + currentjsearch - 7))) / 2;
					//i2p.at<uchar>(j2, i2) = i2img.at<uchar>(j2, i2);
					//temp = i2p.at<uchar>(i2, j2);
					//printf("%f ",temp);
					//printf("%d %d,", j2, i2);
				}
			}
			//imshow("i2p by sequntial search", i2p);
		}
	}

	//cvWaitKey(1000);

	//show image

	imshow("target", i1in);
	imshow("reference", i2in);
	for (int i = 0; i < imgrows; i++)
	{
		for (int j = 0; j < imgcols; j++)
		{
			/*
			Vec3b pix = i2in.at<Vec3b>(Point(j, i));
			Vec3b pix2 = i2p.at<Vec3b>(Point(j, i));
			pix2 = pix;
			i2p.at<Vec3b>(Point(j, i)) = pix;
			*/
			/*
			Vec3b pix = i2img.at<Vec3b>(Point(j, i));
			Vec3b pix2 = i2p.at<Vec3b>(Point(j, i));
			pix2 = pix;
			i2p.at<Vec3b>(Point(j, i)) = pix;
			*/
		}
	}
	imshow("i2p by sequntial search", i2p);
	
	cvWaitKey();
}

