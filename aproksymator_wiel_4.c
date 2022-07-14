#include "makespl.h"
#include "piv_ge_solver.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>


double potega(int wart_potegi, double x[],int n){
	double a;
	double k = 0;
	for(int j=0;j<n;j++){
		a=1;
		for(int i = 0;i<wart_potegi;i++)
			a*=x[j];
		k+=a;
	}
	return k;
}

double dlay(int wart_potegi,double y[],double x[],int n){
	double a;
	double k = 0;
	for(int i=0;i<n;i++){
		a=1;
		for(int j = 0;j<wart_potegi;j++)
			a*=x[i];
		k += y[i]*a;	
	}
	return k;
}

double funkcja(double *a, double x) {
	return a[4]*x*x*x*x+a[3]*x*x*x+a[2]*x*x+a[1]*x+a[0];
}

double dfunkcja(double *a, double x) {
	return a[4]*4*x*x*x+a[3]*3*x*x+a[2]*2*x+a[1];
}

double d2funkcja(double *a, double x) {
	return a[4]*12*x*x+a[3]*6*x+2*a[2];
}

double d3funkcja(double *a, double x) {
	return a[4]*24*x+a[3]*6;
}


void 
make_spl (points_t * pts, spline_t * spl) {

	matrix_t *eqs= NULL;
	double *x = pts->x;
	double *y = pts->y;
	double a = x[0];
	double b = x[pts->n - 1];
	int i, j, k, licz;
	int nb = pts->n - 3 > 10 ? 10 : pts->n - 3;
	char *nbEnv= getenv( "APPROX_BASE_SIZE");
	
	if ( nbEnv != NULL && atoi( nbEnv ) > 0 )
		nb = atoi( nbEnv );
	double *wsp=malloc(5*sizeof(wsp));
	double iksy[3000] = { 0 };
	double igreki[3000] = { 0 };
	double roz, pocz;
	eqs = make_matrix( 5, 6);
	
	if(alloc_spl(spl, nb)==0) {
	
	roz= (b-a)/(spl->n-1);

	for(k=0;k<nb;k++) {
		licz = 0;	
		double xx = spl->x[k] = a + k*roz;
		pocz = a - roz/2 + k*roz;
		xx+= 10.0*DBL_EPSILON;
		
		for(i=0;i<pts->n;i++) {
			if(x[i]>=pocz && x[i]<=pocz+roz) {
				/*iksy=realloc(iksy, (licz+1)*sizeof(double *));
				igreki=realloc(igreki, (licz+1)*sizeof(double *));*/
				iksy[licz]=x[i];
				igreki[licz]=y[i];
				licz++;
			}
		}

	for(i=0;i<5;i++) {
		for(j=0; j<5;j++) {
			put_entry_matrix( eqs, i, j, potega(i+j,iksy,licz));
		}
		put_entry_matrix( eqs, i, 5, dlay(i, igreki, iksy, licz));
	}

	if(piv_ge_solver(eqs)) {
		return;
	}	

	for(i=0;i<5;i++) {

			wsp[i]= get_entry_matrix (eqs, i, 5);
	}
	
		spl->f[k] =  funkcja(wsp,xx);  
		spl->f1[k] = dfunkcja(wsp,xx);
		spl->f2[k] = d2funkcja(wsp,xx); 
		spl->f3[k] = d3funkcja(wsp,xx);
			}
	}
	
	
}	



