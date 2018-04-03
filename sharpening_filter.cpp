
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

IplImage* sharpen_filter(IplImage* img)
{
	IplImage* filtered = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);

	int i, j, nIdx, mIdx;
	int mx, my, m_ref; // masking size
	int k; // RGB color sweep
	int pm_int;
	double c; // laplacian scale

	unsigned char pm;

	printf(" Laplacian Sharpening \n");
	printf(" input Laplacian Scale : \n");
	printf(" To make sharper input Minus value \n");
	scanf("%lf", &c);

	zero_padding(filtered, 0);

	for (j = 0; j < filtered->height; j++)
	{
		for (i = 0; i < filtered->width; i++)
		{
			for (k = 0; k < 3; k++)
			{
				nIdx = filtered->widthStep; // y position increment
				mIdx = filtered->nChannels; // x position increment

				int t = 0;

				if (j > 0 && i > 0 && j < filtered->height -1 && i < filtered->width -1) // exception control
				{
					for (my = 0 ; my < 3 ; my++)
					{
						for (mx = 0 ; mx < 3 ; mx++)
						{
							pm = img->imageData[(j + my - 1)*nIdx + (i + mx - 1 )*mIdx + k];
							pm_arr[t] = (int)pm;
							t++;
						}
					}

					double laplacian;
					double fx1y, fx_1y, fxy1, fxy_1, fxy;
					unsigned char tmp;
				
					fx1y = (double)pm_arr[5];
					fx_1y = (double)pm_arr[3];
					fxy1 = (double)pm_arr[7];
					fxy_1 = (double)pm_arr[1];
					fxy = (double)pm_arr[4];

					laplacian = fx1y + fx_1y + fxy1 + fxy_1 - 4 * fxy;

					tmp = (unsigned char)pm_arr[4];

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

	cvNamedWindow("laplacian", CV_WINDOW_AUTOSIZE);
	cvShowImage("laplacian", filtered);
	cvSaveImage("laplacian.bmp", filtered);
	printf("\n Saved Successfully \n\n");

	// display image information
	display_img_info(filtered);

	return filtered;
}