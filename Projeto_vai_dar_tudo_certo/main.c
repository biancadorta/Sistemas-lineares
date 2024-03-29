#include <stdio.h>
#include <stdlib.h>

char nome_arquivo[40];
double** matriz;
char* incognitas;
int ordem = 0;

typedef enum
bool{
    true,
    false
}bool;

typedef
struct No{
    char* incognita;
    size_t tamanho;
    struct No* prox;
}No;

No* insira(struct No* inicio, char* variavel){

    if(inicio == NULL){
        No* Novo = (No*)malloc(sizeof(struct No)); //e para dar erro pois o char* nao foi "instanciado"
        Novo->incognita = variavel;
        Novo->prox = NULL;
        inicio = Novo;
        return inicio;
    }
    else{
        No* aux = inicio;
        while(aux!=NULL){
            if(aux->prox == NULL){
                No* Novo = (No*)malloc(sizeof(struct No)); //e para dar erro pois o char* nao foi "instanciado"
                Novo->incognita = variavel;
                Novo->prox = NULL;
                aux->prox = Novo;
                return inicio;
            }
            aux = aux->prox;
        }
    }

}
bool trocarLinha(int linha1, int linha2, int qtdLinhas, double** matriz){
    double* vet;
    bool trocou = false;
    if(linha1 != linha2){ //se achou uma linha
        vet = *(matriz+linha1);
        *(matriz+linha1) = *(matriz+linha2);
        *(matriz+linha2) = vet;
        trocou=true;
        return trocou;
    }
    else{
        return trocou;
    }
}

//Calcula a posi��o do maior elemento da coluna a partir do parametro nLinha
int linhaParaTrocar(int nlinha, int ncoluna){
    int linhaTrocar = nlinha;
    int var;
    for(var=0; var < ordem; var++){
        if(*(*(matriz+var)+ncoluna) > *(*(matriz+linhaTrocar)+ncoluna))
            linhaTrocar = var;
    }
    return linhaTrocar;
}

enum bool diagonalZero(){
    int j;
    for(j=0; j < ordem; j++){
        if(*(*(matriz+j)+j) == 0)
            return true;
        else
            return false;
    }
}

void zerarColunas(int linha){
    double aux,aux2 = 0;
    aux = *(*(matriz+linha)+linha);
    int n,m, n2;
    for(n=0; n<=ordem; n++){
        *(*(matriz+linha)+n) = *(*(matriz+linha)+n)/aux;
    }

    for(m=0; m<ordem; m++){
        if(m != linha){
            aux2 = *(*(matriz+m)+linha);
            for(n2=0; n2<=ordem; n2++){
                *(*(matriz+m)+n2) = *(*(matriz+m)+n2)+(*(*(matriz+linha)+n2))*((-1*aux2));
            }
        }
    }
}

void resMat(double** mat,int ord){
    //criar uma copia da matriz principal
    int i3;
    int linha2 = 0;
    bool achou = false;
    for(i3=0; i3 < ord; i3++){ //percorrer as linhas
        if((*(*(mat+i3)+i3)) == 0){
           linha2 = linhaParaTrocar(i3, i3);
           achou = trocarLinha(i3,linha2,ord,mat);
           //if(achou == true){ //se achou uma linha para trocar
                //zerarColunas(i3);
           //}
           /*else{ //tentaremos ver se ha coluna para trocar
                //achou = trocarColuna();
                //if(achou){
                }
                else
                    return; //nao tem solucao para o sistema
           }*/
           printMatriz();
        }
    }
    printMatriz();
}

void printMatriz(){
    int m,n;
    printf("\n");
    for(m=0; m < ordem; m++){ //percorrer a linha
        for(n=0; n <= ordem; n++){//ha as colunas dos coeficientes e a do numero apos o =
            printf("%.0f ", *(*(matriz+m)+ n));
        }
        printf("\n");
    }
    printf("\n");
}

No* vetNaLista(No* inicio, char* incognitas){
    No* aux = inicio;
    int a;
    for(a=0; a<ordem; a++){
        aux = insira(aux, *(incognitas+a));
    }
    return aux;
}

void printarLista(No* le){
    No* p;
    for(p = le; p!= NULL; p = p->prox)
        printf("Incognita: %c\n", p->incognita);
}

void solucao(No* inicio){
    No* aux = inicio;
    int i = 0;
    while(i!=ordem){
        printf("incognita: %c -> valor: %.0lf\n", aux->incognita, *(*(matriz+i)+ordem));
        i++;
        aux = aux->prox;
    }
}

int main()
{
    int i;
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
        matriz =(double**)malloc(ordem*sizeof(double*));//+1 porque estamos guardando as variaveis e o valor apos o =s
        incognitas = (char*)malloc(ordem*sizeof(char));

        int i;
        int aux = ordem+1;
        for(i = 0; i<ordem; i++){
          matriz[i] = (double*)malloc((aux)*sizeof(double));
        }

        printf("\nLENDO AS EQUACOES...\n");
        //precisei fazer esse printf para o fscanf comecaar a ler a proxima linha, pois ele estava juntando o que leu antes com o comeco da 1� equacao

        int j, i2;
        for(j=0; j<=ordem-1; j++){ //le as linhas do arquivo
            for(i2=0; i2<=ordem-1; i2++){
                fscanf(fil, "%lf%s ", (*(matriz + j)+ i2), (incognitas+i2)); //FSCANF MECHE COM ENDERECo
            }
            fscanf(fil, "= %lf", (*(matriz + j)+ ordem));
        }

        No* inicio = NULL;
        inicio = vetNaLista(inicio,incognitas);
        printarLista(inicio);
        printMatriz();
        resMat(matriz, ordem);
        printMatriz();

        if(diagonalZero() == true)
            printf("SISTEMA INDETERMINADO");
        else{
            printf("SISTEMA DETERMINADO\n");
            printf("MATRIZ antes: \n");
            printMatriz();

            for(i=0; i < ordem; i++){
                zerarColunas(i);
            }

            printf("MATRIZ final: \n");
            printMatriz();
            printf("=======SOLUCAO========\n");
            solucao(inicio);
        }

    }
    return 0;
}
