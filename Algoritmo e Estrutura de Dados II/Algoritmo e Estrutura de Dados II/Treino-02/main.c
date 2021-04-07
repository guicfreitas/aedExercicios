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
    
    if(l->inicio == NULL){
        l->inicio = novo;
        novo->prox = NULL;
    }else{
        
        No* noTemp;
        noTemp = l->inicio;
        while(noTemp->prox != NULL){
            noTemp = noTemp->prox;
        }
        
        noTemp->prox = novo;
        novo->prox = NULL;
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

No* reverteRecursivo(No* atual){
    if(atual == NULL || atual->prox == NULL){
        return atual;
    }
    
    No* prox = atual->prox;
    atual->prox = NULL;
    No* inicio = reverteRecursivo(prox);
    prox->prox = atual;
    return inicio;
}

int main(){
    int n;
    Lista* l = criarLista();
        
    while(scanf("%d",&n)!=EOF){
        inserirFim(l,n);
    }
   
    l->inicio = reverteRecursivo(l->inicio);
    imprimirLista(l);
    return 0;
}
