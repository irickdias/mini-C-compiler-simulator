#include<string.h>

struct telasimu // tela do simulador
{
	int ult_lin;
	char ult_instrucao[100];
};
typedef struct telasimu TelaS;

struct endControle
{
	int end;
};
typedef struct endControle EndCon;

struct programa // Programa em c
{
	int pos_lin;
	char instrucao[100];
	struct programa *prox;
};
typedef struct programa Programa;


struct telapro // tela do programa em execução
{
	char print[100];
	struct printvalores *val;
	struct telapro *prox;
};
typedef struct telapro TelaP;

struct printvalores
{
	int valor;
	struct printvalores *prox;
};
typedef struct printvalores PrintVal ;

struct memoria // simulaçao da memoria durante o programa sendo executado
{
	int endereco, valor, flag_end;
	char variavel[20];
	struct memoria *prox;
};
typedef struct memoria Memoria;


// -------------------  Pilha ---------------------
//PILHA TIPO CHAR
struct pilhatipoc
{
	char c;
	struct pilhatipoc *prox;
};
typedef struct pilhatipoc PilhaTC;

//PILHA TIPO INT
struct pilhatipoi
{
	int valor;
	struct pilhatipoi *prox;
};
typedef struct pilhatipoi PilhaTI;

struct pilhasimulador
{
	TelaS simu;
	struct pilhasimulador *prox;
};
typedef struct pilhasimulador PilhaS;

struct pilhams // salva aonda estava a memoria quando chamou a função, vai ser utilizada na hora de excluir as caixinhas criada, na saida da função
{
	Memoria *memo;
	struct pilhams *prox;
};
typedef struct pilhams PilhaMS;


void InitTC(PilhaTC **P)
{
	//*P = (PilhaOP)malloc(sizeof(PilhaOP));
	*P = NULL;
}

void InitTI(PilhaTI **P)
{
	//*P = (PilhaOP)malloc(sizeof(PilhaOP));
	*P = NULL;
}

void InitS (PilhaS **P)
{
	*P = NULL;
}

void InitMS(PilhaMS **P)
{
	*P = NULL;
}


char isEmptyTC(PilhaTC *P)
{
	return P == NULL;
}

char isEmptyTI(PilhaTI *P)
{
	return P == NULL;
}

char isEmptyS (PilhaS *P)
{
	return P == NULL;
}

char isEmptyMS(PilhaMS *P)
{
	return P == NULL;
}


void PushTC(PilhaTC **P, char x)
{
	PilhaTC *novo;
	
	novo = (PilhaTC*)malloc(sizeof(PilhaTC));
	novo->c = x;
	novo->prox = NULL;
	
	if(isEmptyTC(*P))
		*P = novo;
	else
	{
		//aux = novo;
		novo->prox = *P;
		
		*P = novo;
	}
}

void PushTI(PilhaTI **P, int x)
{
	PilhaTI *novo;
	
	novo = (PilhaTI*)malloc(sizeof(PilhaTI));
	novo->valor = x;
	novo->prox = NULL;
	
	if(isEmptyTI(*P))
		*P = novo;
	else
	{
		//aux = novo;
		novo->prox = *P;
		
		*P = novo;
	}
}

void PushPS(PilhaS **P, TelaS telasimu)
{
	PilhaS *novo;
	novo = (PilhaS*)malloc(sizeof(PilhaS));
	novo->simu = telasimu;
	novo->prox = NULL;
	
	if(isEmptyS(*P))
		*P = novo;
	else
	{
		novo->prox = *P;
		
		*P = novo;
	}
}

void PushMS (PilhaMS **P, Memoria *m)
{
	PilhaMS *novo;
	novo = (PilhaMS*)malloc(sizeof(PilhaMS));
	novo->memo = m;
	novo->prox = NULL;
	
	if(isEmptyMS(*P))
		*P = novo;
	else
	{
		novo->prox=*P;
		*P=novo;
	}
}

char PopTC(PilhaTC **P)
{
	PilhaTC *aux;
	char ac;
	//valor=malloc(sizeof(valor)*10);
	
	if(isEmptyTC(*P))
		return '!';
	else
	{
		ac = (*P)->c;
		aux = *P;
		*P = aux->prox;
		free(aux);
		
		return ac;
	}
}

int PopTI(PilhaTI **P)
{
	PilhaTI *aux;
	int x;
	//valor=malloc(sizeof(valor)*10);
	
	if(isEmptyTI(*P))
		return -1;
	else
	{
		x = (*P)->valor;
		aux = *P;
		*P = aux->prox;
		free(aux);
		
		return x;
	}
}

TelaS PopPS(PilhaS **P)
{
	PilhaS *aux;
	TelaS ts;
	ts.ult_lin = 0;
	strcpy(ts.ult_instrucao, "");
	
	if(!isEmptyS(*P))
	{
		ts = (*P)->simu;
		aux = *P;
		*P = aux->prox;
		free(aux);
	}
	return ts;
}

Memoria* PopMS(PilhaMS **P)
{
	PilhaMS *aux;
	Memoria *m;
	if(isEmptyMS(*P))
		return NULL;
	else
	{
		m = (*P)->memo;
		aux = *P;
		*P = aux->prox;
		free(aux);
		
		return m;
	}
}


char TopTC(PilhaTC *P)
{
	return P->c;
}

int TopTI(PilhaTI *P)
{
	return P->valor;
}

// ------------------- FimPilha ------------------------

// ------------------- InicioFila ------------------------

struct filaparametro
{
	int valor;
	struct filaparametro *prox;
};
typedef struct filaparametro FilaPa;

void InitF(FilaPa **F)
{
	*F = NULL;
}


char isEmptyF(FilaPa *F)
{
	return F == NULL;
}

void Enqueue(FilaPa **F, int x)
{
	FilaPa *novo, *aux;
	novo = (FilaPa*)malloc(sizeof(FilaPa));
	novo->valor = x;
	novo->prox = NULL;
	
	if(isEmptyF(*F))
		*F = novo;
	else
	{
		aux = *F;
		while(aux->prox!=NULL)
			aux = aux->prox;
		
		
		aux->prox = novo;	
	}
	
}

