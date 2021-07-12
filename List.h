#ifndef  List_INC
#define  List_INC

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Object.h"

typedef struct Node{
  Object data;
  struct Node* next;
  struct Node* prev;
}Node;
typedef Node* NodePtr;

typedef struct List{
  NodePtr first;
  NodePtr last;
  NodePtr cursor;
  size_t len;
}List;

List* List_New();
void List_Delete(List* this);
bool List_InsertBack(List* this, Object _data);
bool List_InsertFront(List* this, Object _data);
bool List_RemoveBack(List* this, Object* _data_back);
bool List_RemoveFront(List* this, Object* _data_back );
bool List_IsEmpty(List* this);
Object List_Get(List* this);
void List_ForEach(List* this, void(*impfun)(Object) );
void List_CursorNext(List* this);
void List_CursorLast(List* this);
void List_CursorFirst(List* this);

#endif   /* ----- #ifndef List_INC  ----- */
