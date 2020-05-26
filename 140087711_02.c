/*Universidade de Brasilia
Instituto de Ciencias Exatas
Departamento de Ciencia da Computacao
Computacao Basica – 1/2015
Aluno(a): Victor Hugo Magalhaes Rodrigues
Matricula: 140087711
Turma: E
Versão do compilador: GCC
Descricao: Jogo da Forca*/

#ifdef _WIN64
	#define CLEAR "cls"
#else
	#define CLEAR "clear"
#endif

#include <stdio.h>
#include <stdlib.h>

void Tela(char a[], char d[], int* p, int* t, int* f){

	system(CLEAR);
	printf("*****JOGO DA FORCA*****\n");
	printf("Pontuacao da palavra: %d\n",*p);
	printf("Pontuacao total: %d\n\n",*t);
	if(*f==0){
		printf(" ____\n|    |\n|\n|\n|\n|\n|\n\n");
	}
	else{
		if(*f==1){
			printf(" ____\n|    |\n|    O\n|\n|\n|\n|\n\n");
		}
		else{
			if(*f==2){
				printf(" ____\n|    |\n|    O\n|    |\n|    |\n|\n|\n\n");
			}
			else{
				if(*f==3){
					printf(" ____\n|    |\n|  __O\n|    |\n|    |\n|\n|\n\n");
				}
				else{
					if(*f==4){
						printf(" ____\n|    |\n|  __O__\n|    |\n|    |\n|\n|\n\n");
					}
					else{
						if(*f==5){
							printf(" ____\n|    |\n|  __O__\n|    |\n|    |\n|  _|\n|\n\n");
						}
						else{
							printf(" ____\n|    |\n|  __O__\n|    |\n|    |\n|  _| |_\n|\n\n");
						}
					}
				}
			}
		}
	}
	printf("%s\n\n",d);
	printf("%s\n\n",a);
}/*mostra ao usuario a interface do jogo*/

void GeraAlfabeto(char a[]){
int i;
char b;

	b='A';
	for(i=0;i<26;i++){
		a[i]=b;
		b=b+1;
	}
	a[i]='\0';
}/*gera o vetor alfabeto com todas as letras para ser usado no inicio de uma palavra*/

void GeraPalavra(char a[], char b[]){
int i;

	i=0;
	while(a[i]!='\0'){
		b[i]='_';
		i=i+1;
	}
	b[i]='\0';
}/*gera a palavra com underscore*/

void AtualizaAlfabeto(char a[], char b){
int i,j;
char alfabeto_aux[26];

	i=0;
	j=0;
	while(a[i]!='\0'){
		if(a[i]!=b){
			alfabeto_aux[j]=a[i];
			j=j+1;
		}
		i=i+1;
	}
	alfabeto_aux[j]='\0';
	i=0;
	j=0;
	while(alfabeto_aux[i]!='\0'){
		a[i]=alfabeto_aux[i];
		i=i+1;
	}
	a[i]='\0';
}/*retira a letra utilizada do vetor alfabeto e compacta-o*/

void Verifica(char a[], char* b, int* c){
int i;

	if((*b>=97) && (*b<=122)){
		*b=*b-32;
	}
	i=0;
	while(a[i]!='\0'){
		if(*b==a[i]){
			*c=1;
		}
		i=i+1;
	}
}/*verifica se a letra pode ser utilizada*/

void RecebeLetra(char a[], char b[], char c){
int i;

	i=0;
	while(a[i]!='\0'){
		if(c==a[i]){
			b[i]=c;
		}
		i=i+1;
	}
}/*modifica a palavra a ser decifrada*/

int main(){
int j,k, a,forca,igual,continua,perdeu, pontos,pontos_total, achou;
char alfabeto[27], palavra_alvo[21], palavra_decifrada[21], letra, resp_usuario;

FILE *fp;
fp = fopen("palavras.txt","r");

pontos_total=0;
continua=0;
perdeu=0;

	while((feof(fp)==0) && (continua==0) && (perdeu==0)){
		fscanf(fp,"%s ",palavra_alvo);
		fscanf(fp,"%d",&pontos);

		GeraAlfabeto(alfabeto);
		GeraPalavra(palavra_alvo,palavra_decifrada);
		igual=0;
		forca=0;
		while((!igual) && (forca<6)){
			a=0;
			while(a==0){
				Tela(alfabeto,palavra_decifrada,&pontos,&pontos_total,&forca);
				printf("Escolha uma das letras acima para decifrar a palavra: ");
				scanf("%c",&letra);
				Verifica(alfabeto,&letra,&a);
			}/*loop que le a variavel ate ser valida*/
			AtualizaAlfabeto(alfabeto,letra);
			j=0;
			achou=0;
			while(palavra_alvo[j]!='\0'){
				if(letra==palavra_alvo[j]){
					achou=1;
				}
				j=j+1;
			}/*testa se tem a letra escolhida pelo usuario na palavra-alvo*/
			if(achou){
				printf("Letra correta!\n");
				RecebeLetra(palavra_alvo,palavra_decifrada,letra);
			}/*modifica a palavra*/
			else{
				forca=forca+1;
				pontos=pontos-5;
				printf("Letra incorreta! Voce ainda tem %d chances!\n", 6-forca);
			}/*nao modifica a palavra e e calculado forca e pontos*/
			igual=1;
			k=0;
			while(palavra_decifrada[k]!='\0'){
				if(palavra_decifrada[k]!=palavra_alvo[k]){
					igual=0;
				}
				k=k+1;
			}
		}/*loop que gera cada tentativa*/
		if(forca>5){
			perdeu=1;
			Tela(alfabeto,palavra_decifrada,&pontos,&pontos_total,&forca);
		}
		else{
			pontos_total=pontos_total+pontos;
			Tela(alfabeto,palavra_decifrada,&pontos,&pontos_total,&forca);
			printf("Parabens! Voce conseguiu %d pontos na palavra '%s'\n",pontos,palavra_alvo);
			printf("Deseja continuar?(S/N) ");
			scanf("%c",&resp_usuario);
			while((resp_usuario!='s') && (resp_usuario!='S') && (resp_usuario!='n') && (resp_usuario!='N')){
				Tela(alfabeto,palavra_decifrada,&pontos,&pontos_total,&forca);
				printf("Deseja continuar?(S/N) ");
				scanf("%c",&resp_usuario);
				if((resp_usuario=='n') || (resp_usuario=='N')){
					continua=1;
				}
			}/*loop que le a resposta do usuario ate ser valida*/
		}
	}/*loop principal onde le ate o final do arquivo .txt*/
	printf("Voce conseguiu %d pontos.\n",pontos_total);
	printf("GAME OVER\n");

fclose(fp);
getchar();
getchar();

return 0;
}
