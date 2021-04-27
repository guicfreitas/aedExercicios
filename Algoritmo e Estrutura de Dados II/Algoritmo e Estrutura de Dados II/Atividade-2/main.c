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
typedef struct no No;
typedef struct lista Lista;

char classes[4] = {'M','V','E','C'};
char letras[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char numeros[9] = {'1','2','3','4','5','6','7','8','9'};

struct no{
    int hora;
    int ocorrencia;
    No* prox;
    No* anterior;
};

struct lista{
    No* inicio;
    No* fim;
};

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
    float valor;
};

Lista* criarLista(){
    Lista* l = malloc(sizeof(Lista));
    l->inicio=NULL;
    l->fim=NULL;
    return l;
}

void inserirFim(Lista* l,int hora,int ocorrencia){
    No* novo =(No*) malloc(sizeof(No));
    novo->hora=hora;
    novo->ocorrencia = ocorrencia;
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

int gerarNumero(int min,int max){
    int random = 0;
    
    
    random = (min + (rand()%max));
    
    return random;
}

Carro* criarCarro(char classe){
    Carro* novoCarro = (Carro*) malloc(sizeof(Carro));
    
    char* placa = (char*)malloc(sizeof(char)*8) ;
    
    placa[0] = letras[gerarNumero(0, 26)];
    placa[1] = letras[gerarNumero(0, 26)];
    placa[2] = letras[gerarNumero(0, 26)];
    placa[3] = numeros[gerarNumero(0, 9)];
    placa[4] = numeros[gerarNumero(0, 9)];
    placa[5] = numeros[gerarNumero(0, 9)];
    placa[6] = numeros[gerarNumero(0, 9)];
    placa[7] = '\0';
    
    
    novoCarro->placa = placa;
    novoCarro->classe = classe;
    int horaEntrada = gerarNumero(1, 24);
    novoCarro->horaEntrada = horaEntrada;
    int minutoEntrada = gerarNumero(0, 59);
    novoCarro->minutoEntrada = minutoEntrada;
    int horaSaida = gerarNumero(novoCarro->horaEntrada, 10);
    novoCarro->horaSaida = horaSaida;
    int minutoSaida = gerarNumero(0, 59);
    novoCarro->minutoSaida = minutoSaida;
    
    float valorPagar = ((novoCarro->horaSaida*60) + novoCarro->minutoSaida) - ((novoCarro->horaEntrada*60) + novoCarro->minutoEntrada);
    
    valorPagar = valorPagar * 0.05;
    
    novoCarro->valor = valorPagar;
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
int alturaAvl(Vaga* vaga){
    if(vaga == NULL){
        return -1;
    }else{
        return vaga->altura;
    }
}

int fatorBalanceamento(Vaga* raiz){
    if(raiz == NULL){
        return 0;
    }
    
    return alturaAvl(raiz->esq) - alturaAvl(raiz->dir);
}

Vaga* buscaVagaMaisLonge(Vaga* raiz){
    if(raiz != NULL){
        while (raiz->dir != NULL) {
            raiz = raiz->dir;
        }
    }
    
    return raiz;
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
        raiz->classe = classes[gerarNumero(0, 4)];
        Carro* novoCarro = criarCarro(raiz->classe);
        raiz->carro = novoCarro;
        
        raiz->numero = numeroVaga;
        raiz->altura = 0;
        
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


void emordem(Vaga* raiz)
{
    if (raiz == NULL)
        return;
    
    emordem(raiz->esq);
    printf("Vaga: %d\n",raiz->numero);
    printf("Placa: %s\n",raiz->carro->placa);
    printf("Valor pago: %0.2f\n\n",raiz->carro->valor);
    emordem(raiz->dir);
}



int quantidadeCarrosEstacionado(Vaga* raiz){
    int cont = 0;
    
    if(raiz != NULL){
        cont = cont + 1;
        cont = cont +  quantidadeCarrosEstacionado(raiz->esq);
        cont = cont + quantidadeCarrosEstacionado(raiz->dir);
    }
    return cont;
}

float diferencaHora(Carro* carro){
    float horaTotalS = (carro->horaSaida * 60) + (carro->minutoSaida);
    float horaTotalE = (carro->horaEntrada * 60) + (carro->minutoEntrada);
    
    return horaTotalS - horaTotalE;
}

float mediaHoras(Vaga* raiz){
    float total = 0.0;
    
    if(raiz != NULL){
        total = total + diferencaHora(raiz->carro);
        
        
        total = total + mediaHoras(raiz->esq);
        
        
        total = total + mediaHoras(raiz->dir);
        
        
        
    }
    
    return total;
}
int contCarroPorHora(Vaga* raiz, int hora){
    int cont = 0;
    if(raiz != NULL){
        if(raiz->carro->horaEntrada == hora){
            cont = cont + 1;
        }
        cont = cont + contCarroPorHora(raiz->esq, hora);
        cont = cont + contCarroPorHora(raiz->dir, hora);
    }
    return cont;
}

void insereCarrosPorHora(Vaga* raiz, Lista* l){
    if(raiz != NULL){
        inserirFim(l, raiz->carro->horaEntrada, contCarroPorHora(raiz, raiz->carro->horaEntrada));
        insereCarrosPorHora(raiz->esq, l);
        insereCarrosPorHora(raiz->dir, l);
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
            if(analisado->hora == atual->hora && analisado != atual){
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

void verificaHoraMovimentada(Lista* l){
    No* atual = l->inicio->prox;
    No* atualMaior = l->inicio;
    
    while (atual != NULL) {
        if(atual->ocorrencia > atualMaior->ocorrencia){
            atualMaior = atual;
        }
        atual = atual->prox;
    }
    
    printf("Hora com mais carros estacionados foi as %d com %d carros estacionados.\n\n",atualMaior->hora,atualMaior->ocorrencia);
}

Vaga* removeVaga(Vaga* raiz, int nVaga){
    if(raiz == NULL){
        return NULL;
    }
    
    if(nVaga < raiz->numero){
        raiz->esq = removeVaga(raiz->esq, nVaga);
    }else{
        if(nVaga > raiz->numero){
            raiz->dir = removeVaga(raiz->dir, nVaga);
        }else{
            Vaga* temp = raiz;
            if((raiz->esq) && (raiz->dir)){
                Vaga* pai = raiz->dir;
                raiz = pai->esq;
                if(raiz){
                    while(raiz->esq){
                        pai = raiz;
                        raiz = raiz->esq;
                    }
                    pai->esq = raiz->dir;
                    raiz->dir = temp->dir;
                }else{
                    raiz = pai;
                    raiz->esq = temp->esq;
                }
            }else{
                if(raiz->esq){
                    raiz = raiz->esq;
                }else{
                    raiz = raiz->dir;
                }
                free(temp);
            }
        }
    }
    return raiz;
}

Vaga* balancearArv(Vaga* raiz){
    if(raiz == NULL){
        return NULL;
    }
    int fator = fatorBalanceamento(raiz);
    
    if(fator > 1 && fatorBalanceamento(raiz->esq) >= 0){
        return rotacaoDireita(raiz);
    }
    if(fator < -1 && fatorBalanceamento(raiz->dir) <= 0){
        return rotacaoEsquerda(raiz);
    }
    if(fator > 1 && fatorBalanceamento(raiz->esq) < 0){
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }
    if(fator < -1 && fatorBalanceamento(raiz->dir) > 0){
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }
    return raiz;
}

void excluirArv(Vaga* raiz){
    if(raiz != NULL){
        excluirArv(raiz->dir);
        excluirArv(raiz->esq);
        free(raiz);
    }
}

int main(){
    Vaga* raiz = NULL;
    int numeroAleatorio = 0;
    srand ((unsigned int)time(NULL) );
    
    printf("Digite o numero de carros estacionados:\n");
    int numeroEntradas = 0;
    scanf("%d",&numeroEntradas);
    
    for(int cont = 0;cont < numeroEntradas; cont++){
        numeroAleatorio = gerarNumero(0, 1024);
        if(busacaVaga(numeroAleatorio, raiz) == NULL){
            raiz = insereVagaOcupada(numeroAleatorio, raiz);
        }else{
            //VAGA ESTA PREENCHIDA DIRENCIONANDO PARA OUTRA VAGA!
            numeroAleatorio = gerarNumero(0, 1024);
            while (busacaVaga(numeroAleatorio, raiz) != NULL) {
                numeroAleatorio = gerarNumero(0, 1024);
            }
            raiz = insereVagaOcupada(numeroAleatorio, raiz);
            
        }
        
    }
    
    int qtdCarros = quantidadeCarrosEstacionado(raiz);
    float mediaH = (mediaHoras(raiz)/qtdCarros)/60.0;
    printf("\n");
    printf("Media de carros estacionados: %d\n",qtdCarros);
    printf("Media de horas: %0.2f\n",mediaH);
    
    Lista* listaDeCarrosHora = criarLista();
    insereCarrosPorHora(raiz, listaDeCarrosHora);
    removeRepetidos(listaDeCarrosHora);
    verificaHoraMovimentada(listaDeCarrosHora);
    int escolha = -1;
    int vagaPesquisada = 0;
    while(escolha != 0){
        printf("Escolha uma das opcoes abaixo:\n");
        printf("1 - Esvaziar uma vaga específica \n");
        printf("2 - Esvaziar todas as vagas(todas as vagas serao impressas)\n");
        printf("0 - Sair\n");
        
        scanf("%d",&escolha);
        
        switch (escolha) {
            case 1:
                printf("Digite a vaga a ser esvaziada: \n");
                scanf("%d",&vagaPesquisada);
                Vaga* vagaTemp = busacaVaga(vagaPesquisada, raiz);
                if(vagaTemp == NULL){
                    printf("Vaga esta desocupada!\n");
                }else{
                    printf("Placa: %s\n",vagaTemp->carro->placa);
                    printf("Valor pago: %0.2f\n",vagaTemp->carro->valor);
                    raiz = removeVaga(raiz, vagaPesquisada);
                    raiz = balancearArv(raiz);
                }
                
                break;
                
            case 2:
                printf("Esvaziando as vagas: \n");
                emordem(raiz);
                excluirArv(raiz);
                escolha = 0;
                break;
            case 0:
                break;
            default:
                break;
        }
        
    }
    
    
    
    
    
    
    return 0;
}
