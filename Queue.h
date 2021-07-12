#ifndef  Queue_INC
#define  Queue_INC

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include "List.h"

typedef struct Queue{
  List* queue;
  size_t front;
  size_t back;
  size_t len;
}Queue;

Queue* Queue_New();
void Queue_Delete(Queue* this);
void Queue_Insert(Queue* this, Object _data);
void Queue_Remove(Queue* this,Objectptr _data_back);
bool Queue_IsEmpty(Queue* this);
Object Queue_Peek(Queue* this);


#endif   /* ----- #ifndef Queue_INC  ----- */
