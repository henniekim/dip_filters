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


IplImage* unsharpmask(IplImage* img, IplImage* img2)
{
	
	IplImage* unsharpmask = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);


	int i, j, k, nIdx, mIdx;
	double c;
	printf(" input k : \n");
	scanf("%lf", &c);
	for (j = 0; j < img->height; j++)
	{
		for (i = 0; i < img->width; i++)
		{
			for (k = 0; k < 3; k++)
			{
					nIdx = img->widthStep; // y position increment -- transform space
					mIdx = img->nChannels; // x position increment

					unsigned char tmp1 = img->imageData[j*nIdx + i*mIdx + k];
					unsigned char tmp2 = img2->imageData[j*nIdx + i*mIdx + k];

					int tmp3 = (int)tmp1 - (int)tmp2;
					
					unsigned int tmp4 = abs(tmp3);
					unsigned char tmp5 = (unsigned char)tmp4;
					//printf("%d ", tmp5);
					unsharpmask->imageData[j*nIdx + i*mIdx + k] = tmp5;

					unsigned char pm = img->imageData[j*nIdx + i*mIdx + k];

					int pm_int = (int)pm;

					if (tmp3 >= 0)
					{
						pm_int += (int)(c*(double)tmp3);

						if (pm_int > 255)
							pm_int = 255;
						if (pm_int < 0)
							pm_int = 0;

						img->imageData[j*nIdx + i*mIdx + k] = (unsigned char)pm_int;
					}


					if (tmp3 < 0)
					{
						tmp3 = -tmp3;
						pm_int += (int)(-c*(double)tmp3);
						if (pm_int > 255)
							pm_int = 255;
						if (pm_int < 0)
							pm_int = 0;
						img->imageData[j*nIdx + i*mIdx + k] = (unsigned char)pm_int;
					}

			}
		}
	}

	cvNamedWindow("sharpen", CV_WINDOW_AUTOSIZE);
	cvShowImage("sharpen", img);
	cvSaveImage("sharpen_mask.bmp", img);
	printf("\n Saved Successfully \n\n");
	display_img_info(img);

	cvNamedWindow("unsharpmask", CV_WINDOW_AUTOSIZE);
	cvShowImage("unsharpmask", unsharpmask);
	cvSaveImage("unsharpmask.bmp", unsharpmask);
	printf("\n Saved Successfully \n\n");
	display_img_info(unsharpmask);

	return img;
}