int Dequeue(FilaPa **F)
{
	FilaPa *aux;
	int x;
	
	if(isEmptyF(*F))
		return -1;
	else
	{
		aux = *F;
		x = aux->valor;
		
		*F = aux->prox;
		free(aux);
		
		return x;
	}
	
}
// ------------------- FimFila ------------------------
void cria_tela(int tot_lin)
{
	
	
	int i, j, col, lin;
	
	// left side
	col=3;
	for(i=2; i<tot_lin+3; i++)
	{
		gotoxy(col, i);
		printf("%c", 179);
		
//		gotoxy(col+2, i);
//		for(j=col+2; j<79; j++)
//			printf(" ");
	}
	
	
	
	// right side
	col=80;
	for(i=2; i<tot_lin+3; i++)
	{
		gotoxy(col, i);
		printf("%c", 179);
	}
	
	//top
	lin=2;
	for(i=3; i<81; i++)
	{
		gotoxy(i, lin);
		printf("%c", 196);
	}
	
	//bottom
	lin=tot_lin+3;
	for(i=3; i<81; i++)
	{
		gotoxy(i, lin);
		printf("%c", 196);
	}
	
	gotoxy(3, 2);
	printf("%c", 218);
	gotoxy(3, tot_lin+3);
	printf("%c", 192);
	gotoxy(80, 2);
	printf("%c", 191);
	gotoxy(80, tot_lin+3);
	printf("%c", 217);
	
	gotoxy(15, 2);
	printf("%c", 180);
	printf("              ");
	gotoxy(30, 2);
	printf("%c", 195);
	
	
	
}

void tela_simulador(Programa *P, TelaS telasimu, int tot_lin)
{
	textbackground(0);
	clrscr();
	cria_tela(tot_lin);
	
	int i=3;
	
	while(P != NULL)
	{
		gotoxy(5, i);
		
		if(telasimu.ult_lin == i) // i é a posição na tela
		{
			textbackground(11);
			printf("%s\n", telasimu.ult_instrucao);
			textbackground(0);	
		}
		else
		{
			printf("%s\n", P->instrucao);
		}
		
		P=P->prox;
		i++;
	}
}

void mostra_memoria(Memoria *memo, int *tela_memoria, Programa *P, TelaS telasimu, int tot_lin)
{
	textbackground(0);
	clrscr();
	int i, k;
	
	if(*tela_memoria == 1)
	{
		for(i=3; i<27; i++) // top
		{
			gotoxy(i, 3);
			printf("%c", 196);
		}
		
		for(i=3; i<27; i++) // bottom
		{
			gotoxy(i, 5);
			printf("%c", 196);
		}
		
		for(i=3; i<6; i++) // left
		{
			gotoxy(3, i);
			printf("%c", 179);
		}
		
		for(i=3; i<6; i++) // right
		{
			gotoxy(27, i);
			printf("%c", 179);
		}
		
		// canto superior esquerdo
		gotoxy(3, 3);
		printf("%c", 218);
		
		// canto superior direito
		gotoxy(27, 3);
		printf("%c", 191);
		
		// canto inferior esquerdo
		gotoxy(3, 5);
		printf("%c", 192);
		
		// canto inferior direito
		gotoxy(27, 5);
		printf("%c", 217);
		
		gotoxy(5, 4);
		printf("&");
		
		gotoxy(8, 3);
		printf("%c", 194);
		gotoxy(8, 4);
		printf("%c", 179);
		//gotoxy(8, 5);
		//printf("%c", 193);
		
		gotoxy(10, 4);
		printf("Variavel");
		
		gotoxy(20, 3);
		printf("%c", 194);
		gotoxy(20, 4);
		printf("%c", 179);
		//gotoxy(20, 5);
		//printf("%c", 193);
		
		gotoxy(22, 4);
		printf("Valor");
		
		
		
		i=6;
		while(memo != NULL)
		{
			// ------------------- ajusta linha anterior ------------
			gotoxy(8, i-1);
			printf("%c", 197);
			gotoxy(20, i-1);
			printf("%c", 197);
			
			// canto inferior esquerdo
			gotoxy(3, i-1);
			printf("%c", 195);
			
			// canto inferior direito
			gotoxy(27, i-1);
			printf("%c", 180);
			// ------------------- fim ajusta linha anterior ------------
			
			// ***************************************************************************************
			
			//---------------- começa a por os valores na tela -------------------
			
			// pipe
			gotoxy(3, i);
			printf("%c", 179);
			
			// endereço
			gotoxy(4, i);
			printf("%d", memo->endereco);
			
			// pipe
			gotoxy(8, i);
			printf("%c", 179);
			
			// variavel
			gotoxy(11, i);
			printf("%s", memo->variavel);
			
			// pipe
			gotoxy(20, i);
			printf("%c", 179);
			
			// valor
			gotoxy(22, i);
			if(memo->flag_end == 1)
				printf("[%d]", memo->valor);
			else
				printf("%d", memo->valor);
			
			// pipe
			gotoxy(27, i);
			printf("%c", 179);
			
			// ----------------- termina de colocar os valores --------------------
			
			
			
			for(k=3 ; k<27; k++)
			{
				gotoxy(k, i+1);
				printf("%c", 196);
			}
			
			// canto inferior esquerdo
			gotoxy(3, i+1);
			printf("%c", 192);
			
			// canto inferior direito
			gotoxy(27, i+1);
			printf("%c", 217);
			
			i=i+2;
			memo = memo->prox;
		}
		// ajusta linha anterior pela ULTIMA vez
		gotoxy(8, i-1);
		printf("%c", 193);
		gotoxy(20, i-1);
		printf("%c", 193);
		
	}
	else
	{
		tela_simulador(P, telasimu, tot_lin);
		gotoxy(4, tot_lin+4);
		printf("F6 - Sair\t");
		//printf("F7 - Abrir\t");
		printf("F8 - Executar\t");
		printf("F9 - Memoria\t");
		printf("F10 - Tela");
	}
		
	
	
	
	
}

