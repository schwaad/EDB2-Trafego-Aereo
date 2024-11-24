#include <stdbool.h>
#include <string.h>

#ifndef AERONAVE_H
#define AERONAVE_H

typedef struct {
  char *identificador;
  int combustivel;
  int horario;
  int tipo;
  int emergencia;
  int prioridade;
} Aeronave;

int calculaPrioridade(int combustivel, int horario, int tipo, int emergencia);
Aeronave criaAeronave(char *identificador, int combustivel, int horario,
                      int tipo, int emergencia);

#endif AERONAVE_H
