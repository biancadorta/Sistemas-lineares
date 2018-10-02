#include <stdio.h>
#include <stdlib.h>

int main()
{
    char* nome_arquivo;
    //Alocar o tamanho deste ponteirooooooo
    nome_arquivo = (char*)malloc(sizeof(char)*257);
    printf("Hello world!\n");
    printf("Digite o nome do arquivo: \n");
    scanf("%s", nome_arquivo);
    FILE* fil = fopen(nome_arquivo, "r");
    return 0;
}
