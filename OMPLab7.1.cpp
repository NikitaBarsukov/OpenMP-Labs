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
//�� ������ ������� ��� �� ������������������ ������� ���������� �����, �� 
//1. �� ��������� ���������� i;
//2. ��� �������� ������� ��������� ���������� � �������������� �������, � � ����� ������ y ������ ����� �������� ����, � x = i;
//3. �������� ������ � ����� ��������;
//4. ��� �� ������ ����� ����� ����� ���� ����� ���������� i, y, x.