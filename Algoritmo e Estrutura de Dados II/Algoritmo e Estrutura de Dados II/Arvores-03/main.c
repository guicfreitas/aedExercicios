//
//  main.c
//  Algoritmo e Estrutura de Dados II
//
//  Created by João Guilherme on 24/04/21.
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
    }else if(no -> info > raiz->info){
        raiz->dir = insereArv(raiz->dir, no);
    }
    
    return raiz;

}

void printArv(Arv* raiz){
    if(raiz != NULL){
        printf("%d ",raiz->info);
        printArv(raiz->esq);
        printArv(raiz->dir);
    }
}

int contaNos(Arv* raiz){
    int cont = 0;
    
    if(raiz != NULL){
        
        if(raiz->esq != NULL || raiz->dir != NULL){
            
            cont = cont + contaNos(raiz->esq);
            cont = cont + contaNos(raiz->dir);
        }else{
            cont = cont + 1;
        }
        
        
    }
    
    return cont;
    
}


int main(){
    int nEntradas = 0;
    int entrada = 0;
    scanf("%d",&nEntradas);
    
    Arv* raiz = criaVazia();
    
    for(int cont = 0;cont<nEntradas;cont++){
        scanf("%d",&entrada);
        Arv* novoNo;
        novoNo = criaNo(entrada);
        raiz = insereArv(raiz, novoNo);
        
        
    }
    printf("folhas: %d",contaNos(raiz));
    
    
    return 0;
}

