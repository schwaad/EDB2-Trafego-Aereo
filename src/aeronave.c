#include "../include/aeronave.h"
#include <stdio.h>

int calculaPrioridade(int combustivel, int horario, int tipo, int emergencia) {
  return (1000 - combustivel) + (1440 - horario) + 500 * tipo +
         5000 * emergencia;
}

Aeronave criaAeronave(char *identificador, int combustivel, int horario,
                      int tipo, int emergencia) {
  Aeronave novaAeronave;
  novaAeronave.identificador = identificador;
  novaAeronave.combustivel = combustivel;
  novaAeronave.horario = horario;
  novaAeronave.tipo = tipo;
  novaAeronave.emergencia = emergencia;
  novaAeronave.prioridade =
      calculaPrioridade(combustivel, horario, tipo, emergencia);
  return novaAeronave;
}
