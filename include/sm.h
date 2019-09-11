#ifndef _SM_H_
#define _SM_H_

#include <stdint.h>
#include <stdio.h>

#define STX '$'
#define ETX '~'
#define BUFFER_SIZE 128

struct _sm_t;

typedef void (*action_t)(struct _sm_t*, char);
typedef void (*handle_t)(char*);

typedef enum{
  ST_STX,
  ST_ADDR,
  ST_QTD,
  ST_DADO,
  ST_CHK,
  ST_ETX,
  ST_END
}state_t;

typedef struct _sm_t{
  // estado da maquina
  state_t state;

  // endereço
  short my_addr;
  uint8_t addr_flag;
  short addr_rec;

  // quantidade de dados
  uint8_t qtd_dados;

  // dados
  unsigned int data_i;
  char buffer[BUFFER_SIZE];

  // check sum
  uint8_t chk_cal;
  uint8_t chk_rec;

  // void (*action[ST_END])(struct _sm_t*, char);
  action_t action[ST_END];

  // void (*handle)(char*);
  handle_t handle;
}sm_t;

// funcoes publicas
void InitSM(sm_t *sm, short addr, handle_t handle);
void ExecSM(sm_t *sm, char data);

// funcoes privadas
static void fn_STX(sm_t *sm, char data);
static void fn_ADDR(sm_t *sm, char data);
static void fn_QTD(sm_t *sm, char data);
static void fn_DADO(sm_t *sm, char data);
static void fn_CHK(sm_t *sm, char data);
static void fn_ETX(sm_t *sm, char data);

#endif
