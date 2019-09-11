#ifndef _SM_H_
#define _SM_H_

#define STX '$'
#define ETX '~'
#define BUFFER_SIZE 128

struct _sm_t;

typedef void (*action_t)(struct _sm_t*, char);
typedef void (*handle_t)(char*);

typedef enum{
  ST_STX, ST_ADDR, ST_QTD, ST_END
}state_t;

typedef struct _sm_t{
  state_t state;
  short my_addr;
  char buffer[BUFFER_SIZE];
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

#endif