void mostra_tela_programa(TelaP *tela, int *tela_programa, Programa *P, TelaS telasimu, int tot_lin)
{
	TelaP *aux;
	PrintVal *val;
	int i, k, particionou=0;
	char strSep[50];
	
	textbackground(0);
	clrscr();
	gotoxy(1,1);
	
	if(*tela_programa == 1)
	{
		if(tela != NULL)
		{
			aux=tela;
			val=aux->val;
			i=0;
			//k=0;
			//particionou=0;
			
			while(aux!=NULL) // repetição para ir até o final da lista
			{
				k=0; i=0; 
				val=aux->val;
				while(k<strlen(aux->print)-1) // repetição para ir até o ultimo caracter do que precisa ser printado
				{
					particionou=0;
					if(aux->print[k] != '\\')
						strSep[i]=aux->print[k];
					
					if(aux->print[k] == '\\')
					{
						strSep[i]='\0';
						printf(strSep); // printa antes todo o conteudo copiado
						strcpy(strSep, "");
						
						i=0;
						strSep[i]=aux->print[k]; // posicao 0 do strSep recebe o '\'
						
						i++;
						k++;
						strSep[i]=aux->print[k]; // pode ser \n, \t
						
						i++;
						strSep[i]='\0';
						if(strcmp(strSep, "\\n")==0)
							printf("\n");
						if(strcmp(strSep, "\\t")==0)
							printf("\t");
						
						particionou=1;
						strcpy(strSep, "");
						i=0;
						k++; // pula o n ou t
					}
						
					
					
					if(aux->print[k] == '%')
					{
						
						//printf(strSep); // printa tudo o que ja tinha antes
						//reinicia strSep
						//strcpy(strSep, "");
						
						i++; // aumenta um posição para n afetar a antiga posição
						k++;
						while(aux->print[k] != ' ' && aux->print[k] != '\\' && k<strlen(aux->print)) //pegar qual o tipo do %... %d , %1.f
						{
							strSep[i]=aux->print[k];
							i++;
							k++;
						}
							
						
						strSep[i]='\0';
						
						//if(strcmp(strSep, "%d")==0)
							printf(strSep, val->valor);
						//else
						//	printf("s");
						
						particionou=1;
						val = val->prox;
						
						// reinicia variaveis
						i=0;
						//k--; // senão irá pular um caracter, já qque mais a baixo o k é incrementado de novo
						strcpy(strSep, "");
					}
					
					if(!particionou)
					{
						i++;
						k++;
					}
					
				}
				
				
				
				aux=aux->prox;
			}
		}
		
	}
	else
	{
		tela_simulador(P, telasimu, tot_lin);
		gotoxy(4, tot_lin+4);
		printf("F6 - Sair\t");
		//printf("F7 - Abrir\t");
		printf("F8 - Executar\t");
		printf("F9 - Memoria\t");
		printf("F10 - Tela");
	}
		
}

Programa *cria_caixa_programa()
{
	Programa *novo;
	novo=(Programa*)malloc(sizeof(Programa));
	novo->pos_lin=0;
	strcpy(novo->instrucao, "");
	novo->prox=NULL;
	
	return novo;
}

Memoria *cria_caixa_memoria(EndCon *endcon)
{
	Memoria *novo = (Memoria*) malloc(sizeof(Memoria));
	novo->endereco = (*endcon).end;
	strcpy(novo->variavel, "NULL");
	novo->valor = -1;
	novo->flag_end = 0;
	novo->prox=NULL;
	
	// muda o novo endereço disponivel na memoria (EndCon)
	(*endcon).end=(*endcon).end+4;
	
	return novo;
}

TelaP *cria_caixa_print()
{
	TelaP *novo = (TelaP*)malloc(sizeof(TelaP));
	strcpy(novo->print, "\0");
	novo->val = NULL;
	novo->prox = NULL;
	
	return novo;
} 


void cria_programa(Programa **P, char arquivo[], int *tot_lin)
{
	FILE *Arq = fopen(arquivo, "r");
	Programa *novo, *aux;
	int pos_lin=3, pos_col=5;
	char instrucao[100];
	if(Arq==NULL)
		printf("Arquivo não existe!\n\n");
	else
	{
		fflush(stdin);
		fscanf(Arq, "%[^\n]\n", instrucao); // pega tudo até o \n
		while(!feof(Arq))
		{
			
			
			if(*P==NULL) // Primeira caixa a ser inserida
			{
				*P = cria_caixa_programa();
				(*P)->pos_lin=pos_lin;
				strcpy((*P)->instrucao, instrucao);
				aux=*P;
			}
			else // já foi inserida a primeira
			{
				novo = cria_caixa_programa();
				novo->pos_lin=pos_lin;
				strcpy(novo->instrucao, instrucao);
				
				aux->prox=novo; // caixa de tras aponta para o novo
				
				aux=novo; // aux agora aponta para a ultima caixa inserida
			}
			
			gotoxy(pos_col, pos_lin);
			printf("%s\n", aux->instrucao);
			
			*tot_lin+=1;
			pos_lin++;
			
			fflush(stdin);
			fscanf(Arq, "%[^\n]\n", instrucao);
		}
	}
	
	fclose(Arq);
	//tela_simulador( *P, *tot_lin);
}

void proxima_linha(Programa *cab, Programa **exe, TelaS *tela_s, PilhaS **PS)
{
	Programa *aux;
	TelaS tsAux;
	char instrucaoAux[100];
	int i, diferenca;
	aux = (*exe)->prox;
	
	
	
	strcpy(instrucaoAux, aux->instrucao);
	diferenca = 75 - strlen(aux->instrucao); // diferença para poder concatenar com espaços, para preencher o fundo... pegando a linha toda dentro do simulador
	
	for(i=0; i<diferenca-1; i++)
		strcat(instrucaoAux, " ");
	
	gotoxy(5, aux->pos_lin);
	textbackground(11);
	printf("%s", instrucaoAux);
	
	*exe=aux;
		
	(*tela_s).ult_lin = aux->pos_lin;
	strcpy((*tela_s).ult_instrucao, instrucaoAux);
		
	//*ult_lin = aux; // guarda a caixa da informacao atual, para ser executada quando sair da linha
	
}

