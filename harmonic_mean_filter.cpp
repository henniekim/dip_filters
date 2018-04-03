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

IplImage* harmonic_mean_filter(IplImage* img)
{
	IplImage* filtered = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);

	int i, j, nIdx, mIdx;
	int mx, my, m_ref_x, m_ref_y; // masking size
	int k; // RGB color sweep

	unsigned char pm;
	unsigned int pm_int;
	double pm_double;
	double p_double;

	printf(" Harmonic Mean Filter \n");
	printf(" Input Mask Size for x : \n");
	scanf("%d", &m_ref_x);
	printf(" Input Mask Size for y : \n");
	scanf("%d", &m_ref_y);

	mx = m_ref_x;
	my = m_ref_y;

	pm = 0;
	pm_double = 1;
	p_double = 1;

	zero_padding(filtered, 0);

	nIdx = filtered->widthStep; // y position increment -- transform space
	mIdx = filtered->nChannels; // x position increment

	for (j = 0; j < filtered->height; j++)
	{
		for (i = 0; i < filtered->width; i++)
		{
			for (k = 0; k < 3; k++)
			{

				if (j > m_ref_y / 2 && i > m_ref_x / 2 && j < img->height - m_ref_y / 2 && i < img->width - m_ref_x / 2)
				{
					for (mx = ((-m_ref_x) / 2); mx < ((m_ref_x) / 2) + 1; mx++) // subimage window
					{
						for (my = ((-m_ref_y) / 2); my < ((m_ref_y) / 2) + 1; my++) 
						{
							pm = img->imageData[(j + my)*nIdx + (i + mx)*mIdx + k];
							if (pm == 0)
							{
								pm_double += 255 ;
							}
							else
							{
								p_double = (double)pm;
								pm_double += (1.0 / p_double);
							}

						}
					}

					pm_int = (unsigned int)((double)m_ref_x*(double)m_ref_y/pm_double);

					if (pm > 255)
						pm = 255;

					pm = (unsigned char)pm_int;

					filtered->imageData[j*nIdx + i*mIdx + k] = pm;
					pm_double = 0;
				}
			}
		}
	}

	cvNamedWindow("harmonic_mean_filtered", CV_WINDOW_AUTOSIZE);
	cvShowImage("harmonic_mean_filtered", filtered);
	cvSaveImage("harmonic_mean_filtered.bmp", filtered);
	printf("\n Saved Successfully \n\n");

	display_img_info(filtered);

	return filtered;
}