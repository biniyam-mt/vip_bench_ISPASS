/* Kepler.c:

   Solve Kepler's equation using various methods. Can be run as a standalone
   program or called via the entry point kepler (see below.)

   Kepler's equation is the transcendental equation

	E = M + e sin(E)

   where M is a given angle (in radians) and e is a number in the range
   [0,1). Solution of Kepler's equation is a key step in determining the
   position of a planet or satellite in its orbit. Here e is the eccentricity
   of the elliptical orbit and M is the "Mean anomaly." M is a fictitious
   angle that increases at a uniform rate from 0 at perihelion to 2Pi in
   one orbital period. E is an angle at the center of the ellipse. It is
   somewhat difficult to describe in words its precise geometric meaning --
   see any standard text on dynamical or positional astronomy, e.g.,
   W.E. Smart, Spherical Astronomy. Suffice it to say that E determines
   the angle v at the focus between the radius vector to the planet and
   the radius vector to the perihelion, the "true anomaly"  (the ultimate
   angle of interest.) Thus, kepler's equation provides the link between the
   "date", as measured by M, and the angular position of the planet on its
    orbit. 

   Compile: cc -o kepler kepler.c -lm

   ( Use the flag -D_SHORT_STRINGS if your compiler cannot handle multiline
     strings.)

   For usage information, give the command kepler -h or see USAGE defined
   below.

   API usage:

	extern int kepler(double *E, double M, double e, double derror,
            int method);

	where the last two parameters are a double specifying the 
        precision and an int specifying the method. The possible values
        of m are:

	m=0: simple iteration. 
	m=1: Newton's method.
	m=2: Binary search.
	m=3: Power series in e.
	m=4: Fourier Bessel series. 

        The answer is returned through the pointer passed as first argument.
	The function returns the number of iterations required or -1
	in case of an error.

   Also possibly of interest is the included routine for calculating bessel
   functions of the first kind with integer index, although I'm sure the
   implementation is pretty naive. The calling sequence is:

	extern double J(int n, double x);

   Compile this file with cc -c -DNO_MAIN and link your program with kepler.o.

   Author: Terry R. McConnell
	   trmcconn@syr.edu

*/

#ifndef KEPLER_CALC_CPP
#define KEPLER_CALC_CPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
// #include <math.h>

#include "../../config.h"
#include "mathlib.h"

#define VERSION "1.11"

#ifndef PI
#define PI 3.14159265359
#endif
#define LAPLACE_LIMIT .6627434193
#define USAGE "kepler [-h -v -a <.nnnn...> -m <k>] M e"

#ifdef _SHORT_STRINGS
#define HELP USAGE
#else
#define HELP USAGE"\n\
-h: print this helpful message\n\
-v: print version number and exit\n\
-a: obtain solution to accuracy of  < .nnnn (default .0000001)\n\
-m: use selected calculation method k, where\n\
	k = 1: Simple iteration.\n\
	k = 2: Newton's method.\n\
	k = 3: Binary search.\n\
	k = 4: Series in powers of e. (e<.6627434193.)\n\
	k = 5: Fourier Bessel series.\n\
M = mean anomaly (radians)\n\
e = orbit eccentricty."
#endif

/* E = eccentric anomaly,
   e = eccentricity,
   M = mean anomaly
   (using radian measure).
*/

double bin_fact(int n, int j);  /* Used with e-series method. See below. */
VIP_ENCDOUBLE J(int, VIP_ENCDOUBLE);           /* Calculates Bessel function. */
#define MAXITER     16
static double derror = 0.000001;

/* All the algorithms for solving kepler's equation are implemented in
   the following subroutines. A subroutine is called iteratively from
   main, until the previous value of E differs from the current one by
   less than derror.

   To add a new method, add its implementation as a subroutine 
   with signature

	double foo(double E, double e, double M, int reset);

   It should return a better approximation to the true E
   given the current E and the values of e and M. When passed a 
   nonzero value for the reset parameter it should reinitialize any
   static information it retains and return.
   Then add the address of
   the new subroutine to the methods array defined below.
*/ 

/* CURRENTLY IMPLEMENTED METHODS: */

/* Used to solve kepler's equation by simple iteration */

VIP_ENCDOUBLE strict_iteration(VIP_ENCDOUBLE E, VIP_ENCDOUBLE e, VIP_ENCDOUBLE M, int reset)
{

	/* reset is not used in this routine. It may generate a compiler
           warning */
	return M + e*mysin_na(E);
}

/* The following routine is used to solve kepler's equation using
   Newton's method. It is very fast and reliable for small values of
   e, but can be wildly erratic for e close to 1. See, e.g, the discussion
   in Jean Meeus, Astronomical Algorithms, Willmann-Bell, 1991, 181-193.
*/