int procura_valor(Memoria *memo, char var[]) // devolve valor em inteiro ... faz atoi()
{
	Memoria *aux, *atual;
	int i, k, end;
	char auxEnd[20];
	
	aux = memo;
	while(aux != NULL && strcmp(var, aux->variavel)!=0)
		aux = aux->prox;
	
	if(aux == NULL) // chegou ao final da lista e não achou variavel correspondente
		return -1;
	else
	 // achou variavel
	if(aux->flag_end == 1) // a variavel tem um valor que é um endereço para uma outra variavel
	{
		//valor_flag = 0; // se 1, é valor
		while(aux->flag_end == 1)
		{
			//aux = aux->prox;
			/*k = 1;
			strcpy(auxEnd, "\0");
			for(i=0; i<strlen(aux->valor)-2; i++)
			{
				auxEnd[i] = aux->valor[k];
				k++;
			}
			auxEnd[i] = '\0';*/
			
			//end = atoi(auxEnd);
			
			
			// end recebe o valor(endereço) da atual variavel
			end = aux-> valor;
			
			// faz busca pelo endereço
			aux = memo;
			while(aux != NULL && end != aux->endereco)
				aux = aux->prox;
			// as caixas da memoria sempre atribuem um endereço existente, então nunca vai chegar em NULL
			
		}
		// quando sair do laço, é porque passou por todos os endereço e chegou a variavel com valor
		
		// pode ser que precise tratar valores ainda em NULL
		
		return aux->valor;
		
		
	}
	else // é valor
		return aux->valor;
	
}

int procura_endereco(Memoria *memo, char var[]) // devolve endereco simulado da memoria
{
	Memoria *aux;
	
	aux = memo;
	while(aux != NULL && strcmp(var, aux->variavel)!=0)
		aux = aux->prox;
		
	if(aux == NULL)
		return -1;
	else
	 	return aux->endereco;
}

Memoria* procura_variavel(Memoria *memoCab, char var[]) // devolve endereço da caixa da lista
{
	Memoria *aux, *aux2;
	
	aux = memoCab;
	while(aux != NULL && strcmp(aux->variavel, var)!=0)
		aux = aux->prox;
	
	// acho o endereco atribuido de quem chamou a função, e sei que o flag_end é 1
	
	
	// fazer um laço até achar flag_end = 0
	aux2 = aux;
	while (aux2 != NULL && aux2->flag_end != 0)
	{
		aux = memoCab;
		while(aux != NULL && aux->endereco != aux2->valor)
			aux = aux->prox;
		
		if(aux == NULL)
			aux2 = NULL;
		else
			aux2 = aux;
	}
	
	return aux2;
}

int operacao(Memoria *memo, char infixa[])
{
	PilhaTI *P;
	PilhaTC *Temp;
	int i, k, valor, operador=0, resetou, ope2, ope1, res;
	char var[20], c;
	
	
	InitTI(&P);
	InitTC(&Temp);
	
	// verificacao para ver se o primeiro caracter da string infixa é '*', se for é pq é uma variavel com referencia passada por parametro
	//if(infixa[0] == '*')
	//	endereco = 1;
	
	i=0;
	k=0;
	while (i < strlen(infixa))
	{
		resetou=0;
		// tirar espacos
		while(i<strlen(infixa) && infixa[i] == ' ')
			i++;
		
		//if(infixa[i] == '*') // é indicação de referencia
		//{
		//	var[k]=infixa[i];
		//	k++;
		//}
		
		
		if(infixa[i] == '*' || infixa[i] == '/')
		{
			var[k] = '\0';
			valor = atoi(var);
			if(valor == 0 )
				valor = procura_valor(memo, var);
			
			PushTI(&P, valor);
			strcpy(var, "");
			k=0; resetou = 1;
			
			
			//c = TopTC(Temp);
			if(isEmptyTC(Temp))
				PushTC(&Temp, infixa[i]);
			else
			{
				if(TopTC(Temp) == '+' || TopTC(Temp) == '-') // tem prioridade, entao empilha
					PushTC(&Temp, infixa[i]);
				else //  precisa resolver o que está em pilha de operadores (Temp)
				{
					ope2 = PopTI(&P);
					ope1 = PopTI(&P);
					
					if(TopTC(Temp) == '*') // faz multiplcacao
						res = ope1 * ope2;
					else
					if(TopTC(Temp) == '/') // faz divisao
						res = ope1 / ope2;
					
					PushTI(&P, res);
					PopTC(&Temp);
					PushTC(&Temp, infixa[i]);
				}
			}
		}
		else
		if(infixa[i] == '+' || infixa[i] == '-') // vai só resolver, nao empilha
		{
			var[k] = '\0';
			valor = atoi(var);
			if(valor == 0 )
				valor = procura_valor(memo, var);
			
			PushTI(&P, valor);
			strcpy(var, "");
			k=0; resetou = 1;
			
			if(isEmptyTC(Temp)) // tem prioridade, entao empilha
				PushTC(&Temp, infixa[i]);
			else
			{
				ope2 = PopTI(&P);
				ope1 = PopTI(&P);
				if(TopTC(Temp) == '*') //  faz multiplcacao
					res = ope1 * ope2;
				else
				if(TopTC(Temp) == '/') // faz divisao
					res = ope1 / ope2;
				else
				if(TopTC(Temp) == '+') // faz adicao
					res = ope1 + ope2;
				else
				if(TopTC(Temp) == '-') // faz subtracao
					res = ope1 - ope2;
				
				PushTI(&P, res);
				PopTC(&Temp);
				PushTC(&Temp, infixa[i]);
			}
			
			
		}
		else
		if(i == strlen(infixa)-1) //  esta na ultima posicao do vetor de caracter, vai ter uma ultima operacao a ser realizada
		{
			// coloca na pilha pela ultima vez
			var[k] = infixa[i]; k++;
			var[k] = '\0';
			valor = atoi(var);
			if(valor == 0 )
				valor = procura_valor(memo, var);
			
			PushTI(&P, valor);
			
			while(!isEmptyTC(Temp))
			{
				ope2 = PopTI(&P);
				ope1 = PopTI(&P);
				if(TopTC(Temp) == '*') //  faz multiplcacao
					res = ope1 * ope2;
				else
				if(TopTC(Temp) == '/') // faz divisao
					res = ope1 / ope2;
				else
				if(TopTC(Temp) == '+') // faz adicao
					res = ope1 + ope2;
				else
				if(TopTC(Temp) == '-') // faz subtracao
					res = ope1 - ope2;
				
				PushTI(&P, res);
				PopTC(&Temp);
			}
			res = PopTI(&P); // retira o ultimo valor da pilha, este será o resultado final
			
			// res será o valor a ser retornado
		}
		else
			var[k] = infixa[i];
		
		if(!resetou)
			k++;
		i++;
	}
	// fim laco
	// terminou de processar a expressão inteira
	
	/*while(!isEmpty(Temp))
	{
		c = TopTC(Temp);
		if(c == '*')
		{
			ope2 = Pop(&P);
			ope1 = Pop(&P);
			res = ope1 * ope2;
			
			PushTI(&P, res);
			PopTC(&Temp);
		}
		else
		if(c == '/')
		{
			ope2 = Pop(&P);
			ope1 = Pop(&P);
			res = ope1 / ope2;
			
			PushTI(&P, res);
			PopTC(&Temp);
		}
		else
		if(c == '+')
		{
			ope2 = Pop(&P);
			ope1 = Pop(&P);
			res = ope1 + ope2;
			
			PushTI(&P, res);
			PopTC(&Temp);
		}
		else
		{
			ope2 = Pop(&P);
			ope1 = Pop(&P);
			res = ope1 - ope2;
			
			PushTI(&P, res);
			PopTC(&Temp);
		}
	}*/
	
	
	return res;
}

