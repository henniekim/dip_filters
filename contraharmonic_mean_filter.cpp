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

IplImage* contraharmonic_mean_filter(IplImage* img)
{
	IplImage* filtered = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);

	int i, j, nIdx, mIdx;
	int mx, my, m_ref_x, m_ref_y; // masking size
	int k; // RGB color sweep
	double q; // Order of the filter

	unsigned char pm;
	unsigned int pm_int;
	double pm_double;
	double p_double;

	printf(" Contra-harmonic Mean Filter \n");
	printf(" Input Mask Size for x : \n");
	scanf("%d", &m_ref_x);
	printf(" Input Mask Size for y : \n");
	scanf("%d", &m_ref_y);
	printf(" Input Order of the filter : \n");
	printf(" For Positive value to eliminate pepper noise \n");
	printf(" For Negative value to eliminate salt noise \n");
	printf(" q = 0 for arithmetic mean filter, q = -1 for harmonic mean filter \n");
	scanf("%lf", &q);

	mx = m_ref_x;
	my = m_ref_y;

	pm = 0;
	pm_double = 0;
	p_double = 0;

	zero_padding(filtered, 0);

	nIdx = filtered->widthStep; // y position increment -- transform space
	mIdx = filtered->nChannels; // x position increment

	for (j = 0; j < filtered->height; j++)
	{
		for (i = 0; i < filtered->width; i++)
		{
			for (k = 0; k < 3; k++)
			{

				if (j > m_ref_y / 2 && i > m_ref_x / 2 && j < img->height - m_ref_y / 2 + 1&& i < img->width - m_ref_x / 2 + 1)
				{
					for (mx = (-m_ref_x / 2); mx < ( m_ref_x / 2) + 1; mx++) // subimage window
					{
						for (my = (-m_ref_y / 2); my < (m_ref_y / 2) + 1; my++)  // minus 0.001 to correct even number case
						{
							pm = img->imageData[(j + my)*nIdx + (i + mx)*mIdx + k];
							
							double pm_temp = (double)pm;

							p_double += pow(pm_temp, q + 1);
							//if (pm == 0)
							//	pm_temp = 0.001;
							pm_double += pow(pm_temp,q);

						}
					}

					pm_int = (unsigned int)(p_double/pm_double);

					if (pm_int > 255)
						pm_int = 255;
					if (pm_int < 0)
						pm_int = 0;
					pm = (unsigned char)pm_int;

					filtered->imageData[j*nIdx + i*mIdx + k] = pm;
					pm_double = 0;
					p_double = 0;
				}
			}
		}
	}

	cvNamedWindow("contraharmonic_mean_filter", CV_WINDOW_AUTOSIZE);
	cvShowImage("contraharmonic_mean_filter", filtered);
	cvSaveImage("contraharmonic_mean_filter.bmp", filtered);
	printf("\n Saved Successfully \n\n");

	display_img_info(filtered);

	return filtered;
}