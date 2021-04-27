//
//  main.c
//  Algoritmo e Estrutura de Dados II
//
//  Created by João Guilherme on 26/04/21.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct vaga Vaga;
typedef struct carro Carro;

char classes[4] = {'M','V','E','C'};

struct vaga{
    int numero;
    char classe;
    int altura;
    Carro* carro;
    Vaga* esq;
    Vaga* dir;
};

struct carro{
    char* placa;
    char classe;
    int horaEntrada;
    int minutoEntrada;
    int horaSaida;
    int minutoSaida;
};
int gerarNumero(int min,int max){
    int random = 0;
    
    
     random = (min + (rand()%max));
    
    return random;
}

Carro* criarCarro(char* placa, char classe, int horaEnt,int minEnt, int horaSaida, int minutoSaida){
    Carro* novoCarro = (Carro*) malloc(sizeof(Carro));
    
    novoCarro->placa = placa;
    novoCarro->classe = classe;
    novoCarro->horaEntrada = horaEnt;
    novoCarro->minutoEntrada = minEnt;
    novoCarro->horaSaida = horaSaida;
    novoCarro->minutoSaida = minutoSaida;
    
    return novoCarro;
}
Vaga* busacaVaga(int numero, Vaga* raiz){
    if(raiz == NULL){
        return NULL;
    }
    
    if (numero < raiz->numero){
        return busacaVaga(numero, raiz->esq);
    }else if (numero > raiz->numero){
        return busacaVaga(numero, raiz->dir);
    }else{
        return raiz;
    }
}

Vaga* buscaVagaMaisPerto(Vaga* raiz){
    if(raiz == NULL){
        return NULL;
    }else if (raiz->esq == NULL){
        return raiz;
    }else{
        return buscaVagaMaisPerto(raiz->esq);
    }
}

Vaga* buscaVagaMaisLonge(Vaga* raiz){
    if(raiz != NULL){
        while (raiz->dir != NULL) {
            raiz = raiz->dir;
        }
    }
    
    return raiz;
}

int alturaAvl(Vaga* vaga){
    if(vaga == NULL){
        return -1;
    }else{
        return vaga->altura;
    }
}

int alturaBalanceada(int alturaEq, int alturaDr){
    if(alturaEq > alturaDr){
        return alturaEq;
    }else{
        return alturaDr;
    }
}

Vaga* rotacaoEsquerda(Vaga* vaga2){
    Vaga* vaga1;
    
    vaga1 = vaga2->esq;
    vaga2->esq = vaga1->dir;
    vaga1->dir = vaga2;
    
    vaga2->altura = alturaBalanceada(alturaAvl(vaga2->esq), alturaAvl(vaga2->dir)) + 1;
    vaga1->altura = alturaBalanceada(alturaAvl(vaga1->esq), vaga2->altura) + 1;
    
    return vaga1;
}

Vaga* rotacaoDireita(Vaga* vaga1){
    Vaga* vaga2;
    
    vaga2 = vaga1->dir;
    vaga1->dir = vaga2->esq;
    vaga2->esq = vaga1;
    
    vaga1->altura = alturaBalanceada(alturaAvl(vaga1->esq), alturaAvl(vaga1->dir)) + 1;
    vaga2->altura = alturaBalanceada(alturaAvl(vaga2->dir), vaga1->altura) + 1;
    
    return vaga2;
}

Vaga* rotacaoDuplaEsquerda(Vaga* vaga3){
    vaga3->esq = rotacaoDireita(vaga3->esq);
    
    return rotacaoEsquerda(vaga3);
}

Vaga* rotacaoDuplaDireita(Vaga* vaga1){
    vaga1->dir = rotacaoEsquerda(vaga1->dir);
    
    return rotacaoDireita(vaga1);
}

Vaga* insereVagaOcupada(int numeroVaga, Vaga* raiz){
    if(raiz == NULL){
        raiz = (Vaga*) malloc(sizeof(Vaga));
        raiz->numero = numeroVaga;
        raiz->altura = 0;
        raiz->classe = classes[gerarNumero(0, 4)];
        raiz->esq = NULL;
        raiz->dir = NULL;
    }else if(numeroVaga < raiz->numero){
        raiz->esq = insereVagaOcupada(numeroVaga, raiz->esq);
        if(alturaAvl(raiz->esq) - alturaAvl(raiz->dir) == 2){
            if(numeroVaga < raiz->esq->numero){
                raiz = rotacaoEsquerda(raiz);
            }else{
                raiz = rotacaoDuplaEsquerda(raiz);
            }
        }
    }else if(numeroVaga > raiz->numero){
        raiz->dir = insereVagaOcupada(numeroVaga, raiz->dir);
        if(alturaAvl(raiz->dir) - alturaAvl(raiz->esq) == 2){
            if(numeroVaga > raiz->dir->numero){
                raiz = rotacaoDireita(raiz);
            }else{
                raiz = rotacaoDuplaDireita(raiz);
            }
        }
        
    }
    raiz->altura = alturaBalanceada(alturaAvl(raiz->esq), alturaAvl(raiz->dir)) + 1;
    return raiz;
}

/* Imprime a árvore em ordem */
void emordem(Vaga* raiz)
{
    if (raiz == NULL)
        return;
 
    emordem(raiz->esq);
    printf("%d ",raiz->numero);
    emordem(raiz->dir);
}
 
/* Imprime a árvore em pré-ordem */
void preordem(Vaga* raiz)
{
    if (raiz == NULL)
        return;
 
    printf("%d ",raiz->numero);
    preordem(raiz->esq);
    preordem(raiz->dir);
}
 
/* Imprime a árvore em pós-ordem */
void posordem(Vaga* raiz)
{
    if (raiz == NULL)
        return;
 
    posordem(raiz->esq);
    posordem(raiz->dir);
    printf("%d ",raiz->numero);
}

int quantidadeCarrosEstacionando(Vaga* raiz){
    int cont = 0;
    
    if(raiz != NULL){
        cont = cont + 1;
        cont = cont +  quantidadeCarrosEstacionandos(raiz->esq);
        cont = cont + quantidadeCarrosEstacionandos(raiz->dir);
    }
    return cont;
}



int main(){
    Vaga* raiz = NULL;
    srand ((unsigned int)time(NULL) );
    
    printf("Digite o numero de carros estacionados:\n");
    int numeroEntradas = 0;
    scanf("%d",&numeroEntradas);
    
    for(int cont = 0;cont < numeroEntradas; cont++){
        raiz = insereVagaOcupada(gerarNumero(0, 1024), raiz);
    }
    printf("==============================\n");
                printf("IMPRESSAO DA ARVORE:\n\n");
                printf("Em ordem:\n");
                emordem(raiz);
                printf("\n\n");
                printf("Pre ordem:\n");
                preordem(raiz);
                printf("\n\n");
                printf("Pos ordem:\n");
                posordem(raiz);
                printf("\n\n");
                printf("Grafico:\n");
    printf("==============================\n");
    printf("Quantidade de carros estacionados: %d",quantidadeCarrosEstacionado(raiz));
    
   

    return 0;
}
