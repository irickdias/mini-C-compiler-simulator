#include<stdio.h>

void alteraValores2(int x, int y, int *z, int *w)
{
 x = *z * *w;
 *z = x;
 y = *w + 15;
 *w = y;
}

void alteraValores1(int *a, int *b, int *c)
{
 *a = 2 * *a * 10;
 *b = 100 + 50 - *b;
 *c = *c + 1;
 *c = *c/8;
}

int main()
{
 int var1 = 25, var2 = 17, var3 = 31;
 
 printf("var1: %d\nvar2: %d\nvar3: %d\n\n", var1, var2, var3);
 printf("var1 + var2 = %d\nvar3 - var2 = %d\n\n", var1+var2, var3-var2);
 alteraValores1(&var1, &var2, &var3);
 printf("var1: %d\nvar2: %d\nvar3: %d\n\n", var1, var2, var3);
 var1 = 2;
 var2 = 4;
 var3 = 8;
 alteraValores2(var1, var2, &var1, &var2);
 printf("var1: %d\nvar2: %d\nvar3: %d\n", var1, var2, var3*2);
}
//
