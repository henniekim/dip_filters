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
#include <stdlib.h>
#include <time.h>


IplImage* gaussian(IplImage* img)
{
	IplImage* filtered = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);

	srand((unsigned)time(NULL));

	int i, j, nIdx, mIdx;
	int k; // RGB color sweep
	unsigned char img_char_0, img_char_1, img_char_2;

	unsigned int sum_0 =0 , sum_1 = 0, sum_2 = 0;
	double fst_moment_0=0, fst_moment_1=0, fst_moment_2 = 0;
	double snd_moment_0 =0 , snd_moment_1 =0 , snd_moment_2 = 0;
	double var_0 = 0, var_1 = 0 , var_2 = 0;
	double std_0 = 0 , std_1, std_2;

	unsigned char gaussian_char;
	int gaussian_int_0, gaussian_int_1, gaussian_int_2;
	int noise_0, noise_1, noise_2;

	unsigned char p0;
	unsigned char p1;
	unsigned char p2;

	unsigned int width;
	unsigned int height;
	unsigned int size;

	int std = 0;
	int m = 0;
	printf(" Gaussian Noise Filter \n\n");
	printf(" Input standard deviation :");
	scanf("%d", &std);

	for (j = 0; j < filtered->height; j++)
	{
		for (i = 0; i < filtered->width; i++)
		{
			double gauss = gaussian_rv(std, m);

			noise_0 = gauss*std;
				
			for (k = 0; k < 3; k++)
			{

				nIdx = filtered->widthStep; // y position increment -- transform space
				mIdx = filtered->nChannels; // x position increment


				unsigned char q0 = img->imageData[j*nIdx + i*mIdx + k];

				gaussian_int_0 = q0 + noise_0;

				if (gaussian_int_0 > 255)
					gaussian_int_0 = 255;
				if (gaussian_int_0 < 0)
					gaussian_int_0 = 0;

				filtered->imageData[j*nIdx + i*mIdx + k] = (unsigned char)gaussian_int_0;
			}
		}
	}

	cvNamedWindow("gaussian_noise", CV_WINDOW_AUTOSIZE);
	cvShowImage("gaussian_noise", filtered);
	cvSaveImage("gaussian_noise.bmp", filtered);
	printf("\n Saved Successfully \n\n");


	display_img_info(filtered);
	
	return filtered;
}