void print_sit(TelaP **telapCab, TelaP **telapAtual, Memoria *memoCab, char instrucao[]) // print_situação
{
	TelaP *novoP; // novo printf
	PrintVal *novoV, *auxV; // novo valor do printf e auxiliar
	int i, pos, ope=0, asterisco=0, numero=0, letra=0;
	char strSep[50], conteudo[50], variaveis[20][10];
	
	novoP = cria_caixa_print();
	if(*telapCab == NULL) // vazia
		*telapCab = *telapAtual = novoP;
	else
	{
		(*telapAtual)->prox = novoP;
		
		//atualiza telapAtual
		*telapAtual = novoP;
	}
		
	
	
	// procura posição da primeira aspas =  inicio do conteudo a ser printado
	i=0;
	do
	{
		i++;
	} while(instrucao[i] != '"'); // " ou usar valor decimal...
	
	pos=i+1; // vai começar de uma posição a mais de onde está a aspas... EX: printf([i][pos] \n exempl"); -- onde [i] é ' " '
	i=0; // vai ser usado de índice para strSep
	while(instrucao[pos] != '"') // vai pegar apenas o conteudo dentro das aspas
	{
		strSep[i] = instrucao[pos];
		i++;
		pos++;
	}
	strSep[i]='\0';
	
	strcpy(conteudo, strSep); // copia para conteudo
	strcpy(novoP->print, conteudo);
	
	// strcpy(novoP->print, strSep);
	// reinicia variaveis
	//strcpy(strSep, "\0");
	//i=0;
	
	//acha a proxima virgula
	i=pos+1;
	while(instrucao[i] != ',')
		i++;
		
	
	//------------ reinicia variaveis-----------
	
	strcpy(strSep, "");
	
	// incrementa pos, pois está parado na aspas de fechamento
	pos=i+1;
	i=0;
	while(instrucao[pos]!= ';')
	{
		
		while(instrucao[pos] != ',' && instrucao[pos]!= ')')
		{
			if(instrucao[pos] != ' ')
			{
				strSep[i] = instrucao[pos];
				i++;
			}
			
			if(i == 1 && instrucao[pos] == '*' || instrucao[pos] == '*' && (strSep[i-2] == '+' || strSep[i-2] == '-' || strSep[i-2] == '*' || strSep[i-2] == '/'))
			{
				i--;
				strSep[i] = '\0';
			}
			
			if(instrucao[pos] >= '0' && instrucao[pos] <= '9')
				numero=1;
			
			if(instrucao[pos] > '9')
				letra=1;
			
			if(i!=1 && (instrucao[pos] == '+' || instrucao[pos] == '-' || instrucao[pos] == '*' || instrucao[pos] == '/'))
				ope=1;
				
			//if(instrucao[pos] == '*')
			//	asterisco=1;
			
			pos++;
		}
		strSep[i]='\0';
		
		//if(asterisco)
		//{
		//	
		//}
		//else
		
		// cria caixa de novo valor
		novoV = (PrintVal*)malloc(sizeof(PrintVal)); 
		//novoV->valor = procura_valor(memoCab, strSep); //e devolve valor dessa variavel
		novoV->prox=NULL;
		
		if(numero==1 && ope==0 && letra==0)
			novoV->valor = atoi(strSep);
		else
		if(ope==1)
			novoV->valor = operacao(memoCab, strSep);
		else
			novoV->valor = procura_valor(memoCab, strSep); //e devolve valor dessa variavel
		
		// ajusta ponteiros da lista de valores
		if(novoP->val == NULL)
			novoP->val = auxV = novoV;
		else
		{
			auxV->prox = novoV;
			
			// atualiza auxV
			auxV = novoV;
		}
		
		// reinicia as variaveis
		strcpy(strSep, "\0");
		i = ope = letra = numero = 0;
		
		pos++; // aumenta uma posição, pois está para do em virgula
	}
	
	
	
}


