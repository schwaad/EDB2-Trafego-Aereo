#include "../include/maxheap.h"
#include "../include/aeronave.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MaxHeap *criaHeap() {
  MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
  heap->size = 0;
  heap->capacity = 10;
  heap->aeronave = (Aeronave *)malloc(heap->capacity * sizeof(Aeronave));
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

void imprimeHeap(MaxHeap *heap) {
  MaxHeap *heapTemp = (MaxHeap *)malloc(sizeof(MaxHeap));
  heapTemp->capacity = heap->capacity;
  heapTemp->size = heap->size;
  heapTemp->aeronave = (Aeronave *)malloc(heap->capacity * sizeof(Aeronave));

  for (int i = 0; i < heap->size; i++) {
    heapTemp->aeronave[i] = heap->aeronave[i];
  }

  int indice = 1;
  while (heapTemp->size > 0) {
    Aeronave maiorPrioridade = heapTemp->aeronave[0];

    printf("Aeronave %d: %s (Prioridade: %d)\n", indice,
           maiorPrioridade.identificador, maiorPrioridade.prioridade);

    heapTemp->aeronave[0] = heapTemp->aeronave[heapTemp->size - 1];
    heapTemp->size--;

    heapifyDown(heapTemp, 0);
    indice++;
  }

  free(heapTemp->aeronave);
  free(heapTemp);
}

MaxHeap *insereAeronave(Aeronave aeronave, MaxHeap *heap) {
  if (heap->size >= heap->capacity) {
    heap = redimensionaHeap(heap);
  }

  // Inserir a nova aeronave na última posição da heap.
  heap->aeronave[heap->size] = aeronave;

  heap = heapifyUp(heap, heap->size);

  heap->size++;
  return heap;
}

void liberaHeap(MaxHeap *heap) {
  for (int i = 0; i < heap->size; i++) {
    free(heap->aeronave[i].identificador);
  }
  free(heap->aeronave);
  free(heap);
}

void imprimeMaiorPrioridade(MaxHeap *heap) {
  printf("Maior prioridade: %s (Prioridade: %d)",
         heap->aeronave[0].identificador, heap->aeronave[0].prioridade);
}

MaxHeap *heapifyUp(MaxHeap *heap, int index) {
  int parent = (index - 1) / 2;
  if (parent >= 0 &&
      heap->aeronave[index].prioridade > heap->aeronave[parent].prioridade) {
    Aeronave temp = heap->aeronave[index];
    heap->aeronave[index] = heap->aeronave[parent];
    heap->aeronave[parent] = temp;
    heapifyUp(heap, parent);
  }
  return heap;
}

MaxHeap *heapifyDown(MaxHeap *heap, int indice) {
  int filhoEsq = 2 * indice + 1;
  int filhoDir = 2 * indice + 2;
  int maior = indice;

  if (filhoEsq < heap->size &&
      heap->aeronave[filhoEsq].prioridade > heap->aeronave[maior].prioridade) {
    maior = filhoEsq;
  }

  if (filhoDir < heap->size &&
      heap->aeronave[filhoDir].prioridade > heap->aeronave[maior].prioridade) {
    maior = filhoDir;
  }

  if (maior != indice) {
    Aeronave temp = heap->aeronave[indice];
    heap->aeronave[indice] = heap->aeronave[maior];
    heap->aeronave[maior] = temp;
    heap = heapifyDown(heap, maior);
  }

  return heap;
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
  printf("\nEscolha uma aeronave para editar as informações:\n");
  imprimeHeap(heap);

  char identificador[50];
  Aeronave tempAeronave;
  int indice = -1;

  printf("Digite o identificador da aeronave: ");
  scanf("%s", identificador);

  for (int i = 0; i < heap->size; i++) {
    if (strcmp(heap->aeronave[i].identificador, identificador) == 0) {
      indice = i;
      break;
    }
  }

  if (indice == -1) {
    printf("Aeronave com identificador %s não encontrada.\n", identificador);
    return heap;
  }

  tempAeronave = heap->aeronave[indice];

  printf("Digite as novas informações (combustível, horário, tipo, "
         "emergência):\n");
  int combustivel, horario, tipo, emergencia;
  scanf("%d %d %d %d", &combustivel, &horario, &tipo, &emergencia);

  if (combustivel < 0 || horario < 0 || tipo < 0 || emergencia < 0) {
    printf("Valores inválidos.\n");
    return heap;
  }

  Aeronave novaAeronave =
      criaAeronave(identificador, combustivel, horario, tipo, emergencia);

  int prioridadeAntiga = heap->aeronave[indice].prioridade;

  heap->aeronave[indice] = heap->aeronave[heap->size - 1];
  heap->size--;

  insereAeronave(novaAeronave, heap);

  if (prioridadeAntiga < novaAeronave.prioridade) {
    heapifyUp(heap, indice);
  } else if (prioridadeAntiga > novaAeronave.prioridade) {
    heapifyDown(heap, indice);
  }

  return heap;
}

MaxHeap *carregaHeap(const char *caminho) {
  FILE *arquivo = fopen(caminho, "r");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    exit(1);
  }

  MaxHeap *heap = criaHeap();
  char linha[100];
  int indice = 0;
  while (fgets(linha, sizeof(linha), arquivo)) {
    char identificador[50];
    int combustivel, horario, tipo, emergencia;

    sscanf(linha, "%49[^,],%d,%d,%d,%d", identificador, &combustivel, &horario,
           &tipo, &emergencia);

    char *identificadorCopia = (char *)malloc(strlen(identificador) + 1);
    if (identificadorCopia == NULL) {
      perror("Erro ao alocar memória para identificador");
      exit(1);
    }
    strcpy(identificadorCopia, identificador);
    if (heap->size >= heap->capacity) {
      heap->capacity *= 2;
      heap->aeronave = (Aeronave *)realloc(heap->aeronave,
                                           heap->capacity * sizeof(Aeronave));
    }

    Aeronave novaAeronave = criaAeronave(identificadorCopia, combustivel,
                                         horario, tipo, emergencia);
    novaAeronave.prioridade =
        calculaPrioridade(combustivel, horario, tipo, emergencia);
    heap = insereAeronave(novaAeronave, heap);

    indice++;
  }

  fclose(arquivo);
  return heap;
}

void salvaHeap(const MaxHeap *heap, const char *caminho) {
  FILE *arquivo = fopen(caminho, "w");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo para escrita");
    exit(1);
  }

  for (int i = 0; i < heap->size; i++) {
    fprintf(arquivo, "%s,%d,%d,%d,%d\n", heap->aeronave[i].identificador,
            heap->aeronave[i].combustivel, heap->aeronave[i].horario,
            heap->aeronave[i].tipo, heap->aeronave[i].emergencia);
  }

  fclose(arquivo);
}
