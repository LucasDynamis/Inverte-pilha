#include <stdio.h>
#include <stdlib.h>
typedef struct celula {
 int item;
 struct celula* prox;
} TipoCelula;
typedef struct {
 TipoCelula* topo;
} TipoPilha;
void CriaPilhaVazia(TipoPilha* pilha) {
 pilha->topo = NULL;
}
int TestaPilhaVazia(TipoPilha* pilha) {
 return (pilha->topo == NULL);
}
void InserePilha(TipoPilha* pilha, int item) {
 TipoCelula* novaCelula = (TipoCelula*)malloc(sizeof(TipoCelula));
 novaCelula->item = item;
 novaCelula->prox = pilha->topo;
 pilha->topo = novaCelula;
}
void RemovePilha(TipoPilha* pilha, int* item) {
 if (TestaPilhaVazia(pilha)) {
 printf("Erro: pilha vazia!\n");
 return;
 }
 TipoCelula* aux = pilha->topo;
 *item = aux->item;
 pilha->topo = aux->prox;
 free(aux);
}
typedef struct {
 TipoCelula* frente;
 TipoCelula* tras;
} TipoFila;
void CriaFilaVazia(TipoFila* fila) {
 fila->frente = (TipoCelula*)malloc(sizeof(TipoCelula));
 fila->frente->prox = NULL;
 fila->tras = fila->frente;
}
int TestaFilaVazia(TipoFila* fila) {
 return (fila->frente == fila->tras);
}
void InsereFila(TipoFila* fila, int item) {
 fila->tras->prox = (TipoCelula*)malloc(sizeof(TipoCelula));
 fila->tras = fila->tras->prox;
 fila->tras->item = item;
 fila->tras->prox = NULL;
}
void RemoveFila(TipoFila* fila, int* item) {
 if (TestaFilaVazia(fila)) {
 printf("Erro: fila vazia!\n");
 return;
 }
 TipoCelula* aux = fila->frente;
 fila->frente = fila->frente->prox;
 *item = fila->frente->item;
 free(aux);
}
void InverterFila(TipoFila* fila) {
 TipoPilha pilha;
 CriaPilhaVazia(&pilha);
 int item;
 while (!TestaFilaVazia(fila)) {
 RemoveFila(fila, &item);
 InserePilha(&pilha, item);
 }
 while (!TestaPilhaVazia(&pilha)) {
 RemovePilha(&pilha, &item);
 InsereFila(fila, item);
 }
}
// Função de exemplo para testar a inversão de nós da fila
int main() {
 TipoFila fila;
 CriaFilaVazia(&fila);
 InsereFila(&fila, 1);
 InsereFila(&fila, 2);
 InsereFila(&fila, 3);
 InsereFila(&fila, 4);
 printf("Fila original: ");
 TipoCelula* celula = fila.frente->prox;
 while (celula != NULL) {
 printf("%d ", celula->item);
 celula = celula->prox;
 }
 printf("\n");
 InverterFila(&fila);
 printf("Fila invertida: ");
 celula = fila.frente->prox;
 while (celula != NULL) {
 printf("%d ", celula->item);
 celula = celula->prox;
 }
 printf("\n");
 return 0;
}