void atribuicao(Memoria **memoCab, Memoria **memoAtual, EndCon *endcon, char instrucao[], int chamada) // chamada = 1 = não veio peça declaracao; // chamada = 2 = veio pela declaracao;
{
	Memoria *novo, *aux, *shadowAux;
	int i, j, operador=0, res, valor, flag_var=0, endereco=0, numero, letra;
	char strSep[20], variavel[20];
	
	//strcpy(strSep, instrucao);
	strcpy(strSep, "");
	strcpy(variavel, "");
	i=j=numero=letra=0;
	while(i < strlen(instrucao)) // vai passar caracter por caracter até o ponto-virgula
	{
		
		
		if(instrucao[i] != '=' && instrucao[i] != ' ' && instrucao[i] != ';')
		{
			
			strSep[j] = instrucao[i];
			j++;
		}
		
		/*if(flag_var == 0 && instrucao[i] == '*')
		{
			j--;
			strSep[j] = '\0';
			endereco = 1;
			// j vai voltar pra zero aqui
		}*/
		
		if(j == 1 && instrucao[i] == '*' || instrucao[i] == '*' && (strSep[j-2] == '+' || strSep[j-2] == '-' || strSep[j-2] == '*' || strSep[j-2] == '/'))
		{
			j--;
			strSep[j] = '\0';
			
			if(flag_var == 0)
				endereco = 1;
			// j vai voltar pra zero aqui
		}
		
		
		if(instrucao[i] >= '0' && instrucao[i] <= '9')
			numero=1;
		
		if(instrucao[i] > '9' && instrucao[i]!=';')
			letra=1;
		
		if(instrucao[i] == '=') // não vai copiar para strSep
		{
			// strSep tem apenas o nome da variavel
			strSep[j]= '\0';
			strcpy(variavel, strSep);
			
			// "zera" a string, e agora todo o resto até o final será o valor
			strcpy(strSep, "");
			j=numero=letra=0;
			
			// variavel = 0 = ainda nao pegou variavel ...... variavel = 1 = já pegou variavel
			flag_var = 1;
			//endereco = 1;
		}
		
		if(flag_var == 1 && (instrucao[i] == '+' || instrucao[i] == '-' || instrucao[i] == '*' || instrucao[i] == '/'))
			operador=1;
		
		
		//if(flag_var == 0 && instrucao[i] == '*')
		//	endereco = 1;
			
		i++;
	}
	// quando sair do laço, strSep terá o valor a ser atribuido
	
	strSep[j]= '\0';
	
	if(operador)
		valor = operacao(*memoCab, strSep);
	else
	if(numero==1 && letra==0)
		valor = atoi(strSep);
	else
		valor = procura_valor(*memoCab, strSep);
	
	// agora temos a variavel e o seu valor a ser atribuido
	
	
	if(*memoCab == NULL && chamada==2) //  memoria ainda vazia, foi chamada pela função "declaracao"
	{
		novo = cria_caixa_memoria(&*endcon);
		strcpy(novo->variavel, variavel);
		novo->valor = valor;
		
		*memoCab = *memoAtual = novo;
		
	}
	else // então faz uma busca
	{
		//aux=*memoCab;
		//shadowAux= aux->prox;
		
		if(endereco == 1)
		{
			aux = procura_variavel(*memoCab, variavel);
		}
		else
		{
			aux=*memoCab;
			while(aux != NULL && strcmp(aux->variavel, variavel)!=0)
			{
				//shadowAux = aux;
				aux = aux->prox;
			}
		}
		
			
		
		if (aux == NULL && chamada==1) // chegou ao final e não achou nada e não veio pela funcao declaracao
		{ 
			// situação de que está tentando atribuir um valor a uma variavel que n foi declarada
			// msg de erro, pois nãoa achou a variavel na memoria
			
		}
		else
		if(aux == NULL && chamada==2) // veio da função "declaracao"
		{
			// nesse caso, ele irá criar ma caixa nova
			novo = cria_caixa_memoria(&*endcon);
			strcpy(novo->variavel, variavel);
			novo->valor = valor;
			
			(*memoAtual)->prox = novo; // *memoAtual guarda a ultima caixa inserida na memoria
			*memoAtual = novo;
		}
		else 
		if(aux != NULL && chamada==2) // achou a varivael, porem veio pela função "declaracao"... nesse caso, vai substituir o valor desta variavel;
		{
			aux->valor = valor;
		}
		else // achou e não veio pela função "declaracao"
		{
			aux->valor = valor;
		}
		
	}
}

void declaracao(Memoria **memoCab, Memoria **memoAtual, EndCon *endcon, char tipo[], char instrucao[])
{
	Memoria *novo;
	int i, j, atri;
	char strSep[50];
	
	
	i=strlen(tipo)+1;
	while(i<strlen(instrucao)-1)
	{
		j = atri = 0;
		strcpy(strSep, "");
		while(instrucao[i]!= ',' && instrucao[i]!=';')
		{
			if(instrucao[i]!=' ')
			{
				strSep[j]=instrucao[i];
				j++;
			}
				
			
			if(instrucao[i]=='=')
				atri=1;
			
			i++;
			
		}
		strSep[j]='\0';
		if(atri)
		{
			atribuicao(&*memoCab, &*memoAtual, &*endcon, strSep, 2);
		}	
		else
		{
			novo = cria_caixa_memoria(&*endcon);
			strcpy(novo->variavel, strSep);
			
			
			// Acerta ponteiros da lista memoria
			if(*memoCab ==  NULL)
				*memoCab = *memoAtual = novo;
			else
			{
				(*memoAtual)->prox = novo;
				*memoAtual = novo;
			}
		}
		
		i++;
	}
}

