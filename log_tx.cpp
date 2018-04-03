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


IplImage* log_tx(IplImage* img)
{
	IplImage* filtered = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);

	int i, j, nIdx, mIdx;
	int k; // RGB color sweep
	int c; // constant for log transformation

	printf(" Log Transformations \n\n");
	printf(" input log scale \n");
	scanf("%d", &c);

	zero_padding(filtered, 0);
	double max = max_of_img(img);
	max = c*log(1 + max);

	for (j = 0; j < filtered->height; j++)
	{
		for (i = 0; i < filtered->width; i++)
		{
			for (k = 0; k < 3; k++)
			{
				nIdx = filtered->widthStep; // y position increment -- transform space
				mIdx = filtered->nChannels; // x position increment

				unsigned char p = img->imageData[j*nIdx + i*mIdx + k];
				double p_double = (double)p;
				double s = c*log(1 + p_double)/max*255;

				//printf(" %lf", s);
				if (s > 255)
					s = 255;
				if (s < 0)
					s = 0;
				unsigned char s_char = (unsigned char)s;
				
				filtered->imageData[j*nIdx + i*mIdx + k] = s_char;
			}
		}
	}

	cvNamedWindow("Log Transformations", CV_WINDOW_AUTOSIZE);
	cvShowImage("Log Transformations", filtered);
	cvSaveImage("log_tx.bmp", filtered);
	printf("\n Saved Successfully \n\n");

	display_img_info(filtered);

	return filtered;
}