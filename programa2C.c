#include<stdio.h>

void Dobro(int *x)
{
 *x = *x*2;
}

void Triplo(int *num)
{
 *num = *num*3;
}

void Soma(int i, int j, int *k)
{
 *k = i+j;
}

void FuncaoA(int *v1, int *v2, int *v3)
{
 Dobro(&*v1);
 printf("Dobro de A: %d\n", *v1);
 Triplo(&*v2);
 printf("Triplo de B: %d\n", *v2);
 Soma(*v1, *v2, &*v3);
}

int main()
{
 int A, B, C=0;
 A = 2;
 B = 4;
 printf("Valor de A: %d\tValor de B: %d\n", A, B);
 FuncaoA(&A, &B, &C);
 printf("Dobro de A + Triplo de B: %d\n", C);
}
//
