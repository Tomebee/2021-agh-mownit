#include "parameters.h"

int
main (int argc, char** args)
{
	int status; 
	int iter = 0, max_iter = 100; 
	const gsl_root_fsolver_type *T;
	gsl_root_fsolver *s; 
	double r = 0, r_expected = sqrt (5.0);
	double x_lo = 0.0, x_hi = 5.0; 

	gsl_function F;
	struct quadratic_params params = {1.0, 0.0, -5.0};
	F.function = &quadratic;
	F.params = &params; 

	if(argc!=2)
	{
		printf("Using: three_methods method, where method = {bisekcja, sieczne, brent}\n");
		return 1;
	}
	if(strcmp(args[1],"bisekcja")==0)
		T = gsl_root_fsolver_bisection; 
	else if(strcmp(args[1],"sieczne")==0)
		T = gsl_root_fsolver_falsepos;
	else if(strcmp(args[1],"brent")==0)
		T = gsl_root_fsolver_brent;
	else
	{
		printf("Using: three_methods method, where method = {bisekcja, sieczne, brent}\n");
		return 1;
	}			
	
	s = gsl_root_fsolver_alloc (T); 
	gsl_root_fsolver_set (s, &F, x_lo, x_hi); 

	printf ("using %s method\n", 
		gsl_root_fsolver_name (s));

	printf ("%5s [%9s, %9s] %9s %10s %9s\n", "iter", "lower", "upper", "root", "err", "err(est)");

	do
	{
		iter++;
		status = gsl_root_fsolver_iterate (s);
		r = gsl_root_fsolver_root (s);
		x_lo = gsl_root_fsolver_x_lower (s);
		x_hi = gsl_root_fsolver_x_upper (s);
		status = gsl_root_test_interval (x_lo, x_hi,
				0, 0.001);

		if (status == GSL_SUCCESS)
			printf ("Converged:\n");

		printf ("%5d [%.7f, %.7f] %.7f %+.7f %.7f\n", iter, x_lo, x_hi,
			r, r - r_expected, x_hi - x_lo);
	}
	while (status == GSL_CONTINUE && iter < max_iter);
	gsl_root_fsolver_free(s);
	return status;
}
