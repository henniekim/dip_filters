
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


IplImage* geometric_mean_filter(IplImage* img)
{
	IplImage* filtered = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);
	
	int i, j, nIdx, mIdx;
	int mx, my, m_ref_x, m_ref_y ; // masking size
	int k; // RGB color sweep

	unsigned char pm;
	unsigned int pm_int;
	double pm_double;

	printf(" Geometric Mean Filter \n");
	printf(" Input Mask Size for x : \n");
	scanf("%d", &m_ref_x);
	printf(" Input Mask Size for y : \n");
	scanf("%d", &m_ref_y);

	mx = m_ref_x;
	my = m_ref_y;

	pm = 1;
	pm_double = 1;

	zero_padding(filtered, 255);

	nIdx = filtered->widthStep; // y position increment -- transform space
	mIdx = filtered->nChannels; // x position increment

	for (j = 0; j < filtered->height; j++)
	{
		for (i = 0; i < filtered->width; i++)
		{
			

			for (k = 0; k < 3; k++)
			{
				pm_double = 1;

				if (j > m_ref_y / 2 && i > m_ref_x / 2 && j < img->height - m_ref_y / 2   && i < img->width - m_ref_x / 2 )
				{
					for (mx = ((-m_ref_x) / 2); mx < ((m_ref_x) / 2) + 1; mx++) // subimage window
					{
						for (my = ((-m_ref_y) / 2); my < ((m_ref_y) / 2) + 1; my++)  // minus 0.001 to correct even number case
						{

							pm = img->imageData[(j + my)*nIdx + (i + mx)*mIdx + k];
							if (pm == 0)
								pm = 1; 
							pm_double *= (double)(pow((double)pm,1/((double)(m_ref_x))));
							//printf(" %lf", pm_double);

						}
					}

					pm_double = pow(pm_double, 1/((double)m_ref_y));

					//printf(" %lf", pm_double);
					if (pm_double > 255)
						pm_double = 255;
					if (pm_double < 0)
						pm_double = 0;

					pm_int = (unsigned int)(pm_double);
					pm = (unsigned char)pm_int;

					
					filtered->imageData[j*nIdx + i*mIdx + k] = pm;
				}
			}
		}
	}

	cvNamedWindow("Geometric_mean_filter", CV_WINDOW_AUTOSIZE);
	cvShowImage("Geometric_mean_filter", filtered);
	cvSaveImage("Geometric_mean_filter.bmp", filtered);
	printf("\n Saved Successfully \n\n");

	display_img_info(filtered);

	return filtered;
}