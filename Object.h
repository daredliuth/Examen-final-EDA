#ifndef  Object_INC
#define  Object_INC

#include<stdlib.h>
#include<assert.h>

typedef struct{
  int peso;
  int valor;
}Object;
typedef Object* Objectptr;

Objectptr Object_New( int weight, int value );
void Object_Delete(Objectptr p);
void Object_SetWeight( int weight, Objectptr p );
int Object_GetWeight(Objectptr p);
void Object_SetValue( int value, Objectptr p );
int Object_GetValue(Objectptr p);

#endif   /* ----- #ifndef Object_INC  ----- */
