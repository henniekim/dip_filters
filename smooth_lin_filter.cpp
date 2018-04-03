
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

IplImage* smooth_lin_filter(IplImage* img)
{
	IplImage* filtered = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);

	int i, j, nIdx, mIdx;
	int mx, my, m_ref; // masking size
	int k; // RGB color sweep
	unsigned char pm;
	unsigned int pm_int;
	double pm_double;
	
	printf(" Smoothing Linear Filter \n");
	printf(" Input Mask Size : \n");
	scanf("%d", &m_ref);
	mx = m_ref;
	my = m_ref;

	//zero_padding(filtered, 255);

	for (j = 0; j < filtered->height; j++)
	{
		for (i = 0; i < filtered->width; i++)
		{
			for (k = 0; k < 3; k++)
			{
				nIdx = filtered->widthStep; // y position increment -- transform space
				mIdx = filtered->nChannels; // x position increment

				pm = 0;
				pm_double = 0;

				//if (/*j > m_ref / 2 && i > m_ref / 2 && */j < img->height -m_ref /2  && i < img->width - m_ref / 2  )
				{
					for (mx = (-m_ref / 2); mx < (m_ref / 2) + 1; mx++)
					{
						for (my = (-m_ref / 2); my < (m_ref / 2) + 1; my++)
						{
							if ((( j + my < (0) || i + mx < (0)) && (mx < 0 || my < 0)) || (( (j+my >= filtered->height - (1)) || (i+mx >= filtered->width - (1))) && (mx >= 0 || my >=0)))
								pm_double += 0;
							else
							pm = img->imageData[(j + my)*nIdx + (i + mx)*mIdx + k];
							pm_double += (double)pm;
						}
					}

					pm_int = (unsigned int)(pm_double / (m_ref*m_ref));

					pm = (unsigned char)pm_int;
					filtered->imageData[j*nIdx + i*mIdx + k] = pm;
				}
			}
		}
	}

	cvNamedWindow("blurred", CV_WINDOW_AUTOSIZE);
	cvShowImage("blurred", filtered);
	cvSaveImage("blurred.bmp", filtered);
	printf("\n Saved Successfully \n\n");

	// display image information
	display_img_info(filtered);

	return filtered;
}