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

Arv* InsereArv (Arv* raiz, Arv* no) {
    Arv* a = (Arv*) malloc (sizeof(Arv));
    a -> info = info;
    a -> esq = subE;
    a -> dir = subD;
    return a;
}
