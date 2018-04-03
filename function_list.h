#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

void display_img_info(IplImage* img);

IplImage* smooth_lin_filter(IplImage* img); // 1
IplImage* median_filter(IplImage* img); // 2
IplImage* max_filter(IplImage* img); // 3
IplImage* min_filter(IplImage* img); // 4
IplImage* midpoint_filter(IplImage* img); // 5

IplImage* sharpen_filter(IplImage* img); // 6
IplImage* sharpen_filter_2nd(IplImage* img); // 7
IplImage* sobel(IplImage* img); // 8
IplImage* negative(IplImage* img); // 9

IplImage* gaussian(IplImage* img); // 10 
IplImage* salt_pepper_noise(IplImage* img); // 11
IplImage* uniform_noise(IplImage* img); //12
IplImage* geometric_mean_filter(IplImage* img); //13
IplImage* harmonic_mean_filter(IplImage* img); // 14
IplImage* contraharmonic_mean_filter(IplImage* img); // 15
IplImage* alpha_trimmed_mean_filter(IplImage* img); // 16
IplImage* log_tx(IplImage* img); // 17 
IplImage* inverse_log_tx(IplImage* img);// 18
IplImage* gamma_tx(IplImage* img);  // 19
IplImage* unsharpmask(IplImage* img, IplImage* img2); // 20

void zero_padding(IplImage* img, unsigned char pad); 
int bubble_sort(int array[9]);
int* bubble_sort_dynamic(int size, int* arr); // size of array
double gaussian_rv(double stddev, double mean);
int max_of_img(IplImage* img);
int min_of_img(IplImage* img);