#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double f_double(double x);
float f_float(float x);

int main (void)
{
  double sum_double = 0;
  float sum_float = 0;
  
  for(int i = 0; i < 10000; i++) {
    
    sum_double += f_double((double)i);
    
  }
  printf("double %f\n", sum_double);
  

  for(int i = 0; i < 10000; i++) {
    sum_float += f_float((float)i);
  }

  printf("float: %.12f\n", sum_float);

  return 0;
}

double f_double(double x) {
  double f_n;
  if(x == 0.00) {
    return 0.01;
  }

  f_n = f_double((double)x - 1);
  
  return f_n + 3.0 * f_n * (1.0 - f_n);
}

float f_float(float x) {
  float f_n;
  if(x == 0) {
    return 0.01f;
  }

  f_n = (float)f_float(x-1);

  return (float)(f_n + 3.0f * f_n * (1 - f_n));
}

