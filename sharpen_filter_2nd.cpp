
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>
#include "function_list.h"

static int pm_arr[9] = { 0,0,0,0,0,0,0,0,0 };

IplImage* sharpen_filter_2nd(IplImage* img)
{
	IplImage* filtered = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);

	zero_padding(filtered, 0);

	int i, j, nIdx, mIdx;
	int mx, my, m_ref; // masking size
	int k; // RGB color sweep
	int pm_int;
	int c; // laplacian scale

	unsigned char pm;

	double pm_double;

	printf(" Laplacian Sharpening 2 \n");
	printf(" input Laplacian Scale : \n");
	printf(" To make sharper input Minus value \n");
	scanf("%d", &c);

	m_ref = 3;
	mx = 3;
	my = 3;

	for (j = 0; j < filtered->height; j++)
	{
		for (i = 0; i < filtered->width; i++)
		{
			for (k = 0; k < 3; k++)
			{
				nIdx = filtered->widthStep; // y position increment -- transform space
				mIdx = filtered->nChannels; // x position increment

				pm = 0;
				pm_double = 0;
				int t = 0;
				if (j > 0 && i > 0 && j < filtered->height - 1 && i < filtered->width - 1)
				{
					for (my = 0; my < 3 ; my++)
					{
						for (mx = 0; mx < 3 ; mx++)
						{
							pm = img->imageData[(j + my-1)*nIdx + (i + mx-1)*mIdx + k];
							pm_arr[t] = pm;
							t++;
						}
					}

					double laplacian;
					double fx1y, fx_1y, fxy1, fxy_1, fxy;
					double fx_1y_1, fx1y_1, fx_1y1, fx1y1;
					unsigned char tmp;

					fx_1y_1 = pm_arr[0];
					fxy_1 = pm_arr[1];
					fx1y_1 = pm_arr[2];

					fx_1y = pm_arr[3];
					fxy = pm_arr[4];
					fx1y = pm_arr[5];
					
					fx_1y1 = pm_arr[6];
					fxy1 = pm_arr[7];
					fx1y1 = pm_arr[8];
					
					laplacian = fx1y + fx_1y + fxy1 + fx_1y_1 + fx1y_1 + fx_1y1 + fx1y1 + fxy_1 - 8 * fxy;

					tmp = fxy;
					pm_int = (int)tmp + (int)(c*laplacian);

					if (pm_int < 0)
						pm_int = 0;
					if (pm_int > 255)
						pm_int = 255;

					pm = (unsigned char)pm_int;

					filtered->imageData[j*nIdx + i*mIdx + k] = pm;
				}
			}
		}
	}

	cvNamedWindow("laplacian2", CV_WINDOW_AUTOSIZE);
	cvShowImage("laplacian2", filtered);
	cvSaveImage("laplacian2.bmp", filtered);
	printf("\n Saved Successfully \n\n");

	// display image information
	display_img_info(filtered);

	return filtered;
}