
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include "function_list.h"

static int* arr;


IplImage* alpha_trimmed_mean_filter(IplImage* img)
{
	IplImage* filtered = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);

	int i, j, nIdx, mIdx;
	int mx, my, m_ref_x, m_ref_y; // masking size
	int k; // RGB color sweep
	int trim; // d parameter
	int t; // array sweep
	unsigned char pm;
	unsigned int pm_int;
	double pm_double;

	printf(" Alpha-trimmed Mean Filter \n");
	printf(" Input Mask Size of x : \n");
	scanf("%d", &m_ref_x);
	printf(" Input Mask Size of y : \n");
	scanf("%d", &m_ref_y);
	printf(" Input Trim Size d : \n");
	printf(" when d = 0 : arithmetic filter \n");
	printf(" when d = mn -1 : median filter \n");
	printf(" It is useful for multiple types of noise,\n such as a combination of salt & pepper and gaussian noise. \n");
	scanf("%d", &trim);

	mx = m_ref_x;
	my = m_ref_y;

	int msize = mx*my;
	
	printf("\n-----------------------------\n");
	printf(" Mask Size is %d * %d = %d \n", mx, my, msize);
	printf(" Trim size is  : %d \n", trim);
	printf(" -----------------------------\n\n");

	arr = (int*)malloc(sizeof(int)*mx*my);

	zero_padding(filtered, 255);

	for (j = 0; j < filtered->height; j++)
	{
		for (i = 0; i < filtered->width; i++)
		{
			for (k = 0; k < 3; k++)
			{
				nIdx = filtered->widthStep; // y position increment -- transform space
				mIdx = filtered->nChannels; // x position increment

				t = 0;
				
				if (j >= m_ref_y / 2 && i >= m_ref_x / 2 && j <= img->height - m_ref_y / 2 + 1 && i <= img->width - m_ref_x / 2 + 1)
				{
					for (mx = (- m_ref_x / 2); mx < (m_ref_x / 2) + 1; mx++)
					{
						for (my = (-m_ref_y / 2); my < (m_ref_y / 2) + 1; my++)
						{
							pm = img->imageData[(j + my)*nIdx + (i + mx)*mIdx + k];
							*(arr + t) = (int)pm;
							t++;
							if (t == msize)
								break;
						}
					}
					
					arr  = bubble_sort_dynamic(msize, arr);

					int s = 0; // for trim 
					pm_int = 0;

					for (s >= trim; s < msize - trim; s++)
					{
						pm_int += *(arr + 0 + s);
					}
					pm = (unsigned char)( pm_int / (msize - trim));
					filtered->imageData[j*nIdx + i*mIdx + k] = pm;
				}
			}
		}
	}

	cvNamedWindow("alpha_trimmed", CV_WINDOW_AUTOSIZE);
	cvShowImage("alpha_trimmed", filtered);
	cvSaveImage("alpha_trimmed.bmp", filtered);
	printf("\n Saved Successfully \n\n");

	// display image information
	display_img_info(filtered);

	return filtered;
}