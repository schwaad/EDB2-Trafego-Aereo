#include "../include/aeronave.h"
#include "../include/maxheap.h"
#include <stdio.h>

int main() {
  MaxHeap *heap = criaHeap();
  Aeronave aeronave1 = criaAeronave("ABC123", 1000, 540, 1, 0);
  Aeronave aeronave2 = criaAeronave("CDE456", 1000, 540, 1, 1);
  Aeronave aeronave3 = criaAeronave("FGH789", 1100, 540, 1, 0);
  insereAeronave(aeronave1, heap);
  insereAeronave(aeronave2, heap);
  insereAeronave(aeronave3, heap);
  imprimeHeap(heap);
  imprimeMaiorPrioridade(heap);
  removePrimeiraAeronave(heap);
  printf("\nDepois de remover a primeira:\n");
  imprimeHeap(heap);
}
