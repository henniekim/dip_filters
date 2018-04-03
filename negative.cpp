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


IplImage* negative(IplImage* img)
{
	IplImage* filtered = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);

	int i, j, nIdx, mIdx;
	int k; // RGB color sweep

	printf(" Negative Filter \n\n");

	double min = (double)min_of_img(img);
	double max = (double)max_of_img(img);

	printf(" Maximum of the image : %d", (unsigned char)max);
	printf(" minimum of the image : %d", (unsigned char)min);

	for (j = 0; j < filtered->height; j++)
	{
		for (i = 0; i < filtered->width; i++)
		{
			for (k = 0; k < 3; k++)
			{
				nIdx = filtered->widthStep; // y position increment -- transform space
				mIdx = filtered->nChannels; // x position increment

				double p = max - (double)img->imageData[j*nIdx + i*mIdx + k];
				p = p / max * 255; 
				filtered->imageData[j*nIdx + i*mIdx + k] = (unsigned char)p;
			}
		}
	}

	cvNamedWindow("negative", CV_WINDOW_AUTOSIZE);
	cvShowImage("negative", filtered);
	cvSaveImage("negative.bmp", filtered);
	printf("\n Saved Successfully \n\n");

	display_img_info(filtered);

	return filtered;
}