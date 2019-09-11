#include "sm.h"

sm_t sm1, sm2;

int main(int argc, char const *argv[]) {
  InitSM(&sm1, 1000, );

  return 0;
}

void tratar(char *string)
{
  printf("Pacote recebido: %s\n", string);
}

void interrupt(void)
{
  // fazer ação para executar ExecSM()
}
