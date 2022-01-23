#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>

double f1(double x) {
    return x * x;
}

double f2(double x) {
    return 1/sqrt(x);
}

double calculateIntegral(double (*f)(double x), float a, float b, int n) {
    const double dx = (b - a) / (float) n;

    double sum = 0;

    for(int i =1; i<= n; i++) {
        double x = a + i * dx;
        sum += f(x);
    }

    return dx * sum;
}

void analyzeIntegral(double (*f)(double x), double expected, const char *funcName) {
    printf("%s: \n", funcName);

    for(int i = 3; i <= 6; i++) {
        double result, error, limit = pow10((-1)*i);
        int intervals = 1;

        while((error = fabs((result = calculateIntegral(f, 0, 1, intervals++)) - expected)) >= limit) {
            printf("\rf(x): %s | value: %.18f | error %.3e <= %.1e | %d intervals. ", 
                funcName,
                result,
                error,
                limit,
                intervals);
            
            fflush(stdout);
        }
        printf("\n");
    }
}

int main() {
   analyzeIntegral(f1, 1/3.0, "x^2");
   analyzeIntegral(f2, 2.0, "1/sqrt(x)");

   return 0;
}


