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

IplImage*sobel(IplImage* img)
{
	IplImage* filtered = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);

	int i, j, nIdx, mIdx;
	int mx, my, m_ref; // masking size
	int k; // RGB color sweep
	unsigned char pm;
	int pm_int;
	double pm_double;
	int c; // laplacian scale

	printf(" Laplacian Sharpening \n");
	printf(" input Laplacian Scale : \n");
	scanf("%d", &c);

	m_ref = 3;
	mx = 3;
	my = 3;

	zero_padding(filtered, 255);

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
					for (my = 0; my < 3; my++)
					{
						for (mx = 0; mx < 3; mx++)
						{

							pm = img->imageData[(j + my -1)*nIdx + (i + mx -1)*mIdx + k];
							pm_arr[t] = pm;
							t++;
						}
					}

					double laplacian;
					double fxy1, fxy2, fxy3, fxy4, fxy5, fxy6, fxy7, fxy8, fxy9;
					unsigned char tmp;

					fxy1 = pm_arr[0];
					fxy2 = pm_arr[1];
					fxy3 = pm_arr[2];

					fxy4 = pm_arr[3];
					fxy5 = pm_arr[4];
					fxy6 = pm_arr[5];

					fxy7 = pm_arr[6];
					fxy8 = pm_arr[7];
					fxy9 = pm_arr[8];

					laplacian = abs((fxy7 + 2 * fxy8 + fxy9) - (fxy1 + 2 * fxy2 + fxy3)) + abs((fxy3 + 2 * fxy6 + fxy9) - (fxy1 + 2 * fxy4 + fxy7));

					pm_int = (c*laplacian);

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

	cvNamedWindow("sobel", CV_WINDOW_AUTOSIZE);
	cvShowImage("sobel", filtered);
	cvSaveImage("sobel.bmp", filtered);
	printf("\n Saved Successfully \n\n");

	// display image information
	display_img_info(filtered);

	return filtered;
}