//
//  main.c
//  Algoritmo e Estrutura de Dados II
//
//  Created by João Guilherme on 01/04/21.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct lista Lista;
typedef struct no No;

struct no{
    int valor;
    No* prox;
    No* anterior;
};

struct lista{
    No* inicio;
    No* fim;
};

Lista* criarLista(){
    Lista* l = malloc(sizeof(Lista));
    l->inicio=NULL;
    l->fim=NULL;
    return l;
}

void inserirFim(Lista* l,int valor){
    No* novo =(No*) malloc(sizeof(No));
    novo->valor=valor;
    No* notemp=l->fim;
    if(l->fim!=NULL){
        notemp->prox=novo;
        novo->anterior=notemp;
        novo->prox=NULL;
        l->fim=novo;
    }else{
        l->inicio=novo;
        l->fim=novo;
        novo->prox=NULL;
        novo->anterior=NULL;
    }
}


void imprimirLista(Lista* l){
    No* temp = l-> inicio;
    if(temp != NULL){
        if(temp->prox == NULL){
            printf("%d", temp->valor);
        }else{
                printf("%d",temp->valor);
                temp = temp->prox;
            while(temp != NULL){
                printf(" %d",temp->valor);
                temp = temp->prox;
            }
        }
    }
}

void removeNo(Lista* l, No* noRemovido){
    No* noTemp;
    No* anterior;
    No* proximo;
    if(l->inicio == noRemovido){
        noTemp = l->inicio->prox;
        l->inicio = noTemp;
        l->inicio->anterior = NULL;
        free(noRemovido);
    }else if (l->fim == noRemovido){
        noTemp = l->fim->anterior;
        l->fim = noTemp;
        l->fim->prox = NULL;
        free(noRemovido);
    }else{
        anterior = noRemovido->anterior;
        proximo = noRemovido->prox;
        
        anterior->prox = proximo;
        proximo->anterior = anterior;
        free(noRemovido);
    }
}
void removeRepetidos(Lista* l){
    No* analisado = l->inicio;
    No* atual = l->inicio->prox;
    No* atualTemp;
    
    while(analisado != NULL){
        
        if(analisado == l->inicio){
            atual = l->inicio->prox;
        }else{
            atual = l->inicio;
        }
        
        while (atual != NULL) {
            if(analisado->valor == atual->valor && analisado != atual){
                atualTemp = atual;
                atual = atual->prox;
                removeNo(l, atualTemp);
            }else{
                atual = atual->prox;
            }
            
        }
        analisado = analisado->prox;
    }
}

Lista* uniaoLista(Lista* l1, Lista* l2){
    Lista* listaUniao = criarLista();
    No* l1Temp = l1->inicio;
    No* l2Temp = l2->inicio;
    inserirFim(listaUniao, l1Temp->valor);
    l1Temp = l1Temp->prox;
    while(l1Temp != NULL){
        inserirFim(listaUniao, l1Temp->valor);
        l1Temp = l1Temp->prox;
    }
    
    No* lTemp = l1 -> inicio;
    while(lTemp != NULL){
        l2Temp = l2->inicio;
        while(l2Temp != NULL){
            if(l2Temp->valor != lTemp->valor){
                inserirFim(listaUniao, l2Temp->valor);
            }
            l2Temp = l2Temp->prox;
        }
        lTemp = lTemp->prox;
    }
    removeRepetidos(listaUniao);
    return listaUniao;
}

Lista* intersLista(Lista* l1, Lista* l2){
    Lista* listaInters = criarLista();
    No* l1Temp = l1->inicio;
    No* l2Temp = l2->inicio;
    
    
    No* lTemp = l1 -> inicio;
    while(lTemp != NULL){
        l2Temp = l2->inicio;
        while(l2Temp != NULL){
            if(l2Temp->valor == lTemp->valor){
                inserirFim(listaInters, l2Temp->valor);
            }
            l2Temp = l2Temp->prox;
        }
        lTemp = lTemp->prox;
    }
    removeRepetidos(listaInters);
    return listaInters;
}

int mainn(){
    int n, n2;
    Lista* l = criarLista();
    Lista* l2 = criarLista();
    scanf("%d",&n);
    while(n != 0){
        if(n!=0){
            inserirFim(l,n);
        }
        scanf("%d",&n);
    }
    
    scanf("%d",&n2);
    while(n2 != 0){
        if(n2!=0){
            inserirFim(l2,n2);
        }
        scanf("%d",&n2);
    }
    printf("Lista 1: ");
    imprimirLista(l);
    printf("\n");
    
    printf("Lista 2: ");
    imprimirLista(l2);
    printf("\n");
    
    Lista* lu = uniaoLista(l, l2);
    
    printf("Uniao: ");
    imprimirLista(lu);
    printf("\n");
    Lista* li = intersLista(l, l2);
    
    printf("Intersecao: ");
    imprimirLista(li);
    return 0;
}

