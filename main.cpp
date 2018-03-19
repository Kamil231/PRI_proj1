#include <stdio.h>
#include <math.h>
//#include <limits>
#include <stdlib.h>

//funkcja obliczajaca potege algorytmem szybkiego potegowania, x - podstawa potegi, n - potega
long double potegowanie(long double x, int n) 
{
	if (n == 0)
		return 1;

	if (n % 2 == 1) 
		return x * potegowanie(x, n - 1);

	long double w = potegowanie(x, n / 2);
	return w * w;

}

//funkcja obliczajaca silnie rekurencyjnie
long long int silnia(int n)
{
	if (n == 0)
		return 1;
	else
		return(n * silnia(n - 1));
}

//funkcja przyjmujaca dokladnosc n, odrzuca liczby ujemne i inne niz ineger
int podaj_n(){
	char *w, q[100];
	int n = -1;
	int i = 0;
	printf("podaj n: \n");
	while (n < 0){
		while (fgets(q, sizeof(q), stdin)) {		// Wpisuje do q ciag znakow z klawiatury.
			n = strtol(q, &w, 10);					// Do n przekazuje int z ciagu znakow q, do w reszte.
			if (w == q || *w != '\n') {				// Jesli w ciagu znakow q nie bylo int to w == q, jesli pow wpisaniu inta wpisano cos innego niz enter to *w != '\n'
				if (i > 0 )
					printf("n musi byc calkowite, podaj n: \n");
			}
			else break;
			i++;
		}
		if (n < 0)
			printf("n musi byc dodatnie, podaj n: \n");
	}
	return n;
}

void main(){

	//long long int imax = std::numeric_limits<long long int>::max();	// maksymalna wartosc zmiennej typu long long int
	//double dmax = std::numeric_limits<double>::max();				// maksymalna wartosc zmiennej typu double

	long double x;						
	printf("podaj x: \n");
	scanf("%Lf", &x);

	int n;
	n = podaj_n();
	
	long double p;														// wartosc potegi
	long long int s;												// wartosc silni
	long double coshx = 0;												// wartosc ciagu

	for (int i = 0; i < n; i++){
		p = potegowanie(x, 2 * i + 1);
		s = silnia(2 * i + 1);
		coshx = coshx + (1. / s) * p;								// suma pod kreska ulamkowa, za petla csch zostanie odwrocone
		/*if (imax / (i + 1) < s || dmax / (2 * x) < p){				// sprawdza czy dla nastepnej petli nie zostanie przekrowczona max wartosc int lub double
			printf("W nastepnej iteracji przekroczona zostalaby maksymalna wartosc int lub double, koniec obliczen dla n = %d\n", i);
			break;
		}*/
	}

	coshx = 1 / coshx;

	long double coshxr = 2 / (exp(x) - exp(-x));							// csch rzeczywiste
	long double blad = ((coshx - coshxr) / coshxr)*100;					// blad w procentach

	printf("Wartosc cschx obliczona z ciagu: = %Lf \nWartosc rzeczywista cschx = %Lf \n", coshx, coshxr);
	printf("blad = %Lf %%\n", blad);

}
