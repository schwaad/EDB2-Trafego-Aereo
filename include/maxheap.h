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
