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
    int cont = 1;
    Piloto* temp = l-> inicio;
    printf("-----------------------------");
    printf("\n");
    printf("| pos. | plto | eqp | tempo |\n");
    if(temp != NULL){
        if(temp->proxPiloto == NULL){
            printf("|  %02d  |  %02d  |  %c  | %d |\n",cont,temp->numero,temp->equipe,temp->tempo);
            
        }else{
            printf("|  %02d  |  %02d  |  %c  | %d |\n", cont,temp->numero,temp->equipe,temp->tempo);
                temp = temp->proxPiloto;
            cont++;
            while(temp != NULL){
                if(temp->vaiCorrer == 0){
                printf("|  %02d  |  %02d  |  %c  | %d |\n", cont,temp->numero,temp->equipe,temp->tempo);
                    cont++;

                }
                temp = temp->proxPiloto;
            }
        }
        
    }
    printf("-----------------------------\n");
    
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
        pilotoAleatorio = gerarNumero(quantidadePilotos(listaTotal)+1);
        igual = verificaIgualdade(listaVolta, pilotoAleatorio);
        while(igual == 0){
            pilotoAleatorio = gerarNumero(quantidadePilotos(listaTotal)+1);
            igual = verificaIgualdade(listaVolta, pilotoAleatorio);
        }
        
        inserirFim(listaVolta, gerarNumero(50000), pilotoAleatorio, '*', 0);
        cont++;
    }
    guardarMenorTempo(listaTotal, listaVolta);
    if(listaVolta->inicio != NULL){
        excluirLista(listaVolta);
    }
    
}
void Qualify(ListaPilotos* listaTotal, int voltas){
    int numeroDeCarrosVolta = 0;
    
    for(int cont = 0;cont < voltas;cont++){
        numeroDeCarrosVolta = gerarNumero(quantidadePilotos(listaTotal));
        gerarVolta(listaTotal, numeroDeCarrosVolta);
        
    }
}

void troca(ListaPilotos* l,Piloto* p1, Piloto* p2,Piloto* pAnterior){
    
    if(p1 == l->inicio){
        p1->proxPiloto = p2->proxPiloto;
        p2->proxPiloto = p1;
        l->inicio = p2;
    }else if(p2->proxPiloto == NULL){
        pAnterior->proxPiloto = p2;
        p2->proxPiloto = p1;
        p1->proxPiloto = NULL;
    }else{
        p1->proxPiloto = p2->proxPiloto;
        pAnterior->proxPiloto = p2;
        p2->proxPiloto = p1;
    }
}
void ordernaLista(ListaPilotos* l){
   
    Piloto* anterior = l->inicio;
    
    for(Piloto* i = l->inicio;i != NULL;i=i->proxPiloto){
        anterior = l->inicio;
        for(Piloto* j = l->inicio->proxPiloto;j!=NULL;j=j->proxPiloto){
            if(j->tempo < i->tempo){
                troca(l, i, j, anterior);
            }
            anterior = j;
        }
    }
    
}

void removePiloto(ListaPilotos* l, Piloto* pilotoRemovido){
    Piloto* pAtual = l->inicio->proxPiloto;
    Piloto* pAnterior = l->inicio;
    
    if(l->inicio == pilotoRemovido){
        l->inicio = pilotoRemovido->proxPiloto;
        free(pilotoRemovido);
    }else{
        while(pAtual != pilotoRemovido && pAtual != NULL){
            pAnterior = pAtual;
            pAtual = pAtual->proxPiloto;
        }
        
        
        
        if(pilotoRemovido!=NULL){
            pAnterior->proxPiloto = pilotoRemovido->proxPiloto;
            free(pilotoRemovido);
        }
    }
}

Piloto* ultimoElemento(ListaPilotos* l){
    Piloto* pUltimo = l->inicio;
    while(pUltimo->proxPiloto != NULL){
        pUltimo = pUltimo->proxPiloto;
    }
    return pUltimo;
}

void claSort(ListaPilotos* l){
    Piloto* p = l->inicio;
    Piloto* pComMenorTempo;
    Piloto* pMenorAtual = p;
    int menorTempo = p->tempo;
    p = p->proxPiloto;
    //primeiro Menor
    
    while(p != NULL){
        if(p->tempo < menorTempo){
            menorTempo = p->tempo;
            pMenorAtual = p;
        }
        p = p->proxPiloto;
    }
    
    inserirFim(l, pMenorAtual->tempo, pMenorAtual->numero, pMenorAtual->equipe, pMenorAtual->vaiCorrer);
    removePiloto(l, pMenorAtual);
    pComMenorTempo = ultimoElemento(l);
    
    
        p = l->inicio;
        menorTempo = p->tempo;
        while(l->inicio != pComMenorTempo){
            p = l->inicio;
            menorTempo = p->tempo;
            pMenorAtual = p;
            while (p->proxPiloto != NULL && p != pComMenorTempo) {
                if(p->tempo < menorTempo){
                    menorTempo = p->tempo;
                    pMenorAtual = p;
                }
                p = p->proxPiloto;
                
            }
            
            inserirFim(l, pMenorAtual->tempo, pMenorAtual->numero, pMenorAtual->equipe, pMenorAtual->vaiCorrer);
            removePiloto(l, pMenorAtual);
            
        }
    
}

void elimina7(ListaPilotos* l,int ate){
    Piloto* pAtual = l->inicio;
    int cont = 1;
    while(pAtual != NULL){
        if(cont > ate){
            pAtual->vaiCorrer = 1;
        }
        pAtual = pAtual->proxPiloto;
        cont++;
    }
}

void liberaTodos(ListaPilotos* l){
    Piloto* p = l->inicio;
    while(p!=NULL){
        p->vaiCorrer = 0;
        p = p->proxPiloto;
    }
}

int main(){
    int flag = 0;
    srand ((unsigned int)time(NULL) );
    ListaPilotos* l = TotalCarros();
    //imprimirPilotos(l);
    scanf("%d",&flag);
    if(flag == 1){
        printf("Q1\n");
        Qualify(l, QUALIFY1);
        //imprimirPilotos(l);
        claSort(l);
        imprimirPilotos(l);
        
        elimina7(l,17);
        
        Qualify(l, QUALIFY2);
        printf("Q2\n");
        claSort(l);
        imprimirPilotos(l);
        elimina7(l,10);
        
        Qualify(l, QUALIFY3);
        printf("Q3\n");
        claSort(l);
        imprimirPilotos(l);
       
        printf("GRID LARGADA\n");
        liberaTodos(l);
        imprimirPilotos(l);
        
    }
    
    
    
    
    
    return 0;
}



