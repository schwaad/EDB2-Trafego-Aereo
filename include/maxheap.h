#include "./aeronave.h"

typedef struct {
  Aeronave *aeronave;
  int size;
  int capacity;
} MaxHeap;

MaxHeap *criaHeap();

MaxHeap *redimensionaHeap(MaxHeap *heap);

MaxHeap *insereAeronave(Aeronave aeronave, MaxHeap *heap);

void liberaHeap(MaxHeap *heap);

void imprimeHeap(MaxHeap *heap);

void imprimeMaiorPrioridade(MaxHeap *heap);

MaxHeap *removePrimeiraAeronave(MaxHeap *heap);

MaxHeap *editarAeronave(MaxHeap *heap);

MaxHeap *heapifyUp(MaxHeap *heap, int index);

MaxHeap *carregaHeap(const char *caminho);

void salvaHeap(const MaxHeap *heap, const char *caminho);

MaxHeap *heapifyDown(MaxHeap *heap, int index);
