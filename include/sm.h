#ifndef _SM_H_
#define _SM_H_

#define STX '$'
#define BUFFER_SIZE 128

typedef enum{
  ST_STX, ST_ADDR, ST_QTD, ST_END;
}state_t;

typedef void (*action_t)(char);
typedef void (*handle_t)(char*);

typedef struct _sm_t{
  state_t state;
  short my_addr;
  char buffer[BUFFER_SIZE];
  action_t action[ST_END];
  handle_t handle;
}sm_t;

void InitSM(sm_t *sm, short addr, handle_t handle);
void ExecSM(sm_t *sm, char data);

#endif
