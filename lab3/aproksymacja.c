#include <stdio.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_chebyshev.h>

double f(double x, void *p)
{
  (void)(p); /* avoid unused parameter warning */

  return exp(x * x);
  // return fabs(x + x * x * x);
  // return (x > 0) - (x < 0); // sign(x)
}

int main (void)
{
  FILE *output;
  int i, n = 500;
  output = fopen("aproksymacja.txt", "w");
  gsl_cheb_series *cs = gsl_cheb_alloc (40);

  gsl_function F;

  F.function = f;
  F.params = 0;

  gsl_cheb_init (cs, &F, -1.0, 1.0);

  for (i = -1000; i <= 1000; i++)
  {
    double x = i / (double) 1000;
    double r2 = gsl_cheb_eval_n (cs, 2, x);
    double r5 = gsl_cheb_eval_n (cs, 5, x);
    double def = gsl_cheb_eval (cs, x);
    fprintf (output,"%g %g %g %g %g\n", x, GSL_FN_EVAL(&F, x), def, r2, r5);
  }

  gsl_cheb_free (cs);

  return 0;
}

