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


void display_img_info(IplImage* img)
{
	// display image information
	printf("image size = %d kB \n", img->imageSize / 1024);
	printf("colorModel = %s\n", img->colorModel);
	printf("channelSeq = %s\n", img->channelSeq);
	printf("image pixel size = %d x %d \n", img->width, img->height);
	printf("# of channel = %d \n", img->nChannels);
	printf("depth = %d \n", img->depth);
	printf("width Step = %d B \n", img->widthStep);
	cvWaitKey(0);
}