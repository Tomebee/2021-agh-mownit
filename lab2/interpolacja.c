//#include <config.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>

static double fun(double x)
{
  return x + cos(x*x);
}

int main (void)
{
  const double a = 1.0;
  const double b = 10.0;
  const int steps = 10;
  double xi, yi, yi2, x[100], y[100], dx;
  FILE *input, *output;
  int i;

  input = fopen("wartosci.txt", "w");
  output = fopen("inter.txt", "w");

  dx = (b-a) / (double) steps;

  for (i = 0; i <= steps; ++i) {
	  x[i] = a + (double)i * dx + 0.5 * sin((double)i * dx);
      y[i] = fun(x[i]);
      fprintf (input,"%g %g\n", x[i], y[i]);
  }

  {
    gsl_interp_accel *acc 
      = gsl_interp_accel_alloc ();

    gsl_spline *spline_polynomial 
      = gsl_spline_alloc (gsl_interp_polynomial, steps + 1);
    gsl_spline *spline_csp = gsl_spline_alloc(gsl_interp_cspline, steps + 1);

    gsl_spline_init(spline_polynomial, x, y, steps + 1);
    gsl_spline_init(spline_csp, x, y, steps + 1);

    for (xi = a; xi <= b; xi += 0.01) {
        yi = gsl_spline_eval(spline_polynomial, xi, acc);
        yi2 = gsl_spline_eval(spline_csp, xi, acc);
        fprintf (output,"%g %g %g\n", xi, yi, yi2);
	}
	
    gsl_spline_free(spline_polynomial);
    gsl_spline_free(spline_csp);
    gsl_interp_accel_free(acc);
  }
  return 0;
}

