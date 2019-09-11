#include "sm.h"

void InitSM(sm_t *sm, short addr, handle_t handle)
{
  sm->state = ST_STX;
  sm->my_addr = addr;
  sm->handle = handle;

  // definir as funções de cada estado
  sm->action[ST_STX] = fn_STX;
}

void ExecSM(sm_t *sm, char data)
{
  sm->action[sm->state](sm, data);
}

static void fn_STX(sm_t *sm, char data)
{
  if(data == STX)
    sm->state = ST_ADDR;
}

static void fn_ADDR(sm_t *sm, char data)
{
  if()
}
