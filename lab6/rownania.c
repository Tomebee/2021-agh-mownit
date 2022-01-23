#include <stdio.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

int czas(struct rusage *ru0, struct rusage *ru1){
	
	double utime = 0, stime = 0, ttime = 0;	

  	/* Obliczenie czasow. Aby mikrosekundy traktowac jako czesci sekund musimy je wymnozyc przez 10^-6*/
	utime = (double) ru1->ru_utime.tv_sec 
		+ 1.e-6 * (double) ru1->ru_utime.tv_usec 
		- ru0->ru_utime.tv_sec 
		- 1.e-6 * (double) ru0->ru_utime.tv_usec;
  	stime = (double) ru1->ru_stime.tv_sec
    		+ 1.e-6 * (double) ru1->ru_stime.tv_usec 
		- ru0->ru_stime.tv_sec
    		- 1.e-6 * (double) ru0->ru_stime.tv_usec;
	ttime = stime + utime;

	/*printf("user time: %3f\n", utime);
	printf("system time: %3f\n", stime);*/
	printf("total time: %3f\n", ttime);

} 

double rand_double()
{
	int dzielna = rand(), dzielnik = rand(), znak = rand() % 2;
	double a = (double)dzielna/dzielnik;
	if(!znak)
		a *= -1;
	return a;
}

/* oblicza i-ta skladowa wyniku mnozenia macierzy A razy wektor x */
double sprawdz(int i, int n, gsl_matrix* a, gsl_vector* x)
{
	int j;
	double wynik = 0;
	for(j=0; j<n; j++)
		wynik += gsl_matrix_get(a, i, j) * gsl_vector_get(x, j);
	return wynik;
}

int main(int argc, char** args)
{
	if(argc!=2)
	{
		printf("poprawne uzycie: ./rownania n, gdzie n to rozmiar kwadratowej macierzy\n");
		return 1;
	}
	int n, i, s, j;
    struct rusage t0, t1, t2;
	if((n=atoi(args[1])) <= 0)
	{
		printf("niepoprawny wymiar macierzy!\n");
		return 1;
	}
	
	gsl_matrix* a = gsl_matrix_alloc(n, n);
	gsl_matrix* a_kopia = gsl_matrix_alloc(n, n);
	gsl_vector* b = gsl_vector_alloc(n);
	gsl_vector* b_wymnoz = gsl_vector_alloc(n);
	gsl_vector* x = gsl_vector_alloc(n);
	gsl_permutation* p = gsl_permutation_alloc(n);
			
	srand(time(0));
     	for(i=0; i<n; i++) // wypelniam macierz A losowymi liczbami
		for(j=0; j<n; j++)
		{
			gsl_matrix_set(a, i, j, rand_double());
			gsl_matrix_set(a_kopia, i, j, gsl_matrix_get(a, i, j)); // kopia potrzebna do koncowego
		}                                                               // sprawdzenia, bo dekompozycja niszczy A
	for(i=0; i<n; i++)
		gsl_vector_set(b, i, rand_double()); // wypelniam wektor b losowymi liczbami
	
    getrusage(RUSAGE_SELF, &t0);
	gsl_linalg_LU_decomp(a, p, &s); // dekompozycja LU i rozwiazanie ukladu rownan
    getrusage(RUSAGE_SELF, &t1);
	gsl_linalg_LU_solve(a, p, b, x);	
	getrusage(RUSAGE_SELF, &t2);
	printf("Wektor x rozwiazan = \n"); // wypisuje wyliczony wektor x
	gsl_vector_fprintf (stdout, x, "%g");
	printf("\n");
    printf("Czas dekompozycji \n");
    czas(&t0,&t1);
    printf("Czas rozwiazania \n");
	czas(&t1,&t2);

	for(i=0; i<n; i++)
		gsl_vector_set(b_wymnoz, i, sprawdz(i, n, a_kopia, x)); // licze b = A*x
	
	printf("Zaalokowany wektor b = \n"); // sprawdzam zgodnosc
	// gsl_vector_fprintf (stdout, b, "%g");
	printf("\n");	
	
	printf("Wymnozony wektor b = \n");
	// gsl_vector_fprintf (stdout, b_wymnoz, "%g");
	
    gsl_permutation_free(p);
    gsl_vector_free(x);
	gsl_vector_free(b_wymnoz);
	gsl_vector_free(b);
	gsl_matrix_free(a_kopia);
	gsl_matrix_free(a);
	return 0;
}
