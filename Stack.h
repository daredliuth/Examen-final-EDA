#ifndef  Stack_INC
#define  Stack_INC

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include "List.h"

typedef struct
{
    List* stack;
    size_t top;
  } Stack;


Stack*  Stack_New();
void    Stack_Delete( Stack* this );
void    Stack_Push( Stack* this, Object _data );
void     Stack_Pop( Stack* this, Objectptr _data_back );
void     Stack_Peek( Stack* this, Objectptr _data_back );
bool    Stack_IsEmpty( Stack* this );
Stack Stack_Dup(Stack* this);

#endif   /* ----- #ifndef Stack_INC  ----- */
