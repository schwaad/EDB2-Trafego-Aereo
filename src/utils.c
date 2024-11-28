#include "../include/utils.h"

void menuInicial() {
  printf("Digite a opção que deseja:\n");
  printf("1 - Criar novo sistema de controle\n2 - Carregar sistema de controle "
         "existente\n0 - Sair\n");
}

int menuInput() {
  int entrada;
  scanf("%d", &entrada);
  return entrada;
}

void menuSistemaControle() {
  printf("Digite a opção que deseja:\n");
  printf("1 - Inserir aeronave\n2 - Editar aeronave\n3 - Remover primeira da "
         "fila\n4 - Salvar heap\n0 - Voltar\n");
}

void clearTerminal() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void pauseProgram() {
  printf("Insira qualquer tecla para continuar...");
  getchar();
}

void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}
