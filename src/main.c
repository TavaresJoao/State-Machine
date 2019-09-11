#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "sm.h"

#define TRUE 1
#define FALSE 0
#define UART_BUFFER_SIZE 512
#define SPI_BUFFER_SIZE 512

// prototipo das funcoes
void interrupt_uart(int sigN);
void interrupt_spi(int sigN);
void timeout(int sigN);
void tratar_uart(char *string);
void tratar_spi(char *string);

// maquinas de estados (sm1->uart; sm2->spi)
sm_t sm1, sm2;

// buffers das interfaces
char uart_buf[UART_BUFFER_SIZE];
unsigned int uart_it = 0;
char spi_buf[SPI_BUFFER_SIZE];
unsigned int spi_it = 0;

// Os files simularao os barrametos de dados
FILE *file_uart, *file_spi;

// array de testes
unsigned i_dados=0;
char dados[] = {7, 8, STX, 0xBB, 0xAA, 5, 't', 'e', 's', 't', 'e', 0x8F, ETX};

int trocar = 0;

int main(int argc, char const *argv[])
{
  // abrindo os arquivos ("incicializando" as interfaces)
  file_uart = fopen(argv[1], "r");
  file_spi = fopen(argv[2], "r");

  if(file_uart==NULL || file_spi==NULL)
    return 1;
  // os sinais vao "simular" as interrupcoes
  signal(SIGINT,  interrupt_uart);  // ctrl+C
  signal(SIGTSTP, interrupt_spi);   // ctrl+Z
  signal(SIGALRM, timeout);         // alarme

  // inciar as máquinas de estados
  InitSM(&sm1, 43707, tratar_uart);
  //InitSM(&sm2, 10, tratar_spi);

  // loop do micro
  while(1)
  {
    /*
    while(uart_it){
      //printf("Exec: %c\n", uart_buf[uart_it-1]);
      ExecSM(&sm1, uart_buf[--uart_it]);
    }

    while(spi_it)
      ExecSM(&sm2, spi_buf[spi_it--]);*/
    ExecSM(&sm1, dados[i_dados++]);

    // pausa o código ate cheagr um sinal
    pause();
  }

  fclose(file_uart);
  fclose(file_spi);
  return 0;
}

void interrupt_uart(int sigN)
{
  /*
  if(trocar==0)
  {
    uart_buf[uart_it++] = (char) fgetc(file_uart);
    trocar = 1;
  }
  else
  {
    spi_buf[spi_it++] = (char) fgetc(file_spi);
    trocar = 0;
  }
  */
  //uart_buf[uart_it++] = (char) fgetc(file_uart);
}

void interrupt_spi(int sigN)
{
  spi_buf[spi_it++] = (char) fgetc(file_spi);
}

void timeout(int sigN)
{
  exit(0);
}

void tratar_uart(char *string)
{
  printf("\nPacote recebido na uart: %s\n", string);
}

void tratar_spi(char *string)
{
  printf("\nPacote recebido na spi: %s\n", string);
}
