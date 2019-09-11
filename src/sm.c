#include "sm.h"

void InitSM(sm_t *sm, short addr, handle_t handle)
{
  // estado incial
  sm->state = ST_STX;

  // set up inciaal
  sm->my_addr = addr;
  sm->addr_rec = 0;
  sm->data_i = 0;
  sm->addr_flag = 0;

  // função de tartamento
  sm->handle = handle;

  // definir as funções de cada estado
  sm->action[ST_STX] = fn_STX;
  sm->action[ST_ADDR] = fn_ADDR;
  sm->action[ST_QTD] = fn_QTD;
  sm->action[ST_DADO] = fn_DADO;
  sm->action[ST_CHK] = fn_CHK;
  sm->action[ST_ETX] = fn_ETX;
}

void ExecSM(sm_t *sm, char data)
{
  sm->action[sm->state](sm, data);
}

static void fn_STX(sm_t *sm, char data)
{
  printf("\nSTX state: %c\n", data+48);
  if(data == STX)
    sm->state = ST_ADDR;
}

static void fn_ADDR(sm_t *sm, char data)
{
  printf("\nADDR state: %c\n", data+48);
  if(sm->addr_flag==0)
  {
    // parte menos significativa
    sm->addr_rec = (short) data;
    sm->addr_flag = 1;
  }
  else
  {
    sm->addr_rec += (short)(data << 8);
    printf("Addr: %d\n\r", sm->addr_rec);
    printf("Addr: %d\n\r", sm->my_addr);
    if(sm->addr_rec == sm->my_addr){

      sm->state = ST_QTD;
      sm->chk_cal = sm->my_addr;
    }
    else{
      sm->state = ST_STX;
    }

    sm->addr_flag = 0;
    sm->addr_rec = 0;
  }
}

static void fn_QTD(sm_t *sm, char data)
{
  printf("\nQTD state: %c\n", data);
  sm->qtd_dados = (uint8_t) data;
  sm->state = ST_DADO;
}

static void fn_DADO(sm_t *sm, char data)
{
  printf("\nDADO state: %c\tCHK: %c\n", data, sm->chk_cal);
  sm->buffer[sm->data_i++] = data;
  sm->chk_cal += (uint8_t) sm->buffer[sm->data_i-1];

  if(sm->data_i == sm->qtd_dados)
    sm->state = ST_CHK;
}

static void fn_CHK(sm_t *sm, char data)
{
  printf("\nCHK state: %c\n", data);
  sm->chk_rec = (uint8_t) data;

  if(sm->chk_cal == sm->chk_rec){
    sm->state = ST_ETX;
  }
  else{
    sm->state = ST_STX;
  }
}

static void fn_ETX(sm_t *sm, char data)
{
  printf("\nETX state: %c\n", data);
  if(data==ETX){
    sm->handle(sm->buffer);
    sm->state = ST_STX;
  }
  else{
    sm->state = ST_STX;
  }
}
