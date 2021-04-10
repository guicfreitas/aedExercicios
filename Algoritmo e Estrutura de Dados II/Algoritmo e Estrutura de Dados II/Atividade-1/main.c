//
//  main.c
//  Algoritmo e Estrutura de Dados II
//
//  Created by João Guilherme on 09/04/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define QUALIFY1 10
#define QUALIFY2 8
#define QUALIFY3 5
#define NUMERO_PILOTOS 24

typedef struct piloto Piloto;
typedef struct listaPilotos ListaPilotos;

struct piloto{
    int tempo;
    int numero;
    char equipe;
    //sim == 0, nao == 1
    int vaiCorrer;
    Piloto* proxPiloto;
};

struct listaPilotos{
    Piloto* inicio;
};

int gerarNumero(int max){
    int random = 0;
    
    //srand ( (unsigned int) time(NULL) );
     random = rand()%max;
    
    return random;
}
void excluirLista(ListaPilotos* l){
    Piloto* atual = l->inicio;
    Piloto* temp;
    
    while(atual->proxPiloto != NULL){
        temp = atual;
        atual = atual->proxPiloto;
        
        free(temp);
    }
    
    free(l);
}

void inserirFim(ListaPilotos* l, int tempo, int numero, char equipe, int vaiCorrer){
    Piloto* novoP =(Piloto*) malloc(sizeof(Piloto));
    novoP->tempo = tempo;
    novoP->numero = numero;
    novoP->equipe = equipe;
    novoP->vaiCorrer = vaiCorrer;
    
    if(l->inicio == NULL){
        l->inicio = novoP;
        novoP->proxPiloto = NULL;
    }else{
        
        Piloto* pilotoTemp;
        pilotoTemp = l->inicio;
        while(pilotoTemp->proxPiloto != NULL){
            pilotoTemp = pilotoTemp->proxPiloto;
        }
        
        pilotoTemp->proxPiloto = novoP;
        novoP->proxPiloto = NULL;
    }
}


ListaPilotos* TotalCarros(){
    int cont = 1;
    int contLetra = 0;
    int equipeRand = 0;
    char equipePiloto = '\0';
    
    ListaPilotos* l = (ListaPilotos*) malloc(sizeof(ListaPilotos));
    l->inicio = NULL;
    
    char equipes[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    
    while(cont <= NUMERO_PILOTOS){
        
        
        if (contLetra == 0){
            equipeRand = gerarNumero(25);
            equipePiloto = equipes[equipeRand];
            while(equipePiloto == '*'){
                equipeRand = gerarNumero(25);
                equipePiloto = equipes[equipeRand];
            }
            inserirFim(l, 50000, cont, equipePiloto, 0);
            contLetra++;
        }else if (contLetra == 1){
            inserirFim(l, 50000, cont, equipePiloto, 0);
            equipes[equipeRand] = '*';
            contLetra = 0;
        }
        cont++;
    }
    return l;
}

void imprimirPilotos(ListaPilotos* l){
    Piloto* temp = l-> inicio;
    printf("-----------------------------");
    printf("\n");
    printf("| pos. | plto | eqp | tempo |\n");
    if(temp != NULL){
        if(temp->proxPiloto == NULL){
            printf("|  %02d  |  %02d  |  %c  | %d |\n", temp->numero,temp->numero,temp->equipe,temp->tempo);
            
        }else{
            printf("|  %02d  |  %02d  |  %c  | %d |\n", temp->numero,temp->numero,temp->equipe,temp->tempo);
                temp = temp->proxPiloto;
            while(temp != NULL){
                printf("|  %02d  |  %02d  |  %c  | %d |\n", temp->numero,temp->numero,temp->equipe,temp->tempo);
                temp = temp->proxPiloto;
            }
        }
        
    }
    printf("-----------------------------");
    
}
ListaPilotos* criarLista(){
    ListaPilotos* l = (ListaPilotos*) malloc(sizeof(ListaPilotos));
    l->inicio = NULL;
    return l;
}
int quantidadePilotos(ListaPilotos* l){
    int cont = 0;
    Piloto* pTemp = l->inicio;
    while(pTemp!= NULL){
        if(pTemp->vaiCorrer == 0){
            cont++;
        }
        pTemp = pTemp->proxPiloto;
    }
    return cont;
}

int verificaIgualdade(ListaPilotos* listaAtual, int elemento){
    Piloto* pilotoTemp = listaAtual->inicio;
    //sim = 0, nao = 1
    int igual = 1;
    if(elemento == 0){
        return 0;
    }
    
    if(listaAtual->inicio == NULL || pilotoTemp->proxPiloto == NULL){
        igual = 1;
    }else{
        while(pilotoTemp != NULL){
            if(pilotoTemp->numero == elemento || pilotoTemp->vaiCorrer == 1){
                igual = 0;
            }
            pilotoTemp = pilotoTemp->proxPiloto;
        }
        
    }
    
    return igual;
}
void guardarMenorTempo(ListaPilotos* listaTotal, ListaPilotos* listaVolta){
    Piloto* pilotoTotal = listaTotal->inicio;
    Piloto* pilotoVolta = listaVolta->inicio;
    
    while(pilotoVolta != NULL){
        pilotoTotal = listaTotal->inicio;
        while(pilotoTotal != NULL){
            if(pilotoTotal->numero == pilotoVolta->numero){
                if(pilotoVolta->tempo < pilotoTotal->tempo){
                    pilotoTotal->tempo = pilotoVolta->tempo;
                }
            }
            
            pilotoTotal = pilotoTotal->proxPiloto;
        }
        pilotoVolta = pilotoVolta->proxPiloto;
    }
    
}
void gerarVolta(ListaPilotos* listaTotal, int numeroDePilotos){
    int cont = 0;
    int pilotoAleatorio = 0;
    int igual = 1;
    ListaPilotos* listaVolta = criarLista();
    while(cont < numeroDePilotos){
        pilotoAleatorio = gerarNumero(quantidadePilotos(listaTotal));
        igual = verificaIgualdade(listaVolta, pilotoAleatorio);
        while(igual == 0){
            pilotoAleatorio = gerarNumero(quantidadePilotos(listaTotal));
            igual = verificaIgualdade(listaVolta, pilotoAleatorio);
        }
        
        inserirFim(listaVolta, gerarNumero(50000), pilotoAleatorio, '*', 0);
        cont++;
    }
    guardarMenorTempo(listaTotal, listaVolta);
    excluirLista(listaVolta);
}
void Qualify(ListaPilotos* listaTotal, int voltas){
    int numeroDeCarrosVolta = 0;
    
    for(int cont = 0;cont < voltas;cont++){
        numeroDeCarrosVolta = gerarNumero(quantidadePilotos(listaTotal));
        gerarVolta(listaTotal, numeroDeCarrosVolta);
        
    }
}

int main(){
    
    ListaPilotos* l = TotalCarros();
    imprimirPilotos(l);
    
    Qualify(l, QUALIFY1);
    imprimirPilotos(l);
    
    return 0;
}

