#include <stdio.h>

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
int main(){
	double x[5] = {1,2,3,4,5};
	double y[5] = {10,11,12,13,14};
	int n=5;
	double k;
	double tabx[5][5];
	double taby[5][1];
	
	//Macierz X
	for(int i =0;i<5;i++){
		for(int j=0;j<5;j++){
			
			tabx[i][j]=potega(i+j,x,n);
		}
	}
	//Macierz Y
	for(int i=0;i<5;i++){
		taby[i][0]=dlay(i,y,x,n);
	}

	for(int i =0;i<5;i++){
		for(int j=0;j<5;j++){ 
			printf("%lf ",tabx[i][j]);
			}
		printf("\n");
	}
	printf("\n");
	
	for(int i =0;i<5;i++)
		printf("%lf ",taby[i][0]);
	printf("\n");

	return 0;
}
