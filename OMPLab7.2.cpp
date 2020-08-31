//Вычислить прямое произведение множеств А1, А2, А3… Аn.Вход -
//ные данные : целое положительное число n, множества чисел А1, А2, А3…
//Аn, мощности множеств равны между собой и мощность каждого множества
//больше или равна 1. Количество потоков определяется, исходя из мощности
//множеств, и не является параметром задачи.
//

#include <stdio.h>
#include <queue>
#include <string>
#include <iostream>
#include <math.h>
#include <omp.h>
#include<time.h>

void decart(const int& n, const int& power, int** sets)
{
	#pragma omp parallel for schedule(static)
	for (int i = 0; i < n; i++) 
	{
		for (int ac = 0; ac < power; ac++)
		{
			for (int j = 0; j < n; j++) 
			{
				if (i != j)
				for (int k = 0; k < power; k++)
				{
					//std::cout << "(" << sets[i][ac] << "," << sets[j][k] << ")" << std::endl;
					std::cout << "Thread "+ std::to_string(omp_get_thread_num()) + " creates (" + std::to_string(sets[i][ac]) + "," + std::to_string(sets[j][k]) + ")" + "\n";
				}
			}
		}
	}
}

int** stressTest(unsigned n, unsigned power)
{
	srand(time(0));
	int** sets = 0;
	sets = new int*[n];
	for (int i = 0; i < n; i++)
	{	
		sets[i] = new int[power];
		for (int j = 0; j < power; j++)
		{
			sets[i][j] = rand();
		}
	}
	return sets;
}

void setThreadsNumber(const int& power)
{
	if (omp_get_max_threads() < power)
	{
		omp_set_num_threads((int)omp_get_max_threads);
	}
	else
	{
		omp_set_num_threads(4);
	}
}

int main(int argc, char** argv)
{
	const int power = 3;
	const int n = 100;
	//Пример того как хрантся множетсва чисел
	//int sets[n][power] = {
	//	{1,4},
	//	{2,5},
	//	{3,6}
	//};

	int** sets = stressTest(n, power);
	setThreadsNumber(power);
	decart(n, power, sets);
	return 0;
}