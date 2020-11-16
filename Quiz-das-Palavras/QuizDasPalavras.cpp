#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#define max 6
// feito por: Otávio Gomes

// JOGO: QUIZ DAS PALAVRAS
/* Objetivo do jogo:
Você deverá adivinhar 1 palavra correta por fase nesse jogo, será dito algumas dicas sobre
as possíveis palavras junto com o tamanho delas, logo você irá inserir os caracteres
nas posições corretas para formar a palavra que o jogo pensar.

Formando uma palavra ao inserir vários caracteres você pode remover ou inserir caracteres
no formato de uma lista sequencial, após completar a palavra que você digitou
deverá corrigir se a palavra está correta, se ela estiver avançará no jogo.
*/
 //armazena os caracteres digitados
struct palavras{ 
    int n; //definir a qtd de caracteres na string dados (bem dizer atualiza o que tu remove e bota)
	char dados[max]; 
};

//corrigimos se o que o usuario digitou esta correto
struct correcao{
	char nome[6];
	char nome1[6];
	char nome2[6];
	int n; 
};
// fases do jogo que são duas
struct fases{
	char fase1[70]="E UM PASSARO BEM CONHECIDO, LER-SE DE TRAS PARA FRENTE";
	char fase2[50]= "PRIMEIRO COMPUTADOR ELETRONICO";
	int n=0;
};
// prototipo
void Criar(struct palavras *L, struct correcao *C);
void Vazia(struct palavras L);
void menu(struct palavras *L, struct correcao *C);
void menu1();
int corrigir(struct correcao C, struct palavras L);
void inserir(struct palavras *L, int posi, char elemento);
void remover (struct palavras *L, int posi);
void atribuirNome(struct correcao *C);
void mostrar(struct palavras *L);
main(){
	setlocale(LC_ALL,"Portuguese");
	struct palavras l;
	struct correcao c;
	struct fases dicas;
	Criar(&l, &c);
	menu1();
	menu(&l, &c);

}
void menu1(){
	printf("_____________________________________________________________\n");
	printf("\t\tESSE E O JOGO DE ADIVINHACAO\n");
	printf("VOCE DEVE DIGITAR AS LETRAS CORRETAS PARA GANHAR O JOGO\n");
	printf("_____________________________________________________________\n");
	system("pause");
	
}
//menu principal
void menu(struct palavras *L, struct correcao *C){
	char letra;
	int cont, cont1=0;
	int opc, i, posi;
	struct fases dicas;
	
	do{
		system("cls");
		mostrar(L);
		printf("\n\n");
		printf("______________________________________________________\n");
		printf("AQUI VAI UMA DICA: \n");
		switch(dicas.n){
			case 0:
				printf("\t\t\t%s\n", dicas.fase1);
				break;
			case 1:
				printf("\t\t\t%s\n", dicas.fase2);
		}
		printf("______________________________________________________\n");
		
		printf("1- DESEJA INSERIR LETRAS: \n");
		printf("2- DESEJA REMOVER LETRAS: \n");
		printf("3- DESEJA CONFERIR SE ESTA CERTO: \n");
		scanf("%d", &opc);
		switch(opc){
			case 1:
				printf("Digite uma letra: ");
				scanf(" %c", &letra);
				fflush(stdin);
				printf("DIGITE A POSICAO DO SEU CARACTERE!: ");
				scanf("%d", &posi);
				inserir(L, posi, letra);
				break;
			case 2:
				printf("Digite a posicao a ser removida: ");
				scanf("%d", &posi);
				remover(L, posi);
				break;
			case 3:
				printf("CONFERINDO SUA RESPOSTA...\n");
				atribuirNome(C);
				L->dados[L->n] = '\0'; //imprimir precisa ter o barra zero vulgo final
				
				if(!strcmp(C->nome, L->dados)==1){ // comparação se é correto
					printf("%s\n", L->dados);
					printf("VOCE ACERTOU\n\n\n");
					dicas.n++; // saber qual o nome da dica
					C->n++; // saber qual a resposta correta para comparar com o que vc digitou
					atribuirNome(C);
					if(C->n == 2){
						printf("________________________________\n");
						printf("\t FASES CONCLUIDAS!\n\n");
  						printf("\tObrigado por jogar!\n");
						printf("________________________________\n\n\n\n\n");
						printf("=========================================\n");
						printf("| By: Otavio Gomes                      |\n");
						printf("=========================================\n");
						exit(0);
					}
				L->n=0;
				L->dados[0]=' '; //zerar o caracteres
				L->dados[1]='\0'; //
				}else{
					printf("VOCE ERROU!!\n");
					printf("A PALAVRA QUE VOCE FORMOU ESTA INCORRETA!\n\n");
					getch();
				}
				break;
			default:
			printf("OPCAO INVALIDA!!\n");	
		}			
	}
	while(cont!=1);
}

void Criar(struct palavras *L, struct correcao *C){
 	L->n = 0;
 	C->n = 0;
}
  
void Vazia(struct palavras L){
     if (L.n == 0) {
     	printf("Lista vazia \n"); 
	}else{
    	printf("A lista não está vazia\n");
	}
}
 	 
void inserir(struct palavras *L, int posi, char elemento){
  	if ((posi-1 < 0) || (posi-1 > L->n) || L->n >= max-1) { // verifica as situações e não deixa inserir
  		printf("Não foi possível inserir\n");
  		getch();
		}else{
			if(posi-1 <= L->n){ //controlador de caracteres (insere um em cima do outro) (OBS: só insere já estiver nas casas)
				for(int i=L->n ; i>posi-1 ; i--){ // joga as casas para direita, libera casas no vetor
					L->dados[i] = L->dados[i-1]; // pega os valores e jogando a direita
				}		
			}
			L->dados[posi-1] = elemento; // aqui ele é adicionado
  			L->n++; // atualiza o contador de qtd de caracteres da String
    }
}

void remover(struct palavras *L, int posi){// remove os caracteres
	char letra=L->dados[posi-1]; // iguala e passa os caracteres na posicao da string p/ var letra
  if((posi-1 < 0) || (posi-1 >= L->n)){ 
     	printf("NAO FOI POSSIVEL REMOVER\n");
	}else{
     	for (int i=posi-1 ; i< L->n ; i++) { //anda uma casa para esquerda de todos os caracteres que foi removido pela direita
            L->dados[i]=L->dados[i+1]; //incrementa +1
		}
     	L->n--; // subtrair a qtd de caracteres que há inserido
     	printf(" %c Letra removida!\n", letra);
    } 
} 

void atribuirNome(struct correcao *C){
	
	strcpy(C->nome1, "arara"); // igualando a string digitada com ARARA
	strcpy(C->nome2, "eniac"); // igualando a string digitada com ENIAC
	
	switch(C->n){
		case 0:
			strcpy(C->nome, C->nome1); //  controla o que vai ser a palavra CORRETA
			break;
		case 1:
			strcpy(C->nome, C->nome2); // controla o que vai ser a palavra CORRETA
			break;
	}
}

void mostrar(struct palavras *L){
	for(int i=0; i<max-1 ;i++){
		printf("%d\t", i+1);
	}
	printf("\n");
	for(int i=0; i< L->n;i++){
		printf("%c\t", L->dados[i]);
	}
	printf("\n");
}