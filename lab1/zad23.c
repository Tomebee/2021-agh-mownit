#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double f_double(double x);
float f_float(float x);

int main (void)
{
  double min_double,double_result,sum_double = 0;
  float min_float,float_result,sum_float = 0;
  
  for(int i = 0; i < 10000; i++) {
     double_result = f_double((double)i);
     if(i == 0) {
         min_double = double_result;
     }
     else if(double_result + 1 > 1 && double_result + 1 < min_double) {
         min_double = double_result;
     }
    sum_double += double_result;
  }
  printf("double %f min: %f\n", sum_double, min_double);
  

  for(int i = 0; i < 10000; i++) {
    float_result = f_float((float)i);
    if(i == 0) {
         min_float = float_result;
     }
    else if(float_result + 1.0f > 1.0f && float_result < min_float) {
        min_float = float_result;
    }
    sum_float += float_result;
  }

  printf("float: %.12f min: %.12f\n", sum_float, min_float);

  return 0;
}

double f_double(double x) {
  double f_n;
  if(x == 0.00) {
    return 0.01;
  }

  f_n = f_double((double)x - 1);
  
  return 4.0 * f_n - 3.0 * f_n * f_n;
}

float f_float(float x) {
  float f_n;
  if(x == 0) {
    return 0.01f;
  }

  f_n = (float)f_float(x-1);

  return 4.0f * f_n - 3.0f * f_n * f_n;
}

