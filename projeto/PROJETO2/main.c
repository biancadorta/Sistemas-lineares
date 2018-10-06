#include <stdio.h>
#include <stdlib.h>



int main()
{
    char* nome_arquivo;
    char* strarq;
    char* teste;
    //Alocar o tamanho deste ponteirooooooo
    nome_arquivo = (char*)malloc(257*(sizeof(char)));
    printf("Hello world!\n");
    printf("Digite o nome do arquivo: \n");
    scanf("%s", nome_arquivo);
    FILE* fil = fopen(nome_arquivo, "r");
    if(fil == NULL)
        printf("Erro na leitura do arquivo");

    else{
        int i =0;
        char c;
        int qtdEquacoes = 0;
        c = getc(fil); //le do arquivo um caractere retornando-o
        while(c != EOF){
            printf("%c", c);
            c = getc(fil);
            i++; //saber o valor de char existentes para instanciar a string strArq
        }
        printf("\ni: %i", i);
        strarq = (char*)malloc(i*(sizeof(char)));
        teste  = (char*)malloc(i*(sizeof(char)));
        teste  = " ";
        rewind(fil); //posiciona no inicio do arquivo e pego a quantidade de equacoes que esta na 1º linha
        fscanf(fil, "%s", strarq);
        printf("\nQtd equacoes: %s\n", strarq);
        qtdEquacoes = (int)(*strarq);
        printf("%i", qtdEquacoes);

        for(int j =0 ; j <= i; j++){ //comecaremos a ler as equacoes
            fscanf(fil, "%s", strarq);
            printf("%s \n", strarq);
        }

    }
return 0;
}
