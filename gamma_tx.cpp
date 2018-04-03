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


IplImage* gamma_tx(IplImage* img)
{
	IplImage* filtered = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);

	int i, j, nIdx, mIdx;
	int k; // RGB color sweep
	double c; // constant for log transformation
	double g; // gamma constant 

	printf(" Power-Law (Gamma) Transformations \n\n");
	printf(" input scaling constant \n");
	scanf("%lf", &c);
	printf(" input gamma constant\n");
	scanf("%lf", &g);

	unsigned char max = max_of_img(img);
	printf(" maximum intensity of the image is %d", max);
	double s_max = c*pow(max, g);
	printf(" maximum intensity of the image is %lf ", s_max);
	printf(" need scale\n");

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
				double s = c*pow(p_double, g);
			
				s = s / s_max * 255;

				if (s < 0)
					s = 0;

				//printf(" %lf", s);
				unsigned char s_char = (unsigned char)s;

				filtered->imageData[j*nIdx + i*mIdx + k] = s_char;
			}
		}
	}

	cvNamedWindow("Gamma Transformations", CV_WINDOW_AUTOSIZE);
	cvShowImage("Gamma Transformations", filtered);
	cvSaveImage("gamma_tx.bmp", filtered);
	printf("\n Saved Successfully \n\n");

	display_img_info(filtered);

	return filtered;
}