VIP_ENCDOUBLE newton(VIP_ENCDOUBLE E, VIP_ENCDOUBLE e, VIP_ENCDOUBLE M, int reset)
{
	/* reset is not used in this routine. It may generate a compiler
           warning */
	return E + (M + e*mysin_na(E) - E)/((VIP_ENCDOUBLE)1 - e*mycos_na(E));
}

/* The following routine implements the binary search algorithm due
   to Roger Sinnott, Sky and Telescope, Vol 70, page 159 (August 1985.)
   It is not the fastest algorithm, but it is completely reliable. 
*/

VIP_ENCDOUBLE binary(VIP_ENCDOUBLE E, VIP_ENCDOUBLE e, VIP_ENCDOUBLE M, int reset)
{
	static double scale = .7853981633975;   /* PI/4 */
	VIP_ENCDOUBLE R;
	VIP_ENCDOUBLE X;

  // reset is not private
	if(reset) {
		scale = PI/4.0;
		return 0.0;
	}

	R = E - e*mysin_na(E);

/**** IISWC DO Transformation: IF Conversion - LB ****/
  if (M > R)
    X = E + scale;
  else
    X = E - scale;

	scale = scale/2.0;
	return X;
}

/* The following infinite series expansion for E in powers of e is known:

                 __
	        \       n
	E = M +      A e
		/__   n
		n=1

where              __ 
       	     n-1  \          k            (n-1)
A =      (1/2 n!)        (-1) C(n,k)(n-2k)   sin((n-2k)M),
 n                /__
                 0<= k <= [n/2]

which converges for e < LAPLACE_LIMIT (defined above). This is based upon
the Laplace inversion formula -- see the discussion of Burmann's theorem
and following material in Whittaker and Watson.

The bin_fact helper routine calculates C(n,k)(n-2k)^(n-1)/n!2^(n-1) */

VIP_ENCDOUBLE e_series(VIP_ENCDOUBLE E, VIP_ENCDOUBLE e, VIP_ENCDOUBLE M, int reset)
{
	static int n;
	int k;
	VIP_ENCDOUBLE n_2k,a_n=0.0,s_k;

  // reset is not private
	if(reset){
		n = 0;
		return 0.0;
	}

  // n is not private
	if (n==0){
		n++;
		return M;
	}


	for(k=0;2*k<=n;k++){
		n_2k = (double)n - 2.0 * ((double)k);
    	// k is not private
		s_k = k%2 ? -1.0 : 1.0;   /*   (-1)^k */
		a_n = a_n + (s_k*bin_fact(n,k)*mysin_na(n_2k*M));
	}
	n++;
	return E + mypow_na(e,n-1)*a_n;
}
	
/* The eccentric anomaly is an odd periodic function in the Mean Anomoly
   and so can be developed in a Fourier sine series. This turns out to
   be 
                 __
	        \  
	E = M +      (2/n)J (ne)sin(nM)
		/__        n 
		n=1

  where J_n is the Bessel function of the first kind. See, e.g, A Mathematical
  Introdution to Celestial Mechanics, Harry Pollard, Prentice Hall, 1966,
  pp 22-23. The following routine is used to sum this series.
*/


VIP_ENCDOUBLE j_series(VIP_ENCDOUBLE E, VIP_ENCDOUBLE e, VIP_ENCDOUBLE M, int reset)
{
	static int n;
	VIP_ENCDOUBLE dn, term;

  // reset is not private
	if(reset){
		n = 0;
		return 0.0;
	}

	if (n==0)
  {
		n++;
		return M;
	}

	dn = (double)n;
	term = ((VIP_ENCDOUBLE)2.0/(double)n)*J(n,dn*e)*mysin_na(dn*M);
	n++;
	return E + term;
}

typedef VIP_ENCDOUBLE (*method_fn)(VIP_ENCDOUBLE, VIP_ENCDOUBLE, VIP_ENCDOUBLE, int);
static method_fn methods[] = {
          strict_iteration,
					newton,
					binary,
					e_series,
					j_series,
				};

#define NMETHODS (sizeof methods /sizeof(void *))

/* Symbolic constants for method indices. */
#define IITERATION 0
#define INEWTON 1
#define IBINARY 2
#define IESERIES 3
#define IJSERIES 4



