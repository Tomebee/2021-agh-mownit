#include "parameters.h"


int
main (int argc, char** args)
{
	int status; 
	int iter = 0, max_iter = 100; 
	const gsl_root_fdfsolver_type *T; 
	gsl_root_fdfsolver *s; 
	double r0, r = 5.0, r_expected = 1.0; 
	gsl_function_fdf F; 
	
	struct quadratic_params params = {1.0, -2.0, 1.0};
	F.f = &quadratic;
	F.df = &quadratic_deriv;
	F.fdf = &quadratic_fdf;
	F.params = &params;

	if(argc!=2)
	{
		printf("Using: fdf method, where method = {newton, secant, steffenson}\n");
		return 1;
	}
	if(strcmp(args[1],"newton")==0)
		T = gsl_root_fdfsolver_newton;
	else if(strcmp(args[1],"secant")==0)
		T = gsl_root_fdfsolver_secant; 
	else if(strcmp(args[1],"steffenson")==0)
		T = gsl_root_fdfsolver_steffenson; 
	else
	{
		printf("Using: fdf method, where method = {newton, secant, steffenson}\n");
		return 1;
	}			
	
	s = gsl_root_fdfsolver_alloc (T);
	gsl_root_fdfsolver_set (s, &F, r); 

	printf ("using %s method\n", 
		gsl_root_fdfsolver_name (s)); 
	
	printf ("%-5s %10s %10s %10s\n", "iter", "root", "err", "err(est)");

	do
	{
		iter++;
		status = gsl_root_fdfsolver_iterate (s);
		r0 = r;
		r = gsl_root_fdfsolver_root (s);
		status = gsl_root_test_delta (r, r0, 0, 1e-3);		

		if (status == GSL_SUCCESS)
			printf ("Converged:\n");

		printf ("%5d %10.7f %+10.7f %10.7f\n",
			iter, r, r - r_expected, r - r0);
	}
	while (status == GSL_CONTINUE && iter < max_iter);
	gsl_root_fdfsolver_free(s);
	return status;
}
