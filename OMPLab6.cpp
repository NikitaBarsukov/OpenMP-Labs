//Дана последовательность натуральных чисел{ a0…an–1 }. Создать
//OpenMP - приложение для вычисления выражения a0 - а1 + a2 - а3 + a4 - а5 + ...

#include<omp.h>
#include<stdio.h>

const int N = 100;
int A[N];  //последовательность чисел a0…a99

void fillArray(int* A) {
	for (int i = 0; i < N; i++) {
		A[i] = i;
	}
}

int main()
{
	int i, subresult;
	double sum = 0.0;
	fillArray(A);
	if (omp_get_max_threads() < 4)
	{
		omp_set_num_threads((int)omp_get_max_threads);
	}
	else
	{
		omp_set_num_threads(4);
	}
	//#pragma omp parallel for - используя фичи омп, декларируем паррлельный for
	//schedule(static, 25) - контроль того, каким образом поток будет брать кусочки массива к себе на исполнеине. В данном случае, все итерации будут циклически распределяться между потоками по 25 штук.
	//private(i, a2) - на протяжении исполнения, потоки будут иметь свою копию переменных i и a2.
	//shared(A) - массив А будет разделен между потоками (Все потоки будут иметь доступ к одной и той же области памяти).
	//reduction(+:sum) -  условие гарантирует безопасное выполнение операций редукции, те в конечном счете здесь окажется результат сложения всех потоков. 
	#pragma omp parallel for schedule(static, 25) private(i, subresult)  shared(A) reduction(+:sum)
	for (i = 1; i < N; i += 2)
	{
		subresult = A[i - 1] - A[i];
		sum = sum + subresult;
	}
	printf("sum = %f\n", sum);
	return(0);

}