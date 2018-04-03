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



IplImage* salt_pepper_noise(IplImage* img)
{
	IplImage* filtered = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);

	int i, j, nIdx, mIdx;
	int k; // RGB color sweep
	int r0 = 1;
	int scale;

	srand((unsigned)time(NULL));
	printf(" Salt & Pepper Noise \n\n");
	printf(" input scale : (the lower the denser) from 2 to infinity \n");
	scanf("%d", &scale);

	for (j = 0; j < filtered->height; j++)
	{
		for (i = 0; i < filtered->width; i++)
		{
		
			nIdx = filtered->widthStep; // y position increment -- transform space
			mIdx = filtered->nChannels; // x position increment

			r0 = rand() % scale;

			for (k = 0; k < 3; k++)
			{
				if (r0 == 0)
					filtered->imageData[j*nIdx + i*mIdx + k] = 0;
				else if (r0 == 1)
					filtered->imageData[j*nIdx + i*mIdx + k] = 255;
				else
					filtered->imageData[j*nIdx + i*mIdx + k] = img->imageData[j*nIdx + i*mIdx + k];
			}
		}
	}

	cvNamedWindow("salt_pepper_noise", CV_WINDOW_AUTOSIZE);
	cvShowImage("salt_pepper_noise", filtered);
	cvSaveImage("salt_pepper_noise.bmp", filtered);
	printf("\n Saved Successfully \n\n");

	display_img_info(filtered);

	return filtered;
}