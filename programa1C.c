#include<stdio.h>

void Multiplica(int x, int y, int *r)
{
 *r= x*y;
}

void Soma(int x, int y, int *r)
{
 *r= x+y;
}

void Subtrai(int x, int y, int *r)
{
 *r= x-y;
}

void Divide(int x, int y, int *r)
{
 *r= x/y;
}

int main()
{
 int A=3,B=5, res, aux;
 
 res = 288;
 printf("Valor aleatorio: %d\n", res);
 res = 0;
 printf("Valores iniciais\n A=%d \n B=%d \n res=%d\n",A, B, res);
 Multiplica(A, B, &aux);
 res = aux;
 printf("Resultado da multiplicacao: %d\n", res);
 Subtrai(A+10, B, &aux);
 res = aux;
 printf("Resultado da subtracao: %d\n", res);
 Soma(A*2, B*2, &aux);
 res = aux;
 printf("Resultado da Soma: %d\n", res);
 Divide(A+9, B+1, &aux);
 res = aux;
 printf("Resultado da divisao: %d\n", res);
 
}
//
