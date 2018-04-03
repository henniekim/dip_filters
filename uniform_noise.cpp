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
#include <time.h>
#include <stdlib.h>


IplImage* uniform_noise(IplImage* img)
{
	IplImage* filtered = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);

	srand((unsigned)time(NULL));

	int i, j, nIdx, mIdx;
	int k; // RGB color sweep
	unsigned int r0 = 1;
	int scale;

	srand((unsigned)time(NULL));
	printf(" Uniform Noise \n\n");
	printf(" input scale : (the lower the denser) from 2 to infinity \n");
	scanf("%d", &scale);

	for (j = 0; j < filtered->height; j++)
	{
		for (i = 0; i < filtered->width; i++)
		{

			nIdx = filtered->widthStep; // y position increment -- transform space
			mIdx = filtered->nChannels; // x position increment

			r0 = rand() % scale;

			int p0;
			unsigned char q0;


			for (k = 0; k < 3; k++)
			{
				q0 = img->imageData[j*nIdx + i*mIdx + k];
				p0 = q0 + r0 - 0.5*(unsigned int)scale;
				if (p0 > 255)
					p0 = 255;
				if (p0 < 0)
					p0 = 0;

				filtered->imageData[j*nIdx + i*mIdx + k] = (unsigned char)p0;
				
			}
		}
	}

	cvNamedWindow("uniform_noise", CV_WINDOW_AUTOSIZE);
	cvShowImage("uniform_noise", filtered);
	cvSaveImage("uniform_noise.bmp", filtered);
	printf("\n Saved Successfully \n\n");

	display_img_info(filtered);

	return filtered;
}