void chamada_funcao(Programa *P, Programa **exe, Memoria *memoCab, Memoria **memoAtual, EndCon *endcon, TelaS *tela_s, char nome_funcao[], char instrucao[])
{
	Programa *aux, *fun_inst, *fun_ini;
	Memoria *novo;
	PilhaTI *Temp, *Main;
	FilaPa *F;
	int achou = 0, i, j, valores, endereco = 0, asterisco, primeiro, numero, operador, letra;
	char *part, strSep[20], fun[50], strAux[50];
	aux = P;
	
	InitF(&F);
	// encontra onde começa a função no programa
	while(aux != NULL && achou==0)
	{
		// divide a string pelo '(' ..... primeira posicao vai ser o tipo da função
		//part = strtok(aux->instrucao, " (");
		// segunda posicao irá ser o nome da função, que é o que interessa
		//part = strtok(NULL, " (");
		i = j = 0;
		while(i< strlen(aux->instrucao) && aux->instrucao[i] != '(')
		{
			
			fun[j] = aux->instrucao[i];
			j++;

			if(aux->instrucao[i] == ' ')
			{
				// ignora tudo o que ja tinha antes e reseta as variaveis
				strcpy(fun, "");
				j=0;
			}
			
			i++;
		}
		fun[j]='\0';
		
		if(strcmp(fun, nome_funcao)==0)
		{
			achou=1;
			fun_inst = aux;
		}
			
		
		aux = aux->prox;
	}
	
	
	// verifica se achou a função ou não
	
	if(aux == NULL)
		printf("erro");
	else
	{
		// instrucao tem a instrucao de chamada com as passagens de parametros EX: calcula(a, b, &c);
		// fun_inst tem a instrucao da chamada com as referencias dos parametros  EX: void calcula(int x, int y, int *z)
		// achou a função
		//part = 
		
		
		
		// laço para enfileirar os valores da passagem de parametros
		i = j = endereco = operador = numero = letra = 0;
		while (i < strlen(instrucao))
		{
			if(instrucao[i]!=' ' && instrucao[i]!=',' && instrucao[i]!='&' && instrucao[i]!=')')
			{
				strSep[j] = instrucao[i];
				j++;
			}
			
			//idéia:  fazer contagem de asteristicos... se for 1 e ela estiver na strSep[0], nao é uma operacao
			
			// condição para tirar '*' que não seja de operacao
			// 3 situações:
			// a) - instrucao[i] == '*' e uma a instrucao[i-1] , ou seja uma posição atras, for == '&' ( &* ) 
			// b) - instrucao[i] == '*' e j ainda é zero, quer dizer que é o primeiro caracter que irá pegar e não é operação
			// c) - é uma operacao e encontrou um operador, seguido de *
			
			if(instrucao[i]=='*' && instrucao[i-1]=='&' || j==1 && instrucao[i]=='*' || instrucao[i]=='*' && (strSep[j-2] == '+' || strSep[j-2] == '-' || strSep[j-2] == '*' || strSep[j-2] == '/'))
			{
				// tira da string  e posiciona na posição de trás
				j--;
				strSep[j] = '\0';
			}
			
			if(instrucao[i]=='&') 
				endereco=1;
			
			if(j!=1 && endereco!=1 && (instrucao[i] == '+' || instrucao[i] == '-' || instrucao[i] == '*' || instrucao[i] == '/'))
				operador = 1;
			
			if(instrucao[i]>= '0' && instrucao[i]<='9')
				numero=1;
			
			if(instrucao[i]>'9')
				letra = 1;
			
			if(instrucao[i]=='(')
			{
				//reinicia strSep, pois o tudo antes do abre parenteses não importa
				strcpy(strSep, "");
				j=0;
				letra=0;
			}
			
			if(instrucao[i]==',' || instrucao[i]==')')
			{
				// enfileira primeiro, depois reinicia a variavel strSep
				strSep[j]='\0';
				
				if(numero == 1 && operador == 0 && letra==0)
					Enqueue(&F, atoi(strSep));
				else
				if(operador == 1)
					Enqueue(&F, operacao(memoCab, strSep));
				else
				if(!endereco)
					Enqueue(&F, procura_valor(memoCab, strSep));
				else
					Enqueue(&F, procura_endereco(memoCab, strSep));
				
				// reinicia variaveis
				strcpy(strSep, "");
				j = endereco = operador = numero = letra = 0;
				
			}
			
			
			
			i++;
		}
		
		
		
		strcpy(strAux, fun_inst->instrucao);
		part = strtok(strAux, "(,)");
		asterisco = endereco = 0;
		primeiro = 1;
		strcpy(strSep, "");
		while(part)
		{
			if(!primeiro) // primera vez será "void calcula", isso não interessa
			{
				i = j = 0;
				while(i < strlen(part))
				{
					if(part[i] != ' ' && part[i] != '*')
					{
						strSep[j] = part[i];
						j++;
					}
					
					
					if(part[i] == '*')
						asterisco = 1;
					
					if(part[i+1] == ' ')
					{
						strSep[j] = '\0';
						//strcpy(tipo, strSep);
						
						// reinicia
						strcpy(strSep, "");
						j=0;
					}
					
					
					i++;	
				}
				
				strSep[j] = '\0';
				if(!isEmptyF(F))
				{
					novo = cria_caixa_memoria(&*endcon);
					novo->valor = Dequeue(&F);
					strcpy(novo->variavel, strSep);
					if(asterisco)
						novo->flag_end=1;
					
					(*memoAtual)->prox = novo;
					*memoAtual = novo;
					
				}
				else
				{
					// erro no quantidade de parametros está errada
				}
				
				// reinicia variveis na saida
				strcpy(strSep, "");
				j=0;
				asterisco = 0;
				
				
				//part = strtok(fun_inst->instrucao, "(,)");
			}
			
			primeiro = 0;
			part = strtok(NULL, "(,)");
		}
		
		
		// terminou de atribuir as passagens de parametros
		// laço para procurar a primeira linha executavel da função
		aux = fun_inst;
		while(aux != NULL && strcmp(aux->instrucao, "") == 0 && strcmp(aux->instrucao, "{") != 0)
			aux = aux->prox;
		
		(*tela_s).ult_lin = aux->pos_lin;
		strcpy((*tela_s).ult_instrucao, aux->instrucao);
		
		*exe=aux->prox;
	}
	
	
	
}

void executa_linha(Programa *P, Programa **exe, Memoria **memoCab, Memoria **memoAtual, TelaP **telapCab, TelaP **telapAtual, EndCon *endcon, TelaS *tela_s, PilhaS **PS, PilhaMS **MS)
{
	Programa *aux;
	Memoria *auxM, *antM, *auxM2;
	TelaS tsAux;
	int i, descobriu;
	char strAux[100], strSep[50]; // strAuxiliar e strSeparada
	
	strcpy(strAux, (*exe)->instrucao); // copia a instrucao para uma string auxiliar, para poder ser manipulada
	
	descobriu = i = 0;
	while(descobriu==0 && i<strlen(strAux))
	{
		strSep[i] = strAux[i];
		strSep[i+1] = '\0';
		if(strcmp(strSep, "int")==0 || strcmp(strSep, "float")==0) // é declaração
		{
			descobriu=1;
			declaracao(&*memoCab, &*memoAtual, &*endcon, strSep, strAux);
		}
		else
		if(strAux[i+1] == '(') // pode ser uma chamada de função ou um printf
		{
			
			
			if(strcmp(strSep, "printf")==0) // é printf
			{
				descobriu=1;
				print_sit(&*telapCab, &*telapAtual, *memoCab, strAux);
			}
			else // é chamada de função
			{
				PushPS(&*PS, *tela_s);
				PushMS(&*MS, *memoAtual);
				chamada_funcao(P, &*exe, *memoCab, &*memoAtual, &*endcon, &*tela_s, strSep, strAux);
				//PushPE(&*PE, *exe);
				descobriu=1;
			}
		}
		else
		if(strAux[i+1] == '=') // é atribuição
		{
			descobriu=1;
			atribuicao(&*memoCab, &*memoAtual, &*endcon, strAux, 1); // manda a instrução inteira (strAux)
		}
		else
		if(strAux[i] == '}')
		{
			tsAux = PopPS(&*PS);
		
			aux = P;
			while(aux != NULL && aux->pos_lin != tsAux.ult_lin)
				aux = aux->prox;
			
			
			
			//atualiza linha em execução
			*exe=aux;
			
			// excluir caixas que foram criada para a chamada de função
			antM  = PopMS(&*MS);
			if(antM != NULL)
			{
				*memoAtual = antM;
				auxM = antM->prox; // pega a caixa da frente
				antM->prox = NULL; // corta a ligação com a caixa da frente
				
				while(auxM!=NULL)
				{
					auxM2 = auxM;
					auxM = auxM->prox;
					
					free(auxM2);
				}
			}
			
			
		}
		
		
		i++;
	}
	
}

