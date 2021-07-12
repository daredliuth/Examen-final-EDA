#ifndef  CDLL_INC
#define  CDLL_INC

#include <stdlib.h> // para malloc and friends
#include <assert.h> // para los asserts
#include <stdbool.h> // para bool, true y false
#include "Object.h"


typedef Object Item;
typedef Object* ItemPtr;

typedef struct Node {
    Item data;
    struct Node* next;
    struct Node* prev;
}Node;
typedef Node* NodePtr;

typedef struct CDLL {
    NodePtr first;
    NodePtr last;
    NodePtr cursor;
    size_t len;
} CDLL;

CDLL*  CDLL_New();
void   CDLL_Delete(      CDLL* this );
bool   CDLL_InsertBack(  CDLL* this, Item _data );
bool   CDLL_InsertFront( CDLL* this, Item _data );
bool   CDLL_InsertAfter( CDLL* this, Item _data );
bool   CDLL_InsertBefore(CDLL* this, Item _data );
bool   CDLL_Remove(      CDLL* this, ItemPtr _data_back );
bool   CDLL_RemoveFront( CDLL* this, ItemPtr _data_back );
bool   CDLL_RemoveBack(  CDLL* this, ItemPtr _data_back );
bool   CDLL_RemoveAfter( CDLL* this, ItemPtr _data_back );
bool   CDLL_RemoveBefore(CDLL* this, ItemPtr _data_back );
size_t CDLL_Len(         CDLL* this );
bool   CDLL_IsEmpty(     CDLL* this );
void   CDLL_MakeEmpty(   CDLL* this );
bool   CDLL_Peek(        CDLL* this, ItemPtr _data_back );
void   CDLL_CursorFirst( CDLL* this );
void   CDLL_CursorLast(  CDLL* this );
void   CDLL_CursorNext(  CDLL* this );
void   CDLL_CursorPrev(  CDLL* this );
bool   CDLL_FindIf(      CDLL* this, Item _key, bool (*cmp) (Item,Item) );
bool   CDLL_Search(      CDLL* this, Item _key );
void   CDLL_Traverse(    CDLL* this, void (*pfun)(Item) );
#endif   /* ----- #ifndef DLL_INC  ----- */
