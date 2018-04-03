// 3, July, 2017 Digital Image Processing 2nd week
// This program was made by Kim Dong Hyun for Studying


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
#pragma warning(disable: 4819)


int main(int argc, char** argv)
{
	int sel;
	// load image
	IplImage* img = cvLoadImage("uniform_salt_pepper.tif");
	IplImage* img1;
	IplImage* img2;
	if (img == NULL)
	{
		printf(" could not find the image");
		return 0;
	}
	cvNamedWindow("img", CV_WINDOW_AUTOSIZE);
	cvShowImage("img", img);
	display_img_info(img);
	while (1)
	{
		printf(" \n-------------------------------------\n");
		printf("  input number to start processing\n");
		printf(" (1) smooth Linear filter \n");
		printf(" (2) Median filter \n");
		printf(" (3) Max filter \n");
		printf(" (4) min filter \n");
		printf(" (5) Midpoint filter \n");
		printf(" (6) Laplacian Sharpening filter \n");
		printf(" (7) Laplacian Sharpening filter 2nd \n");
		printf(" (8) Sobel Gradiant \n");
		printf(" (9) Negative filter \n");
		printf(" (10) Gaussian Noise \n");
		printf(" (11) Salt Pepper Noise \n");
		printf(" (12) Uniform Noise \n");
		printf(" (13) Geometric mean filter \n");
		printf(" (14) Harmonic mean filter \n");
		printf(" (15) Contra-Harmonic mean filter \n");
		printf(" (16) Alpha-trimmed mean filter \n");
		printf(" (17) Log Transformations \n");
		printf(" (18) Inverse Log Transformation \n");
		printf(" (19) Gamma transformation\n");
		printf(" (20) Unsharp Mask\n");
		printf(" -------------------------------------\n\n");
		int num;
		scanf("%d", &num);

		switch (num)
		{

		case 1:
			img = cvLoadImage("1041a.tif");
			smooth_lin_filter(img);
			break;

		case 2:
			img = cvLoadImage("uniform_salt_pepper.tif");
			median_filter(img);
			break;

		case 3:
			img = cvLoadImage("blurtest.tif");
			max_filter(img);
			break;

		case 4:
			img = cvLoadImage("blurtest.tif");
			min_filter(img);
			break;

		case 5:
			img = cvLoadImage("mid.tif");
			midpoint_filter(img);
			break;
		
		case 6:
			img = cvLoadImage("moon.tif");
			sharpen_filter(img);
			break;

		case 7:
			img = cvLoadImage("moon.tif");
			sharpen_filter_2nd(img);
			break;

		case 8:

			printf(" Input test image \n");
			printf(" (1) Figure 3.42 - contact lens : sobel_test.tif \n");
			printf(" (2) Figure 3.43 - skeleton : skeleton.tif \n ");
			//printf(" (3) Figure 3.9 - Aerial image : gammatest3.tif \n");
			scanf("%d", &sel);

			switch (sel)
			{
			case 1:
				img = cvLoadImage("sobel_test.tif");
				break;
			case 2:
				img = cvLoadImage("skeleton.tif");
				break;
			//case 3:
			//	img = cvLoadImage("gammatest3.tif");
			//	break;
			default:
				break;
			}

			sobel(img);
			break;

		case 9:
			img = cvLoadImage("logtest.tif");
			negative(img);
			break;


		case 10:
			img = cvLoadImage("noise_test.tif");
			gaussian(img);
			break;

		case 11:
			img = cvLoadImage("lena.bmp");
			salt_pepper_noise(img);
			break;

		case 12:
			img = cvLoadImage("noise_test.tif");
			uniform_noise(img);
			break;

		case 13:
			img = cvLoadImage("noise_test.tif");
			geometric_mean_filter(img);
			break;

		case 14:
			img = cvLoadImage("salt_pepper_noise.bmp");
			harmonic_mean_filter(img);
			break;

		case 15:
			img = cvLoadImage("salt.tif");
			contraharmonic_mean_filter(img);
			break;

		case 16:
			alpha_trimmed_mean_filter(img);
			break;

		case 17 :
			img = cvLoadImage("unsharpmask.bmp");
			log_tx(img);
			break;

		case 18 :
			img = cvLoadImage("negative.bmp");
			inverse_log_tx(img);
			break;

		case 19 :

			printf(" Input test image \n");
			printf(" (1) Figure 3.7 - Black & White : gammatest1.tif \n");
			printf(" (2) Figure 3.8 - MRI : gammatest2.tif \n ");
			printf(" (3) Figure 3.9 - Aerial image : gammatest3.tif \n");
			scanf("%d", &sel);

			switch (sel)
			{
			case 1 : 
				img = cvLoadImage("gammatest.tif");
				break;
			case 2: 
				img = cvLoadImage("gammatest2.tif");
				break;
			case 3: 
				img = cvLoadImage("gammatest3.tif");
				break;
			default :
				break;
			}
			
			gamma_tx(img);
			break;

		case 20:
			img1 = cvLoadImage("unsharp_test.tif");
			img2 = cvLoadImage("blurred.bmp");
			unsharpmask(img1, img2);
			break;

		default:
			printf(" selected process does not exist\n");
			break;
		}
	}
	return 0;

}











