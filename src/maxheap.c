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

void imprimeHeap(MaxHeap *heap) {
  for (int i = 0; i < heap->size; i++) {
    printf("Aeronave %d: %s (Prioridade: %d)\n", i + 1,
           heap->aeronave[i].identificador, heap->aeronave[i].prioridade);
  }
}

void imprimeMaiorPrioridade(MaxHeap *heap) {
  printf("Maior prioridade: %s (Prioridade: %d)",
         heap->aeronave[0].identificador, heap->aeronave[0].prioridade);
}

void heapifyUp(MaxHeap *heap, int index) {
  int parent = (index - 1) / 2;
  if (parent >= 0 &&
      heap->aeronave[index].prioridade > heap->aeronave[parent].prioridade) {
    Aeronave temp = heap->aeronave[index];
    heap->aeronave[index] = heap->aeronave[parent];
    heap->aeronave[parent] = temp;
    heapifyUp(heap, parent);
  }
}

void heapifyDown(MaxHeap *heap, int index) {
  int leftChild = 2 * index + 1;
  int rightChild = 2 * index + 2;
  int largest = index;

  if (leftChild < heap->size && heap->aeronave[leftChild].prioridade >
                                    heap->aeronave[largest].prioridade) {
    largest = leftChild;
  }
  if (rightChild < heap->size && heap->aeronave[rightChild].prioridade >
                                     heap->aeronave[largest].prioridade) {
    largest = rightChild;
  }
  if (largest != index) {
    Aeronave temp = heap->aeronave[index];
    heap->aeronave[index] = heap->aeronave[largest];
    heap->aeronave[largest] = temp;
    heapifyDown(heap, largest);
  }
}

MaxHeap *removePrimeiraAeronave(MaxHeap *heap) {
  if (heap->size <= 0) {
    printf("Heap está vazia. Não há aeronaves para remover.\n");
    return heap;
  }

  heap->aeronave[0] = heap->aeronave[heap->size - 1];
  heap->size--;

  heapifyDown(heap, 0);

  return heap;
}

MaxHeap *editarAeronave(MaxHeap *heap) {
  printf(
      "Escolha uma aeronave para editar as informações (insira o indice):\n");
  imprimeHeap(heap);
  int indice;
  scanf("%d", &indice);

  if (indice < 0 || indice >= heap->size) {
    printf("Índice inválido.\n");
    return heap;
  }

  printf("Digite as novas informações (combustível, horário, tipo, "
         "emergência):\n");
  int combustivel, horario, tipo, emergencia;
  scanf("%d %d %d %d", &combustivel, &horario, &tipo, &emergencia);

  heap->aeronave[indice] = criaAeronave(heap->aeronave[indice].identificador,
                                        combustivel, horario, tipo, emergencia);
  heapifyUp(heap, indice);
  heapifyDown(heap, indice);

  return heap;
}
