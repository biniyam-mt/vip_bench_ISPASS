#include <stdio.h>

#include "../../config.h"
#include "mathlib.h"

typedef VIP_ENCDOUBLE (*fn_type)(VIP_ENCDOUBLE x);

double sqrt_value;

#define FN_SQRT

#ifdef FN_SQRT
VIP_ENCDOUBLE
f(VIP_ENCDOUBLE x)
{
  return x*x - sqrt_value;
}

VIP_ENCDOUBLE
df(VIP_ENCDOUBLE x)
{
  return x*2.0;
}
#endif

#ifdef FN_COMPLEX
VIP_ENCDOUBLE
f(VIP_ENCDOUBLE x)
{
  return x*x*x - x - 1.0;
}

VIP_ENCDOUBLE
df(VIP_ENCDOUBLE x)
{
  return x*3.0 - 1.0;
}
#endif



// calculate function value using Newton-Raphson method
VIP_ENCDOUBLE rn_solver(VIP_ENCBOOL& converged, double maxerr, unsigned maxiter, fn_type f, fn_type df)
{
  unsigned iter;
  VIP_ENCDOUBLE guess = 1.0;

  converged = false;
  for (iter = 0; iter < maxiter; iter++) {
      converged = myfabs_na(f(guess)) <= maxerr;

/**** IISWC DO Transformation: LOOP Conversion - LB ****/
/**** Early exit loop ****/
/**** IISWC DO Transformation: IF Conversion - LB ****/
/**** After loop conversion, if will be present before predication ****/
      if (converged)
        break;
      guess = guess - f(guess)/df(guess);
  }
  return guess;
}


double testdata[] = {
  395856.76220473,270306.80574294,932459.74833807,881022.81949615,70473.028447684,582103.8084143,37192.131696927,
  607938.62471086,329081.89022736,78531.037513184,325073.20247627,648692.01186933,744982.1258859,236439.23130461,
  7397.74047289,973218.15857982,846514.65828256,804528.86250616,804592.95559602,317002.2601471,539128.20585759,
  300805.543927,808726.5000455196,398639.79574811,746867.29179032,726986.58426265,89910.107895278,152448.39631835,
  971033.76322222,849626.4469692,834030.4248274,247231.09454278,863139.85370489,517243.77285195,798550.73169246,
  355200.70467728,10331.048309033,305804.09107807,958121.83380634,100665.02513818,540398.10389697,361497.4429536,
  571322.02067934,219532.94205547,3315.861315617,290434384.19881872,479817.47545507,307333.29886535,71797.849784014,
  870080.84816375
};
#define NTESTDATA   (sizeof(testdata)/sizeof(double))




int main(void) {
  /**** Init Data ****/
  VIP_ENCDOUBLE root;
  VIP_ENCBOOL converged;
  VIP_ENCDOUBLE roots[NTESTDATA];
  VIP_ENCDOUBLE converges[NTESTDATA];

  /**** Kernel ****/
  { 
    Stopwatch s("VIP_Bench Runtime");
    for (unsigned int i=0; i < NTESTDATA; i++) {
      sqrt_value = testdata[i];
      root = rn_solver(converged, 0.00001, 20, f, df);
      roots[i] = root;
      converges[i] = converged;
    }
  }

  /**** Print Results ****/
  for (unsigned int i=0; i < NTESTDATA; i++) {
    printf("sqrt(%lf) == %lf (converged:%c)\n", testdata[i], VIP_DEC(roots[i]), VIP_DEC(converges[i]) ? 't' : 'f');
  }
  
  return 0;
}
