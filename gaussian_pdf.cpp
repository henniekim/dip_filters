#define _USE_MATH_DEFINES
#include <math.h>
#include "function_list.h"

double gaussian_rv(double stddev, double mean)
{

	 double v1, v2, s;

  do {
    v1 =  2 * ((double) rand() / RAND_MAX) - 1;      // -1.0 ~ 1.0 까지의 값
    v2 =  2 * ((double) rand() / RAND_MAX) - 1;      // -1.0 ~ 1.0 까지의 값
    s = v1 * v1 + v2 * v2;
  } while (s >= 1 || s == 0);

  s = sqrt( (-2 * log(s)) / s );

  return v1 * s;

}
