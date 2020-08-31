#include <stdio.h>
#include <math.h>
#include <omp.h>
#define N 1000

int main(int argc, char** argv)
{
	double a[N];
	double y, x;
	int i; 
	# pragma omp parallel for private(i, y, x) shared(a)
	for (i = 0; i < N; i++)
	{	
		y = i * sin((double) i / N * 3.14);
		x = i * cos((double) i / N * 3.14);
		a[i] = y + x;
	}
	for (i = 0; i < N; i++)
	{
		printf("%g\n", a[i]);
	}
	return 0;
}
//Ќе совсем пон€тно что за тригонометрическую формулу использует автор, но 
//1. Ќе объ€влена переменна€ i;
//2. ѕри заданном делении результат приводитс€ к целочисленному формату, и в таком случае y всегда будет равн€тс€ нулю, а x = i;
//3. –асшарил массив а между потоками;
//4. “ак же каждый поток будет иметь свои копии переменных i, y, x.