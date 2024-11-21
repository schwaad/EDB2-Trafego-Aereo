#include "../include/maxheap.h"
#include "../include/aeronave.h"
#include <stdio.h>
#include <stdlib.h>

MaxHeap *criaHeap() {
  MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
  if (heap != NULL) {
    heap->size = 0;
    heap->aeronave = NULL;
    heap->capacity = 0;
  }
  return heap;
}

MaxHeap *redimensionaHeap(MaxHeap *heap) {
  if (heap->capacity == 0) {
    heap->capacity = 1;
    heap->aeronave = (Aeronave *)malloc(heap->capacity * sizeof(Aeronave));
  } else {
    heap->capacity *= 2;
    heap->aeronave =
        (Aeronave *)realloc(heap->aeronave, heap->capacity * sizeof(Aeronave));
  }

  if (heap->aeronave == NULL) {
    fprintf(stderr, "Erro ao redimensionar a heap.\n");
    exit(EXIT_FAILURE);
  }

  return heap;
}

MaxHeap *insereAeronave(Aeronave aeronave, MaxHeap *heap) {
  if (heap->size >= heap->capacity) {
    heap = redimensionaHeap(heap);
  }

  int i = heap->size++;
  while (i > 0 &&
         aeronave.prioridade > heap->aeronave[(i - 1) / 2].prioridade) {
    heap->aeronave[i] = heap->aeronave[(i - 1) / 2];
    i = (i - 1) / 2;
  }
  heap->aeronave[i] = aeronave;
  return heap;
}

void liberaHeap(MaxHeap *heap) {
  free(heap->aeronave);
  free(heap);
}
