
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
IplImage* midpoint_filter(IplImage* img)
{
	IplImage* filtered = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);

	zero_padding(filtered, 255);

	int i, j, nIdx, mIdx;
	int mx, my, m_ref; // masking size
	int k; // RGB color sweep
	unsigned char pm;
	unsigned int pm_int;
	double pm_double;

	//int pm_arr[9] = { 0,0,0,0,0,0,0,0,0 };

	printf(" midpoint filter \n\n");

	m_ref = 3;



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
				int t = 0; // array control 

				if (j > m_ref / 2 && i > m_ref / 2 && j < img->height - m_ref / 2 && i < img->width - m_ref / 2)
				{
					for (mx = (-m_ref / 2); mx < (m_ref / 2) + 1; mx++)
					{
						for (my = (-m_ref / 2); my < (m_ref / 2) + 1; my++)
						{
							pm = img->imageData[(j + my)*nIdx + (i + mx)*mIdx + k];
							//printf(" %d ", t);
							pm_arr[t] = pm;
							t++;

						}
					}
					bubble_sort(pm_arr);

					pm_int = (pm_arr[0]+pm_arr[8])/2;

					pm = (unsigned char)pm_int;
					filtered->imageData[j*nIdx + i*mIdx + k] = pm;
				}
			}
		}
	}

	cvNamedWindow("midpoint_filtered", CV_WINDOW_AUTOSIZE);
	cvShowImage("midpoint_filtered", filtered);
	cvSaveImage("midpoint_filtered.bmp", filtered);
	printf("\n Saved Successfully \n\n");

	// display image information
	display_img_info(filtered);

	return filtered;
}