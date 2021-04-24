//
//  main.c
//  Algoritmo e Estrutura de Dados II
//
//  Created by João Guilherme on 16/04/21.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct arv Arv;
struct arv {
    int info;
    Arv* esq;
    Arv* dir;
};

Arv* criaVazia() {
    return NULL;
}

Arv* criaNo(int info){
    Arv* novoNo = (Arv*) malloc (sizeof(Arv));
    novoNo -> info = info;
    novoNo -> esq = NULL;
    novoNo -> dir = NULL;
    
    return novoNo;
}
//aceitando numero iguais
Arv* insereArv (Arv* raiz, Arv* no) {
    if(raiz == NULL){
        return no;
    }
    
    if(no->info < raiz->info){
        raiz->esq = insereArv(raiz->esq, no);
    }else{
        raiz->dir = insereArv(raiz->dir, no);
    }
    
    return raiz;

}
