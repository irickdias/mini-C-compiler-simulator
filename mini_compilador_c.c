#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include "meuconio.h"
#include "trabTad.h"
int main()
{
	

	Programa *P=NULL;
	int tot_lin=0, primeiro=1;
	
	cria_programa(&P, "programa1C.c", &tot_lin);
	cria_tela(tot_lin);
	simulacao(P, tot_lin, &primeiro);
	
	
	gotoxy(1, tot_lin+5);
	textbackground(0); // BLACK
	return 1;
}