VIP_ENCDOUBLE
solve_kepler(int m, VIP_ENCDOUBLE M, VIP_ENCDOUBLE e)
{
	VIP_ENCDOUBLE sign = 1.0;
   	VIP_ENCDOUBLE E_old=PI/2;
   	VIP_ENCDOUBLE E;
   	VIP_ENCDOUBLE (*method)(VIP_ENCDOUBLE,VIP_ENCDOUBLE, VIP_ENCDOUBLE,int) = (VIP_ENCDOUBLE(*)(VIP_ENCDOUBLE,VIP_ENCDOUBLE,VIP_ENCDOUBLE,int))methods[m-1];



	/* Normalize M to lie between 0 and PI */
/**** IISWC DO Transformation: IF Conversion - LB ****/
	sign = M > 0 ? 1.0 : -1.0;

	M = myfabs_na(M)/((VIP_ENCDOUBLE)2*PI);
	M = (M - myfloor_na(M))*2*PI*sign;

/**** IISWC DO Transformation: IF Conversion - LB ****/
	sign = 1.0;
	if(M > PI){
		M = 2*PI - M;
		sign = -1.0;
	}
	/* Do selected calculation, and quit when accuracy is bettered. */

/**** IISWC DO Transformation: Loop Conversion - LB ****/
	while(myfabs_na(E_old - (E = method(E_old,e,M,0))) >= derror){
		E_old = E;
	}

	return sign*E;
}

/* The bin_fact routine calculates C(n,k)(n-2k)^(n-1)/n!2^(n-1). This
   routine assumes 2k <  n, and tries to keep the intermediate products
   small to prevent overflow.  */

int
main(void)
{
	/**** Init Data ****/
	VIP_INIT;
	VIP_ENCDOUBLE results[5];


	/**** Kernel ****/
	{
		Stopwatch s("VIP_Bench Runtime");
		results[0] = solve_kepler(1, 0.34, 0.25);
		results[1] = solve_kepler(2, 6.037831992006549, 0.25600674983752);
		results[2] = solve_kepler(3, 0.66985737, 0.96714);
		results[3] = solve_kepler(4, 6.259047404, 0.0167086);
		results[4] = solve_kepler(5, 0.25359634, 0.2488);
	}


	/**** Print Results ****/
	printf("Solve Kepler's Eq via simple iteration for test parameters...\n"); 
	printf("E = %f\n",VIP_DEC(results[0]));

	printf("Solve Kepler's Eq via Newton's method for SpaceX Tesla...\n"); 
	printf("E = %f\n",VIP_DEC(results[1]));

	printf("Solve Kepler's Eq via binary search for Haley's comet...\n"); 
	printf("E = %f\n",VIP_DEC(results[2]));

	printf("Solve Kepler's Eq via power series for Earth's orbit...\n"); 
	printf("E = %f\n",VIP_DEC(results[3]));

	printf("Solve Kepler's Eq via Fourier Bessel series for Pluto's orbit...\n"); 
	printf("E = %f\n",VIP_DEC(results[4]));

	return 0;
}



double 
bin_fact(int n, int k)
{
		int j;
		double cum_prod = 1.0;
		double num_fact,den_fact,dj,dk,x;

		x = ((double) n)/2.0 - (double)k;

		for(j=n-k;j>1;j--){
			dj = (double)j;
			dk = (double) n -(double)k - dj + 1.0;
			den_fact = n - k - j + 1 <= k ? dk*dj : dj;  
			num_fact = n - k - j + 1 <= k ? x*x : x; 
			cum_prod = cum_prod * (num_fact/den_fact);
		}
		return cum_prod;
}



/* The following routine calculates the Bessel function of the first kind 
   for an integer index. We just sum the series representation given by


                      __                     2j
	              \        j        (x/2)
J (x) = 1/n! (x/2)^n       (-1)   __________________
 n	              /__          j!(n+1)...(n+j)
		      j=0

   
See Special functions and their applications, N.N. Lebedev, Dover, 1972,
pp 95-142 for an introduction to Bessel functions and related cylinder
functions.
*/
#define MAXJITER    12

VIP_ENCDOUBLE J(int n, VIP_ENCDOUBLE x)
{
	VIP_ENCDOUBLE dsum=0.0,dterm,s_j,d_n,d_j,cfact=1.0;
	int j,nn;

	nn = n >= 0 ? n : -n;  /* Absolute value of n. Use the relation
                            J  (x) = (-1)^n J  (x) for negative n 
				    -n              n    */

	d_n = (double) nn;
	
	/* Calculate the common factor (x/2)^n/n! so it only has to be
           done once. */

	for(j=1;j<=nn;j++){
		d_j = (double)j;
		cfact = cfact * (x/((VIP_ENCDOUBLE)2.0*d_j));
	}

	/* j = 0 term: */
	dsum = dterm = cfact;

	j = 1;

	/**** IISWC DO Transformation: LOOP Conversion - LB ****/
	do {
		d_j = (double)j;
		s_j = j%2 ? -1.0: 1.0;
		dterm = dterm * (x*x/(d_j*4.0*(d_n + d_j)));
		dsum = dsum + (s_j*dterm);
		j++;
	} while( dterm > DBL_EPSILON );
  // fprintf(stderr, "j == %d\n", j);
		
	s_j = nn%2 ? -1.0 : 1.0;
	return  n >= 0 ? dsum : s_j*dsum;
}

#endif
