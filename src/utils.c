#include "../include/utils.h"

void menuInicial() {
  printf("Digite a opção que deseja:\n");
  printf("1 - Criar novo sistema de controle\n2 - Carregar sistema de controle "
         "existente\n3 - Sair");
}

void menuSistemaControle() {
  printf("Digite a opção que deseja:\n");
  printf("1 - Inserir aeronave\n 2 - Editar aeronave\n 3 - Remover primeira da "
         "fila");
}

void clearTerminal() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}
