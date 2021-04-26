//
//  main.c
//  Algoritmo e Estrutura de Dados II
//
//  Created by João Guilherme on 25/04/21.
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
// nao aceitando numero iguais
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

Arv* buscaNo(Arv* raiz, int info, Arv** pai){
    Arv* atual = raiz;
    *pai = NULL;
    
    while(atual) {
        if(atual -> info == info ){
            return atual;
        }
        *pai = atual;
        if(info < atual->info){
            atual = atual->esq;
        }else{
            atual = atual->dir;
        }
    }
    return  NULL;
}

Arv* removeNo(Arv* raiz, int info){
    Arv* pai;
    Arv* no;
    Arv* p;
    Arv* q;
    
    no = buscaNo(raiz, info, &pai);
    
    if(no == NULL){
        return raiz;
    }
    
    if(!no->esq || !no->dir){
        if(!no->esq){
            q = no->dir;
        }else{
            q = no->esq;
        }
    }else{
        p = no;
        q = no->esq;
        
        while (q->dir) {
            p = q;
            q = q->dir;
        }
        
        if(p != no){
            p -> dir = q->esq;
            q->esq = no->esq;
        }
        q->dir = no->dir;
    }
    if (!pai){
        free(no);
        return (q);
    }
    if(info < pai->info){
        pai->esq = q;
    }else{
        pai->dir = q;
    }
    
    free(no);
    return (raiz);
}

int verificaPar(Arv* raiz){
    int temPar = 0;
    if(raiz != NULL){
        if(raiz->info%2 == 0){
            temPar += 1;
        }else{
            temPar = temPar + verificaPar(raiz->esq);
            temPar = temPar + verificaPar(raiz->dir);
        }
    }
    return temPar;
}

void printArv(Arv* raiz){
    if(raiz != NULL){
        printf("%d ",raiz->info);
        printArv(raiz->esq);
        printArv(raiz->dir);
    }
}


void removePar(Arv* raiz){
    Arv* Atual = raiz;
    Arv* eq = raiz->esq;
    Arv* dr = raiz->dir;
    
    while (verificaPar(raiz) != 0) {
        if(Atual->info % 2 == 0){
            Atual = removeNo(raiz, raiz->info);
        }else{
           // Atual = atu
        }
            
    }
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
   
    
    
    return 0;
}
