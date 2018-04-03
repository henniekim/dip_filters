
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

int* bubble_sort_dynamic(int size, int* arr) // size of array
{
	int i, j, temp = 0;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (*(arr + j) > *(arr + j + 1))
			{
				temp = *(arr + j);
				*(arr + j) = *(arr + j + 1);
				*(arr + j + 1) = temp;
			}			
		}
	}
	return arr;
}