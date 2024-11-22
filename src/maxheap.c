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

MaxHeap *insereAeronave(Aeronave aeronave, MaxHeap *heap) {
  if (heap->size >= heap->capacity) {
    heap = redimensionaHeap(heap);
  }

  heap->aeronave[heap->size] = aeronave;
  heap = heapifyUp(heap, heap->size);
  heap->size++;
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

  if (filhoEsq > heap->size) {
    return heap;
  }
  if (heap->aeronave[filhoEsq].prioridade <
      heap->aeronave[filhoDir].prioridade) {
    Aeronave temp = heap->aeronave[filhoEsq];
    heap->aeronave[filhoEsq] = heap->aeronave[filhoDir];
    heap->aeronave[filhoDir] = temp;
  }
  if (heap->aeronave[indice].prioridade < heap->aeronave[filhoEsq].prioridade) {
    Aeronave temp = heap->aeronave[filhoEsq];
    heap->aeronave[filhoEsq] = heap->aeronave[indice];
    heap->aeronave[indice] = temp;
    heapifyDown(heap, indice++);
  }
}

MaxHeap *cmpLeftRight(MaxHeap *heap) {
  int i = heap->size - 1;
  while (i >= 0) {
    int filhoEsq = 2 * i + 1;
    int filhoDir = 2 * i + 2;

    if (filhoEsq < heap->size && filhoDir < heap->size &&
        heap->aeronave[filhoEsq].prioridade <
            heap->aeronave[filhoDir].prioridade) {
      Aeronave temp = heap->aeronave[filhoEsq];
      heap->aeronave[filhoEsq] = heap->aeronave[filhoDir];
      heap->aeronave[filhoDir] = temp;
    }

    i--;
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
  printf(
      "\nEscolha uma aeronave para editar as informações (insira o índice):\n");
  imprimeHeap(heap);

  int indice;
  scanf("%d", &indice);
  indice -= 1;

  if (indice < 0 || indice >= heap->size) {
    printf("Índice inválido.\n");
    return heap;
  }

  printf("Digite as novas informações (combustível, horário, tipo, "
         "emergência):\n");
  int combustivel, horario, tipo, emergencia;
  scanf("%d %d %d %d", &combustivel, &horario, &tipo, &emergencia);

  if (combustivel < 0 || horario < 0 || tipo < 0 || emergencia < 0) {
    printf("Valores inválidos.\n");
    return heap;
  }

  int prioridadeAntiga = heap->aeronave[indice].prioridade;
  Aeronave novaAeronave = criaAeronave(heap->aeronave[indice].identificador,
                                       combustivel, horario, tipo, emergencia);

  heap->aeronave[indice] = heap->aeronave[heap->size - 1];
  heap->size--;
  insereAeronave(novaAeronave, heap);
  if (prioridadeAntiga < novaAeronave.prioridade) {
    heapifyUp(heap, indice);
  } else if (prioridadeAntiga > novaAeronave.prioridade) {
    heapifyDown(heap, indice);
  }
  cmpLeftRight(heap);
  return heap;
}

MaxHeap *carregaHeap(const char *caminho) {
  FILE *arquivo = fopen(caminho, "r");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    exit(1);
  }

  MaxHeap *heap = criaHeap();
  char linha[100]; // Tamanho adequado para armazenar uma linha do CSV
  int indice = 0;
  while (fgets(linha, sizeof(linha), arquivo)) {
    char identificador[50]; // Espaço suficiente para o identificador
    int prioridade, combustivel, horario, tipo, emergencia;

    // Lê os dados da linha, garantindo que o identificador seja lido
    // corretamente
    sscanf(linha, "%49[^,],%d,%d,%d,%d,%d", identificador, &prioridade,
           &combustivel, &horario, &tipo, &emergencia);

    // Aloca dinamicamente para o identificador
    char *identificadorCopia = (char *)malloc(strlen(identificador) + 1);
    if (identificadorCopia == NULL) {
      perror("Erro ao alocar memória para identificador");
      exit(1);
    }
    strcpy(identificadorCopia,
           identificador); // Copia o identificador para a memória alocada

    // Se necessário, realoca a heap
    if (heap->size >= heap->capacity) {
      heap->capacity *= 2;
      heap->aeronave = (Aeronave *)realloc(heap->aeronave,
                                           heap->capacity * sizeof(Aeronave));
    }

    // Cria a aeronave e insere na heap
    Aeronave novaAeronave = criaAeronave(identificadorCopia, combustivel,
                                         horario, tipo, emergencia);
    insereAeronave(novaAeronave, heap);

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
