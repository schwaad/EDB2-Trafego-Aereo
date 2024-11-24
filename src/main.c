#include "../include/aeronave.h"
#include "../include/maxheap.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  MaxHeap *heap = criaHeap();
  clearTerminal();

  while (1) {
    menuInicial();
    int entradaInicial = menuInput();
    clearBuffer();

    if (entradaInicial == 0)
      break;

    switch (entradaInicial) {
    case 1: {
      while (1) {
        clearTerminal();
        menuSistemaControle();
        int entradaSecund = menuInput();
        clearBuffer();

        if (entradaSecund == 0)
          break;

        switch (entradaSecund) {
        case 1: {
          char identificador[50];
          int combustivel, horario, tipo, emergencia;

          printf("Digite o identificador da aeronave:\n");
          fgets(identificador, sizeof(identificador), stdin);
          identificador[strcspn(identificador, "\n")] =
              '\0'; // Remove o '\n' ao final

          printf("Digite o combustível da aeronave:\n");
          scanf("%d", &combustivel);

          printf("Digite o horário da aeronave:\n");
          scanf("%d", &horario);

          printf("Digite o tipo da aeronave:\n");
          scanf("%d", &tipo);

          printf("Digite 1 para emergência ou 0 para não emergência:\n");
          scanf("%d", &emergencia);

          clearBuffer();

          Aeronave novaAeronave = criaAeronave(identificador, combustivel,
                                               horario, tipo, emergencia);
          insereAeronave(novaAeronave, heap);

          imprimeHeap(heap);
          pauseProgram();
          break;
        }
        case 2:
          editarAeronave(heap);
          imprimeHeap(heap);
          clearBuffer();
          pauseProgram();
          break;

        case 3:
          removePrimeiraAeronave(heap);
          printf("Removida com sucesso.\n");
          imprimeHeap(heap);
          clearBuffer();
          pauseProgram();
          break;
        case 4: {
          char caminho[255];
          printf("Digite o caminho com o nome do arquivo csv que deseja "
                 "salvar:\n");
          scanf("%s", caminho);
          salvaHeap(heap, caminho);
          printf("Heap salva com sucesso.\n");
          clearBuffer();
          pauseProgram();
          break;
        }
        default:
          printf("Entrada inválida.\n");
        }
      }
      liberaHeap(heap);
      break;
    }
    case 2: {
      char caminho[255];
      printf("Informe o caminho do arquivo csv: ");
      fgets(caminho, sizeof(caminho), stdin);
      caminho[strcspn(caminho, "\n")] = '\0'; // Remove o '\n'
      heap = carregaHeap(caminho);
      printf("Heap carregada com sucesso.\n");
      imprimeHeap(heap);
      clearBuffer();
      pauseProgram();
      while (1) {
        clearTerminal();
        menuSistemaControle();
        int entradaSecund = menuInput();
        clearTerminal();
        if (entradaSecund == 0)
          break;

        switch (entradaSecund) {
        case 1: {
          char identificador[50];
          int combustivel, horario, tipo, emergencia;

          printf("Digite o identificador da aeronave:\n");
          fgets(identificador, sizeof(identificador), stdin);
          identificador[strcspn(identificador, "\n")] =
              '\0'; // Remove o '\n' ao final

          printf("Digite o combustível da aeronave:\n");
          scanf("%d", &combustivel);

          printf("Digite o horário da aeronave:\n");
          scanf("%d", &horario);

          printf("Digite o tipo da aeronave:\n");
          scanf("%d", &tipo);

          printf("Digite 1 para emergência ou 0 para não emergência:\n");
          scanf("%d", &emergencia);

          clearBuffer();

          Aeronave novaAeronave = criaAeronave(identificador, combustivel,
                                               horario, tipo, emergencia);
          insereAeronave(novaAeronave, heap);

          imprimeHeap(heap);
          pauseProgram();
          break;
        }
        case 2:
          editarAeronave(heap);
          imprimeHeap(heap);
          clearBuffer();
          pauseProgram();
          break;

        case 3:
          removePrimeiraAeronave(heap);
          printf("Removida com sucesso.\n");
          imprimeHeap(heap);
          clearBuffer();
          pauseProgram();
          break;
        case 4: {
          char caminho[255];
          printf("Digite o caminho com o nome do arquivo csv que deseja "
                 "salvar:\n");
          scanf("%s", caminho);
          salvaHeap(heap, caminho);
          printf("Heap salva com sucesso.\n");
          clearBuffer();
          pauseProgram();
          break;
        }
        default:
          printf("Entrada inválida.\n");
        }
      }
      break;
    }
    default:
      printf("Entrada inválida.\n");
    }
  }

  liberaHeap(heap);
  return 0;
}