void primeira_vez(Programa *P, Programa **exe, TelaS *tela_s)
{
	Programa *aux;
	char instrucaoAux[100];
	int i, diferenca;
	
	aux = P;
	while(aux!=NULL && strcmp(aux->instrucao, "int main()")!=0)
		aux=aux->prox;
	
	if(aux==NULL) // foi até o final e não achou nenhum int main()
	{
		clrscr();
		cria_tela(30);
		//simulacao(30);
		gotoxy(5, 3);
		textbackground(4); // RED
		printf("ERRO: Programa nao possui o 'int main()'");
	}
	else
	{
		// achou a linha do int main()
		// aux recebe 2 caixas a frente, sendo essa a primeira linha executavel do programa
		aux = aux->prox->prox;
		strcpy(instrucaoAux, aux->instrucao);
		diferenca = 75 - strlen(aux->instrucao); // diferença para poder concatenar com espaços, para preencher o fundo... pegando a linha toda dentro do simulador
		
		for(i=0; i<diferenca-1; i++)
			strcat(instrucaoAux, " ");
		
		gotoxy(5, aux->pos_lin);
		textbackground(11);
		printf("%s", instrucaoAux);
		
		*exe=aux;
		//(*ult_lin)->ultimaLida = aux; // guarda a caixa da informacao atual, para ser executada quando sair da linha
		(*tela_s).ult_lin = aux->pos_lin;
		strcpy((*tela_s).ult_instrucao, instrucaoAux);
	}
}

void executa_programa(Programa *cab, Programa **exe, Memoria **memoCab, Memoria **memoAtual, TelaP **telapCab, TelaP **telapAtual, EndCon *endcon, TelaS *tela_s, int *primeiro, PilhaS **PS, PilhaMS **MS)
{
	//Tela tela;
	Programa *aux;
	char instrucaoAux[100];
	int i, diferenca;
	
	//começa pela primeira linha executavel dentro do int main()
	if(*primeiro==1)
	{
		primeira_vez(cab, &*exe, &*tela_s);
		*primeiro=0;
	}
	else
	{ // programa ja está em excução
		// desmarca linha selecionada e executa ela
		gotoxy(5, (*tela_s).ult_lin);
		textbackground(0); // BLACK
		printf("%s", (*tela_s).ult_instrucao);
		
		// -----------------------------------------FAZER FUNÇÃO PARA EXECUTAR AS LINHAS LIDAS---------------------------------------
		// exe ainda aponta para a ultima caixa!!!! 
		// Programa *exe, Memoria **memoCab, Memoria **memoAtual, TelaP **telapCab, TelaP **telapAtual, EndCon *endcon
		executa_linha(cab, &*exe, &*memoCab, &*memoAtual, &*telapCab, &*telapAtual,  &*endcon, &*tela_s, &*PS, &*MS);
		// se for função, terá uma busca feita a partir da instrucao..... senão uma busca pela proxima linha ...... 2 funções diferentes
		
		
		// selecionar a proxima linha, e procurar a instrucao na lista de PROGRAMA, pelo posicao da linha
		proxima_linha(cab, &*exe, &*tela_s, &*PS);
		//gotoxy(5, tela.ult_lin);
		//textbackground(11);
		
		if((*exe)->prox == NULL)
			*exe=NULL;
		
		//*ult_lin= //atualiza a linha que acabou de ser lida
	}
	
}


void simulacao(Programa *P, int tot_lin, int *primeiro)
{
	Programa *executando;
	Memoria *memoCab, *memoAtual;
	TelaP *telapCab, *telapAtual;
	TelaS tela_s;
	EndCon endcon;
	//PilhaPE *PE;
	PilhaS *PS;
	PilhaMS *MS;
	int tela_memoria=0, tela_programa=0, var_funcao;
	char ch1, ch2;
	gotoxy(4, tot_lin+4);
	printf("F6 - Sair\t");
	//printf("F7 - Abrir\t");
	printf("F8 - Executar\t");
	printf("F9 - Memoria\t");
	printf("F10 - Tela");
	
	
	executando = P; // P ja foi criado previamento, portanto não é NULL
	endcon.end = 100;
	memoCab = memoAtual = NULL;
	telapCab = telapAtual = NULL;
	//var_funcao = 0;
	//InitPE(&PE);
	InitS(&PS);
	InitMS(&MS);
	//linha = NULL;
	
	// os botoes F1, F2, F3 retornam 2 valores
	ch1 = getch(); // primeiro valor do botão
	ch2 = getch(); // segundo valor do botão ..  será diferenciado por esse
	
	while(ch2!=64)
	{
		switch(ch2)
		{
		
			//F8	
			case 66: if(tela_memoria != 1 && tela_programa != 1 && executando!=NULL)
					 	executa_programa(P, &executando, &memoCab, &memoAtual, &telapCab, &telapAtual, &endcon, &tela_s, &*primeiro, &PS, &MS);
					 break;
			
			//F9		 
			case 67: //Memoria(P);
					 if(tela_memoria == 1) // tela da memoria está visivel
					 	tela_memoria = 0;
					 else
					 	tela_memoria = 1; // tela da memoria irá ficar visivel
					 
					 mostra_memoria(memoCab, &tela_memoria, P, tela_s, tot_lin);
					 break;
			
			//F10
			case 68: //MostraTela(P);
					 if(tela_programa == 1) // tela do programa está visivel
					 	tela_programa = 0;
					 else
					 	tela_programa = 1; // tela do programa irá ficar visivel
					
					 mostra_tela_programa(telapCab, &tela_programa, P, tela_s, tot_lin);
					 break;
		}
		
		ch1 = getch();
		ch2 = getch();
	}
	
}
