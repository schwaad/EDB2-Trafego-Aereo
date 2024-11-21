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

void heapifyUp(MaxHeap *heap, int index);

void heapifyDown(MaxHeap *heap, int index);
