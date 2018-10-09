#include <stdio.h>
#include <stdlib.h>

int main()
{
    char nome_arquivo[40];
    float** matriz;
    char** incognitas;
    int ordem = 0;
    printf("Hello world!\n");
    printf("Digite o nome do arquivo: \n");
    scanf("%s", nome_arquivo);
    FILE* fil = fopen(nome_arquivo, "r");

    if(fil == NULL)
        printf("Erro na leitura do arquivo.");

    else{
        fscanf(fil,"%i", &ordem);
        printf("Ordem do sistema: %i", ordem);
        //Agora podemos alocar na memoria a matriz, pois temos a ordem
        matriz =(float**)malloc((ordem+1)*sizeof(float*));//+1 porque estamos guardando as variaveis e o valor apos o =s
        incognitas = (char*)malloc((ordem)*sizeof(char));

        int i;
        for(i = 0; i<ordem; i++){
          matriz[i] = (float*)malloc(ordem*sizeof(float));
        }

        printf("\nLENDO AS EQUACOES...\n");
        //precisei fazer esse printf para o fscanf comecaar a ler a proxima linha, pois ele estava juntando o que leu antes com o comeco da 1º equacao

        int j, i2;
        for(j=0; j<=ordem-1; j++){ //le as linhas do arquivo
            for(i2=0; i2<=ordem-1; i2++){ //le a linha da equacao, neste caso as n primeiras partes
                //na 1º linha saberemos quais sao as variaveis, logo so precisaremos atribuir ao vetor incognita na primeira vez
                //que le
                fscanf(fil, "%f%s ", (*(matriz + j)+ i2), (incognitas+i2)); //FSCANF MECHE COM ENDERECO
                printf("%.0f",*(*(matriz + j)+ i2));
                printf("%s\n", *(incognitas+i2));
            }
            fscanf(fil, "=%f", *(matriz + j)+(i2+1));
        }
    }
    return 0;
}
