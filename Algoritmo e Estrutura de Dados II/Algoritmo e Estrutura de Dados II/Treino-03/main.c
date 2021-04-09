//
//  main.c
//  Algoritmo e Estrutura de Dados II
//
//  Created by João Guilherme on 07/04/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista Lista;
typedef struct no No;

struct no{
    No* prox;
    int recorrencia;
    char valor[100];
};

struct lista{
    No* inicio;
};

Lista* criarLista(){
    Lista* l = malloc(sizeof(Lista));
    l->inicio=NULL;
    return l;
}

void inserirFim(Lista* l,char valor[]){
    No* novo =(No*) malloc(sizeof(No));
    strcpy(novo->valor,valor);
    novo->recorrencia = 0;
    
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
    int contPalavras = 0;
    int maiorAtual = l->inicio->recorrencia;
    No* maiorIncidencia = l->inicio;
    No* temp = l-> inicio;
    if(temp != NULL){
        if(temp->prox == NULL){
            printf("%s (%d)", temp->valor,temp->recorrencia);
            contPalavras += 1;
            
        }else{
                maiorIncidencia = temp;
                printf("%s (%d)", temp->valor,temp->recorrencia);
                temp = temp->prox;
                contPalavras += 1;
            
            while(temp != NULL){
                printf("\n%s (%d)", temp->valor,temp->recorrencia);
                temp = temp->prox;
                contPalavras += 1;
                
            }
        }
    }
    temp = l->inicio;
    while(temp != NULL){
        if(temp->recorrencia > maiorAtual){
            maiorAtual = temp->recorrencia;
            maiorIncidencia = temp;
        }
        temp = temp->prox;
    }
    printf("\nTotal de palavras: %d\n",contPalavras);
    printf("Maior incidencia: %s - %d vezes",maiorIncidencia->valor,maiorIncidencia->recorrencia);
}

void removeNo(Lista* l, No* valor){
    No* anterior;
    No* atual;
    
    if(l->inicio == valor){
        l->inicio = valor->prox;
        free(valor);
        
    }
    
    anterior = l->inicio;
    atual = l->inicio->prox;
    while(atual != valor){
        anterior = atual;
        atual = atual->prox;
    }
    anterior->prox = valor->prox;
    free(valor);
}
void removeRepetido(Lista* l){
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
            if(strcmp(analisado->valor, atual->valor) == 0 && analisado != atual){
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

void inserirSeparado(Lista* l,char texto[]){
    char palavraAtual[100];
    
        
    inserirFim(l, palavraAtual);
   
    removeRepetido(l);
}

void palavrasRecorrentes(Lista* l, Lista* listaPalavras){
    No* palavraAtual = l->inicio;
    No* palavraAnalisada = listaPalavras->inicio;
    
    while(palavraAtual != NULL){
        palavraAnalisada = listaPalavras->inicio;
        while(palavraAnalisada != NULL){
            if(strcmp(palavraAtual->valor, palavraAnalisada->valor)==0){
                palavraAtual->recorrencia += 1;
            }
            palavraAnalisada = palavraAnalisada->prox;
        }
        palavraAtual = palavraAtual->prox;
    }
}

void separarPalavra (Lista* l,Lista* listaPalavras, char palavra[]){
    int cont = 0;
    int contInicial = 0;
    char palavra1[50];
    char palavra2[50] = "\0";
    int i = 0;
    
    while(cont < strlen(palavra) && palavra[cont] != ':' && palavra[cont] != ',' && palavra[cont] != '.' && palavra[cont] != '.' && palavra[cont] != '-' && palavra[cont] != '?' && palavra[cont] != '!'){
        cont++;
    }
    
    strncpy(palavra1, palavra,cont);
    contInicial = cont;
    for(cont = cont+1  ;cont < strlen(palavra);cont++){
        palavra2[i] = palavra[cont];
        i++;
    }
    
    inserirFim(l, palavra1);
    inserirFim(listaPalavras, palavra1);
    
    if(contInicial <= strlen(palavra2)){
        inserirFim(l, palavra2);
        inserirFim(listaPalavras, palavra2);
    }
    
}

int main(){
    char texto[100] = "";
    int temPonto = 0;
    
    Lista* l = criarLista();
    Lista* listaPalvras = criarLista();
    
    
    while(scanf("%s",texto)!=EOF){
        temPonto = 0;
        for(int cont = 0;cont<strlen(texto);cont++){
            if(texto[cont] == ':' || texto[cont] == ',' || texto[cont] == '.' || texto[cont] == '-' || texto[cont] == '?' || texto[cont] == '!'){
                temPonto = 1;
            }
        }
        
        if(temPonto == 0){
            inserirFim(l, texto);
            inserirFim(listaPalvras, texto);
        }else{
            separarPalavra(l, listaPalvras, texto);
        }
        
        
        
    }
    
    removeRepetido(l);
    palavrasRecorrentes(l, listaPalvras);
    imprimirLista(l);
    
    
    return 0;
}
